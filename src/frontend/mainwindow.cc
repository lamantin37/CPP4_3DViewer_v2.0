#include "mainwindow.h"

#include <Qt3DRender/QRenderCapture>

#include "./ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      re_settings_("School 21", "3DViewer") {
  ui_->setupUi(this);
  transform_ = new Qt3DCore::QTransform();
  parent_win_ = new Qt3DCore::QEntity();  // конктруктор корневого окна
  parent_win_->setObjectName("Root window");

  view_ = new Qt3DExtras::Qt3DWindow();  // создаем окно для отображения сцены
  view_->defaultFrameGraph()->setClearColor(QRgb(0xffffff));  // стандартный фон
  view_->setRootEntity(parent_win_);  // устанавливаем корневое окно
  controller_ = new Controller();
  QSize screen_size = view_->screen()->size();  // получение размера окна
  facade_ = new Facade();

  widget_ = QWidget::createWindowContainer(
      view_);  // встраивание виджета view в окно приложения
  widget_->setMinimumSize(QSize(100, 100));
  widget_->setMaximumSize(screen_size);  // и установка его как максимального
  widget_->setFocusPolicy(Qt::NoFocus);

  settings_button_ = new QPushButton("Settings", this);
  settings_button_->hide();

  QPushButton *button = new QPushButton("Choose file", this);
  QPushButton *create_gif_button = new QPushButton("Create GIF", this);
  QPushButton *save_model_button = new QPushButton("Save model render", this);

  QLineEdit *line_edit = new QLineEdit(this);

  gif_timer_ = new QTimer(this);

  layout_ = new QVBoxLayout();  // добавление виджета, кнопки и
                                // текстового поля в лейаут
  layout_->addWidget(widget_);
  layout_->addWidget(button);
  layout_->addWidget(line_edit);
  layout_->addWidget(create_gif_button);
  layout_->addWidget(save_model_button);

  this->centralWidget()->setLayout(
      layout_);  // установка его в качестве центрального виджета

  camera_obj_ = view_->camera();  // создаем объект камеры
  camera_obj_->lens()->setPerspectiveProjection(
      45.0f, 16.0f / 9.0f, 0.1f,
      10000.0f);  // устанавливаем параметры проекции камеры
  camera_obj_->setPosition(
      QVector3D(0, 2, 0));  // позиция камеры в трехмерном пространстве
  camera_obj_->setUpVector(
      QVector3D(1, 0, 0));  // вектор верха камеры (x, y, z)
  camera_obj_->setViewCenter(QVector3D(1, 1, 0));  // центр обзора камеры

  line_material_ = new Qt3DExtras::QDiffuseSpecularMaterial(parent_win_);
  line_material_->setAmbient(QColor(Qt::black));

  Qt3DExtras::QOrbitCameraController *cameraController =
      new Qt3DExtras::QOrbitCameraController(parent_win_);
  cameraController->setCamera(camera_obj_);
  cameraController->setLookSpeed(100.0f);   // Скорость вращения
  cameraController->setLinearSpeed(50.0f);  // Линейная скорость

  entity_object_ = new Qt3DCore::QEntity(parent_win_);

  // открытие файла и его загрузка
  OpenObjectFile(line_edit, button);
  settings_win_ = new SettingsWindow(this, controller_, facade_);

  connect(save_model_button, &QPushButton::clicked, this,
          [=]() { ImageRender(); });
  connect(create_gif_button, &QPushButton::clicked, this,
          &MainWindow::CreateGif);
  connect(gif_timer_, &QTimer::timeout, this, &MainWindow::CaptureFrameForGif);
}

MainWindow::~MainWindow() {
  if (mesh_)
    settings_win_->SaveSettings(&re_settings_, camera_obj_, mesh_,
                                line_material_, view_);
  delete controller_;
  delete ui_;
  delete facade_;
}

void MainWindow::OpenObjectFile(QLineEdit *line_edit, QPushButton *button) {
  connect(button, &QPushButton::clicked, this, [=]() {
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "",
                                                    "Obj Files (*.obj)");
    if (filename.isEmpty()) return;
    line_edit->setText(filename);
    if (previous_model_ != filename) {
      previous_model_ = filename;
      Object object_info = facade_->LoadObject(filename);
      UpdateView(filename, &object_info);
      settings_button_->show();
    }
  });
}

void MainWindow::UpdateView(const QString &filename, Object *object_info) {
  if (mesh_ != nullptr) {
    entity_object_->removeComponent(mesh_);
    delete mesh_;
  }
  if (file_label_ != nullptr) {
    layout_->removeWidget(file_label_);
    delete file_label_;
  }
  mesh_ = new Qt3DRender::QMesh(parent_win_);
  previous_model_ = filename;
  file_label_ = facade_->UpdateView(filename, object_info, mesh_,
                                    entity_object_, transform_, layout_);
  settings_win_->LoadSettings(&re_settings_, camera_obj_, mesh_, view_,
                              entity_object_, line_material_);
  Settings();
}

void MainWindow::Settings() {
  layout_->addWidget(settings_button_);
  connect(settings_button_, &QPushButton::clicked, this, [=]() {
    if (!settings_flag_) {
      settings_win_->show();
      settings_win_->AddMoveSliders(transform_);
      settings_win_->AddRotateSliders(transform_);
      settings_win_->AddScaleSliders(transform_);
      settings_win_->ProjectionSettings(camera_obj_);
      settings_win_->LineColorSettings(entity_object_, line_material_);
      settings_win_->LineTypeSettings(mesh_);
      settings_win_->BackgroundSettings(view_);
      settings_flag_ = true;
    } else {
      settings_win_->show();
    }
  });
}

void MainWindow::ObjectInfo(const Object &object, const char *filename) {
  QString str(filename);
  layout_->removeWidget(file_label_);
  layout_->removeWidget(vertices_label_);
  layout_->removeWidget(polygons_label_);
  delete file_label_;
  delete vertices_label_;
  delete polygons_label_;
  file_label_ = new QLabel("File: " + str, this);
  vertices_label_ = new QLabel(
      "Number of vertices: " + QString::number(object.num_of_vertices), this);
  polygons_label_ = new QLabel(
      "Number of polygons: " + QString::number(object.num_of_polygons), this);
  file_label_->setFixedSize(QSize(1000, 20));
  vertices_label_->setFixedSize(QSize(250, 20));
  polygons_label_->setFixedSize(QSize(250, 20));
  layout_->addWidget(file_label_);
  layout_->addWidget(vertices_label_);
  layout_->addWidget(polygons_label_);
}

void MainWindow::ImageRender() {
  QString filename = QFileDialog::getSaveFileName(
      this, "Save Image", "", "JPEG Files (*.jpeg *.jpg);;BMP Files (*.bmp)");
  if (!filename.isEmpty())
    QTimer::singleShot(100, this, [this, filename]() {
      facade_->ImageRender(filename, view_);
    });
}

void MainWindow::CreateGif() {
  gif_file_name_ =
      QFileDialog::getSaveFileName(this, "Save GIF", "", "(*.gif)");
  if (!gif_file_name_.isEmpty()) {
    facade_->StartGifCreation(gif_file_name_, fps_);
    frame_count_ = 0;
    gif_timer_->start(1000 / fps_);
  }
}

void MainWindow::CaptureFrameForGif() {
  if (frame_count_ < gif_time_ * fps_) {
    facade_->CaptureFrameForGif(view_);
    frame_count_++;
  } else {
    gif_timer_->stop();
    facade_->FinishGifCreation();
  }
}

}  // namespace s21
