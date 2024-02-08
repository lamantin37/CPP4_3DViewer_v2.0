#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent) {
  setWindowFlags(Qt::Window);
  setFixedSize(QSize(400, 600));
  layout = new QVBoxLayout();
  moveX = new QSlider(Qt::Horizontal, this);
  moveZ = new QSlider(Qt::Horizontal, this);
  moveY = new QSlider(Qt::Horizontal, this);
  lineEditX = new QLineEdit(this);
  lineEditX->setValidator(new QDoubleValidator(this));
  lineEditY = new QLineEdit(this);
  lineEditY->setValidator(new QDoubleValidator(this));
  lineEditZ = new QLineEdit(this);
  lineEditZ->setValidator(new QDoubleValidator(this));
  moveXlabel = new QLabel("X-axis movement", this);
  moveYlabel = new QLabel("Y-axis movement", this);
  moveZlabel = new QLabel("Z-axis movement", this);

  rotateX = new QSlider(Qt::Horizontal, this);
  lineEditRX = new QLineEdit(this);
  lineEditRX->setValidator(new QDoubleValidator(this));
  rotateY = new QSlider(Qt::Horizontal, this);
  lineEditRY = new QLineEdit(this);
  lineEditRY->setValidator(new QDoubleValidator(this));
  rotateZ = new QSlider(Qt::Horizontal, this);
  lineEditRZ = new QLineEdit(this);
  lineEditRZ->setValidator(new QDoubleValidator(this));
  rotateXlabel = new QLabel("X-axis rotation", this);
  rotateYlabel = new QLabel("Y-axis rotation", this);
  rotateZlabel = new QLabel("Z-axis rotation", this);

  scaleObject = new QSlider(Qt::Horizontal, this);
  scaleObjectLabel = new QLabel("Scale object");
  scaleEdit = new QLineEdit(this);
  scaleEdit->setValidator(new QDoubleValidator(this));

  backgroundColor = new QPushButton("Change background color", this);
  lineColor = new QPushButton("Change line color", this);
  background_color = QColor(Qt::white);
  line_color = QColor(Qt::black);
  point_color = QColor(Qt::black);

  setLayout(layout);
}

void SettingsWindow::save_settings(
    QSettings *setts, Qt3DRender::QCamera *cameraObj, Qt3DRender::QMesh *mesh,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material,
    Qt3DExtras::Qt3DWindow *view) {
  Qt3DRender::QCameraLens *lens = cameraObj->lens();
  Qt3DRender::QCameraLens::ProjectionType projectionType =
      lens->projectionType();
  if (projectionType == Qt3DRender::QCameraLens::PerspectiveProjection) {
    setts->setValue("projection", "parallel");
  } else if (projectionType ==
             Qt3DRender::QCameraLens::OrthographicProjection) {
    setts->setValue("projection", "central");
  }
  Qt3DRender::QGeometryRenderer::PrimitiveType primitiveType =
      mesh->primitiveType();
  if (primitiveType == Qt3DRender::QGeometryRenderer::PrimitiveType::Lines) {
    setts->setValue("line type", "lines");
  } else if (primitiveType ==
             Qt3DRender::QGeometryRenderer::PrimitiveType::Points) {
    setts->setValue("line type", "points");
  }
  QColor line_clr = QColor(Qt::black);
  if (line_material->ambient() != QColor(Qt::black))
    line_clr = line_material->ambient();
  setts->setValue("line material", line_clr.name());
  QColor backgroundColor = view->defaultFrameGraph()->clearColor();
  setts->setValue("background color", backgroundColor.name());
  setts->sync();
}

void SettingsWindow::load_settings(
    QSettings *setts, Qt3DRender::QCamera *cameraObj, Qt3DRender::QMesh *mesh,
    Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *object,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material) {
  QString projection = setts->value("projection").toString();
  if (projection == "parallel") {
    float aspectRatio = float(view->width()) / view->height();
    cameraObj->lens()->setPerspectiveProjection(45.0f, aspectRatio, 0.1f,
                                                10000.0f);
  } else if (projection == "central") {
    float aspectRatio = float(view->width()) / view->height();
    cameraObj->lens()->setOrthographicProjection(-aspectRatio, aspectRatio,
                                                 -1.0, 1.0, 0.1f, 10000.0f);
  }
  QString primType = setts->value("line type").toString();
  if (primType == "lines") {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  } else if (primType == "points") {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
  }
  QColor lineMaterial(setts->value("line material").toString());
  line_material->setAmbient(lineMaterial);
  object->addComponent(line_material);
  QColor backgroundColor(setts->value("background color").toString());
  view->defaultFrameGraph()->setClearColor(backgroundColor);
  setts->sync();
}

void SettingsWindow::add_move_sliders(Qt3DCore::QTransform *transform) {
  moveXlabel->setMaximumSize(150, 15);
  moveYlabel->setMaximumSize(150, 15);
  moveZlabel->setMaximumSize(150, 15);
  moveX->setRange(-100, 100);  // задаем диапазон слайдера
  moveX->setTickInterval(1);  // интервал изменения значения слайдера
  moveY->setRange(-100, 100);
  moveY->setTickInterval(1);
  moveZ->setRange(-100, 100);
  moveZ->setTickInterval(1);
  QHBoxLayout *xLayout = new QHBoxLayout();
  xLayout->addWidget(moveX);
  xLayout->addWidget(lineEditX);
  QHBoxLayout *yLayout = new QHBoxLayout();
  yLayout->addWidget(moveY);
  yLayout->addWidget(lineEditY);
  QHBoxLayout *zLayout = new QHBoxLayout();
  zLayout->addWidget(moveZ);
  zLayout->addWidget(lineEditZ);
  layout->addWidget(moveXlabel);
  layout->addLayout(xLayout);
  layout->addWidget(moveYlabel);
  layout->addLayout(yLayout);
  layout->addWidget(moveZlabel);
  layout->addLayout(zLayout);
  MOVE_MACRO(moveX, lineEditX)
  MOVE_MACRO(moveY, lineEditY)
  MOVE_MACRO(moveZ, lineEditZ)
}

void SettingsWindow::add_rotate_sliders(Qt3DCore::QTransform *transform) {
  rotateXlabel->setMaximumSize(150, 15);
  rotateYlabel->setMaximumSize(150, 15);
  rotateZlabel->setMaximumSize(150, 15);
  rotateX->setRange(0, 360);
  rotateX->setTickInterval(1);
  rotateY->setRange(0, 360);
  rotateY->setTickInterval(1);
  rotateZ->setRange(0, 360);
  rotateZ->setTickInterval(1);
  QHBoxLayout *xLayout = new QHBoxLayout();
  xLayout->addWidget(rotateX);
  xLayout->addWidget(lineEditRX);
  QHBoxLayout *yLayout = new QHBoxLayout();
  yLayout->addWidget(rotateY);
  yLayout->addWidget(lineEditRY);
  QHBoxLayout *zLayout = new QHBoxLayout();
  zLayout->addWidget(rotateZ);
  zLayout->addWidget(lineEditRZ);
  layout->addWidget(rotateXlabel);
  layout->addLayout(xLayout);
  layout->addWidget(rotateYlabel);
  layout->addLayout(yLayout);
  layout->addWidget(rotateZlabel);
  layout->addLayout(zLayout);
  ROTATE_MACRO(rotateX, lineEditRX, setRotationX)
  ROTATE_MACRO(rotateY, lineEditRY, setRotationY)
  ROTATE_MACRO(rotateZ, lineEditRZ, setRotationZ)
}

void SettingsWindow::add_scale_slider(Qt3DRender::QCamera *cameraObj) {
  scaleObjectLabel->setMaximumSize(150, 20);
  layout->addWidget(scaleObjectLabel);
  scaleObject->setRange(-1000, 1000);
  scaleObject->setValue(0);
  QHBoxLayout *xLayout = new QHBoxLayout();
  xLayout->addWidget(scaleObject);
  xLayout->addWidget(scaleEdit);
  layout->addLayout(xLayout);
  connect(scaleObject, &QSlider::valueChanged, this,
          [this, cameraObj](int value) {
            QVector3D cameraPosition = cameraObj->position();
            QVector3D viewCenter = cameraObj->viewCenter();
            QVector3D direction = cameraPosition - viewCenter;
            direction.normalize();
            float scaleFactor = std::pow(1.01f, value);
            cameraObj->setPosition(viewCenter + direction * scaleFactor);
            scaleEdit->setText(QString::number(value));
          });
  connect(scaleEdit, &QLineEdit::returnPressed, this, [this, cameraObj]() {
    QVector3D cameraPosition = cameraObj->position();
    QVector3D viewCenter = cameraObj->viewCenter();
    QVector3D direction = cameraPosition - viewCenter;
    direction.normalize();
    float scaleFactor = std::pow(1.01f, scaleEdit->text().toFloat());
    cameraObj->setPosition(viewCenter + direction * scaleFactor);
  });
}

void SettingsWindow::projection_settings(Qt3DRender::QCamera *cameraObj,
                                         Qt3DExtras::Qt3DWindow *view) {
  QLabel *projLabel = new QLabel("Select projection:", this);
  QRadioButton *parallelProjectionRadioButton =
      new QRadioButton("Parallel projection", this);
  QRadioButton *centralProjectionRadioButton =
      new QRadioButton("Central projection", this);
  QHBoxLayout *hLayout = new QHBoxLayout();
  hLayout->addWidget(parallelProjectionRadioButton);
  hLayout->addWidget(centralProjectionRadioButton);
  layout->addWidget(projLabel);
  layout->addLayout(hLayout);
  connect(parallelProjectionRadioButton, &QRadioButton::clicked, this, [=]() {
    float aspectRatio = float(view->width()) / view->height();
    cameraObj->lens()->setOrthographicProjection(-aspectRatio, aspectRatio,
                                                 -1.0, 1.0, 0.1f, 10000.0f);
  });
  connect(centralProjectionRadioButton, &QRadioButton::clicked, this, [=]() {
    float aspectRatio = float(view->width()) / view->height();
    cameraObj->lens()->setPerspectiveProjection(45.0f, aspectRatio, 0.1f,
                                                10000.0f);
  });
}

void SettingsWindow::line_type_settings(Qt3DRender::QMesh *mesh) {
  typeLabel = new QLabel("Select line type:", this);
  lineTypeRadioButton = new QRadioButton("Solid line", this);
  dotTypeRadioButton = new QRadioButton("Dotted line", this);
  LineTypeLayout = new QHBoxLayout();
  LineTypeLayout->addWidget(lineTypeRadioButton);
  LineTypeLayout->addWidget(dotTypeRadioButton);
  layout->addWidget(typeLabel);
  layout->addLayout(LineTypeLayout);
  connect(lineTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  });
  connect(dotTypeRadioButton, &QRadioButton::clicked, this, [=]() {
    mesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
  });
}

void SettingsWindow::line_color_settings(
    Qt3DCore::QEntity *object,
    Qt3DExtras::QDiffuseSpecularMaterial *line_material) {
  layout->addWidget(lineColor);
  connect(lineColor, &QPushButton::clicked, this, [=]() {
    line_color = QColorDialog::getColor(Qt::white, this, "Choose line color");
    if (line_color.isValid()) {
      line_material->setAmbient(line_color);
      object->addComponent(line_material);
    }
  });
}

void SettingsWindow::background_settings(Qt3DExtras::Qt3DWindow *view) {
  layout->addWidget(backgroundColor);
  connect(backgroundColor, &QPushButton::clicked, this, [=]() {
    background_color =
        QColorDialog::getColor(Qt::white, this, "Choose background color");
    if (background_color.isValid()) {
      view->defaultFrameGraph()->setClearColor(QColor(background_color));
    }
  });
}
