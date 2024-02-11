#include "settingswindow.h"

namespace s21 {
SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent) {
  setWindowFlags(Qt::Window);
  setFixedSize(QSize(400, 600));
  layout_ = new QVBoxLayout();
  move_x_ = new QSlider(Qt::Horizontal, this);
  move_z_ = new QSlider(Qt::Horizontal, this);
  move_y_ = new QSlider(Qt::Horizontal, this);
  line_edit_x_ = new QLineEdit(this);
  line_edit_x_->setValidator(new QDoubleValidator(this));
  line_edit_y_ = new QLineEdit(this);
  line_edit_y_->setValidator(new QDoubleValidator(this));
  line_edit_z_ = new QLineEdit(this);
  line_edit_z_->setValidator(new QDoubleValidator(this));
  move_x_label_ = new QLabel("X-axis movement", this);
  move_y_label_ = new QLabel("Y-axis movement", this);
  move_z_label_ = new QLabel("Z-axis movement", this);

  rotate_x_ = new QSlider(Qt::Horizontal, this);
  line_edit_rx_ = new QLineEdit(this);
  line_edit_rx_->setValidator(new QDoubleValidator(this));
  rotate_y_ = new QSlider(Qt::Horizontal, this);
  line_edit_ry_ = new QLineEdit(this);
  line_edit_ry_->setValidator(new QDoubleValidator(this));
  rotate_z_ = new QSlider(Qt::Horizontal, this);
  line_edit_rz_ = new QLineEdit(this);
  line_edit_rz_->setValidator(new QDoubleValidator(this));
  rotate_x_label_ = new QLabel("X-axis rotation", this);
  rotate_y_label_ = new QLabel("Y-axis rotation", this);
  rotate_z_label_ = new QLabel("Z-axis rotation", this);

  scale_object_ = new QSlider(Qt::Horizontal, this);
  scale_object_label_ = new QLabel("Scale object");
  scale_edit_ = new QLineEdit(this);
  scale_edit_->setValidator(new QDoubleValidator(this));

  background_color_button_ = new QPushButton("Change background color", this);
  line_color_button_ = new QPushButton("Change line color", this);
  background_color_ = QColor(Qt::white);
  line_color_ = QColor(Qt::black);
  point_color_ = QColor(Qt::black);

  setLayout(layout_);
}

void SettingsWindow::SaveSettings(
    QSettings *setts, Qt3DRender::QCamera *camera_obj, Qt3DRender::QMesh *mesh,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material,
    Qt3DExtras::Qt3DWindow *view) {
  Qt3DRender::QCameraLens *lens = camera_obj->lens();
  Qt3DRender::QCameraLens::ProjectionType projection_type =
      lens->projectionType();
  if (projection_type == Qt3DRender::QCameraLens::PerspectiveProjection)
    setts->setValue("projection", "parallel");
  else if (projection_type == Qt3DRender::QCameraLens::OrthographicProjection)
    setts->setValue("projection", "central");
  if (mesh) {
    Qt3DRender::QGeometryRenderer::PrimitiveType primitive_type =
        mesh->primitiveType();
    if (primitive_type == Qt3DRender::QGeometryRenderer::PrimitiveType::Lines)
      setts->setValue("line type", "lines");
    else if (primitive_type ==
             Qt3DRender::QGeometryRenderer::PrimitiveType::Points)
      setts->setValue("line type", "points");
  }
  QColor line_clr = QColor(Qt::black);
  if (line_material->ambient() != QColor(Qt::black))
    line_clr = line_material->ambient();
  setts->setValue("line material", line_clr.name());
  QColor background_color_button_ = view->defaultFrameGraph()->clearColor();
  setts->setValue("background color", background_color_button_.name());
  setts->sync();
}

void SettingsWindow::LoadSettings(
    QSettings *setts, Qt3DRender::QCamera *camera_obj, Qt3DRender::QMesh *mesh,
    Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *object,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material) {
  QString projection = setts->value("projection").toString();
  if (projection == "parallel") {
    float aspect_ratio = float(view->width()) / view->height();
    camera_obj->lens()->setPerspectiveProjection(45.0f, aspect_ratio, 0.1f,
                                                 10000.0f);
  } else if (projection == "central") {
    float aspect_ratio = float(view->width()) / view->height();
    camera_obj->lens()->setOrthographicProjection(-aspect_ratio, aspect_ratio,
                                                  -1.0, 1.0, 0.1f, 10000.0f);
  }
  QString prim_type = setts->value("line type").toString();
  if (prim_type == "lines")
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  else if (prim_type == "points")
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
  QColor lineMaterial(setts->value("line material").toString());
  line_material->setAmbient(lineMaterial);
  object->addComponent(line_material);
  QColor background_color_button_(setts->value("background color").toString());
  view->defaultFrameGraph()->setClearColor(background_color_button_);
  setts->sync();
}

void SettingsWindow::AddMoveSliders(Qt3DCore::QTransform *transform) {
  move_x_label_->setMaximumSize(150, 15);
  move_y_label_->setMaximumSize(150, 15);
  move_z_label_->setMaximumSize(150, 15);
  move_x_->setRange(-100, 100);  // задаем диапазон слайдера
  move_x_->setTickInterval(1);  // интервал изменения значения слайдера
  move_y_->setRange(-100, 100);
  move_y_->setTickInterval(1);
  move_z_->setRange(-100, 100);
  move_z_->setTickInterval(1);
  QHBoxLayout *x_layout = new QHBoxLayout();
  x_layout->addWidget(move_x_);
  x_layout->addWidget(line_edit_x_);
  QHBoxLayout *y_layout = new QHBoxLayout();
  y_layout->addWidget(move_y_);
  y_layout->addWidget(line_edit_y_);
  QHBoxLayout *z_layout = new QHBoxLayout();
  z_layout->addWidget(move_z_);
  z_layout->addWidget(line_edit_z_);
  layout_->addWidget(move_x_label_);
  layout_->addLayout(x_layout);
  layout_->addWidget(move_y_label_);
  layout_->addLayout(y_layout);
  layout_->addWidget(move_z_label_);
  layout_->addLayout(z_layout);
  connectMoveSlider(move_x_, line_edit_x_, transform, 0);
  connectMoveSlider(move_y_, line_edit_y_, transform, 1);
  connectMoveSlider(move_z_, line_edit_z_, transform, 2);
}

void SettingsWindow::AddRotateSliders(Qt3DCore::QTransform *transform) {
  rotate_x_label_->setMaximumSize(150, 15);
  rotate_y_label_->setMaximumSize(150, 15);
  rotate_z_label_->setMaximumSize(150, 15);
  rotate_x_->setRange(0, 360);
  rotate_x_->setTickInterval(1);
  rotate_y_->setRange(0, 360);
  rotate_y_->setTickInterval(1);
  rotate_z_->setRange(0, 360);
  rotate_z_->setTickInterval(1);
  QHBoxLayout *x_layout = new QHBoxLayout();
  x_layout->addWidget(rotate_x_);
  x_layout->addWidget(line_edit_rx_);
  QHBoxLayout *y_layout = new QHBoxLayout();
  y_layout->addWidget(rotate_y_);
  y_layout->addWidget(line_edit_ry_);
  QHBoxLayout *z_layout = new QHBoxLayout();
  z_layout->addWidget(rotate_z_);
  z_layout->addWidget(line_edit_rz_);
  layout_->addWidget(rotate_x_label_);
  layout_->addLayout(x_layout);
  layout_->addWidget(rotate_y_label_);
  layout_->addLayout(y_layout);
  layout_->addWidget(rotate_z_label_);
  layout_->addLayout(z_layout);
  connectRotateSlider(rotate_x_, line_edit_rx_, transform,
                      &Qt3DCore::QTransform::setRotationX);
  connectRotateSlider(rotate_y_, line_edit_ry_, transform,
                      &Qt3DCore::QTransform::setRotationY);
  connectRotateSlider(rotate_z_, line_edit_rz_, transform,
                      &Qt3DCore::QTransform::setRotationZ);
}

void SettingsWindow::AddScaleSliders(Qt3DRender::QCamera *camera_obj) {
  scale_object_label_->setMaximumSize(150, 20);
  layout_->addWidget(scale_object_label_);
  scale_object_->setRange(-1000, 1000);
  scale_object_->setValue(0);
  QHBoxLayout *x_layout = new QHBoxLayout();
  x_layout->addWidget(scale_object_);
  x_layout->addWidget(scale_edit_);
  layout_->addLayout(x_layout);
  connect(scale_object_, &QSlider::valueChanged, this,
          [this, camera_obj](int value) {
            QVector3D camera_position = camera_obj->position();
            QVector3D view_center = camera_obj->viewCenter();
            QVector3D direction = camera_position - view_center;
            direction.normalize();
            float scale_factor = std::pow(1.01f, value);
            camera_obj->setPosition(view_center + direction * scale_factor);
            scale_edit_->setText(QString::number(value));
          });
  connect(scale_edit_, &QLineEdit::returnPressed, this, [this, camera_obj]() {
    QVector3D camera_position = camera_obj->position();
    QVector3D view_center = camera_obj->viewCenter();
    QVector3D direction = camera_position - view_center;
    direction.normalize();
    float scale_factor = std::pow(1.01f, scale_edit_->text().toFloat());
    camera_obj->setPosition(view_center + direction * scale_factor);
  });
}

void SettingsWindow::ProjectionSettings(Qt3DRender::QCamera *camera_obj,
                                        Qt3DExtras::Qt3DWindow *view) {
  QLabel *proj_label = new QLabel("Select projection:", this);
  QRadioButton *parallel_projection_radio_button =
      new QRadioButton("Parallel projection", this);
  QRadioButton *central_projection_radio_button =
      new QRadioButton("Central projection", this);
  QHBoxLayout *h_layout = new QHBoxLayout();
  h_layout->addWidget(parallel_projection_radio_button);
  h_layout->addWidget(central_projection_radio_button);
  layout_->addWidget(proj_label);
  layout_->addLayout(h_layout);

  connect(parallel_projection_radio_button, &QRadioButton::clicked, this,
          [=]() {
            float aspect_ratio = float(view->width()) / view->height();
            camera_obj->lens()->setOrthographicProjection(
                -aspect_ratio * 2.0f, aspect_ratio * 2.0f, -2.0f, 2.0f, 0.1f,
                10000.0f);
            camera_obj->setPosition(QVector3D(0, 0, 20));
            // camera_obj->setPosition(QVector3D(0, 20, 0));
            // camera_obj->setPosition(QVector3D(20, 0, 0));
            camera_obj->setViewCenter(QVector3D(0, 0, 0));
            camera_obj->setUpVector(QVector3D(0, 1, 0));
          });

  connect(central_projection_radio_button, &QRadioButton::clicked, this, [=]() {
    float aspect_ratio = float(view->width()) / view->height();
    camera_obj->lens()->setPerspectiveProjection(45.0f, aspect_ratio, 0.1f,
                                                 10000.0f);
    camera_obj->setPosition(QVector3D(0, 2, 0));
    camera_obj->setViewCenter(QVector3D(1, 1, 0));
    camera_obj->setUpVector(QVector3D(1, 0, 0));
  });
}

void SettingsWindow::LineTypeSettings(Qt3DRender::QMesh *mesh) {
  type_label_ = new QLabel("Select line type:", this);
  line_type_radio_button_ = new QRadioButton("Solid line", this);
  dot_type_radio_button_ = new QRadioButton("Dotted line", this);
  line_type_layout_ = new QHBoxLayout();
  line_type_layout_->addWidget(line_type_radio_button_);
  line_type_layout_->addWidget(dot_type_radio_button_);
  layout_->addWidget(type_label_);
  layout_->addLayout(line_type_layout_);
  connect(line_type_radio_button_, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  });
  connect(dot_type_radio_button_, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
  });
}

void SettingsWindow::LineColorSettings(
    Qt3DCore::QEntity *object,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material) {
  layout_->addWidget(line_color_button_);
  connect(line_color_button_, &QPushButton::clicked, this, [=]() {
    line_color_ = QColorDialog::getColor(Qt::white, this, "Choose line color");
    if (line_color_.isValid()) {
      line_material->setAmbient(line_color_);
      object->addComponent(line_material);
    }
  });
}

void SettingsWindow::BackgroundSettings(Qt3DExtras::Qt3DWindow *view) {
  layout_->addWidget(background_color_button_);
  connect(background_color_button_, &QPushButton::clicked, this, [=]() {
    background_color_ =
        QColorDialog::getColor(Qt::white, this, "Choose background color");
    if (background_color_.isValid())
      view->defaultFrameGraph()->setClearColor(QColor(background_color_));
  });
}
}  // namespace s21
