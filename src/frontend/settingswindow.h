#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>

#include "../backend/auxiliary_modules.h"

#define ROTATE_MACRO(SLIDER, LINE_EDIT, ROTATION)             \
  connect(SLIDER, &QSlider::valueChanged, this, [=]() {       \
    float angle = SLIDER->value();                            \
    transform->ROTATION(angle);                               \
    LINE_EDIT->setText(QString::number(angle));               \
  });                                                         \
                                                              \
  connect(LINE_EDIT, &QLineEdit::returnPressed, this, [=]() { \
    float angle = LINE_EDIT->text().toFloat();                \
    transform->ROTATION(angle);                               \
    SLIDER->setValue(angle);                                  \
  });

#define MOVE_MACRO(SLIDER, LINE_EDIT)                         \
  connect(SLIDER, &QSlider::valueChanged, this, [=]() {       \
    float x = moveX->value();                                 \
    float y = moveY->value();                                 \
    float z = moveZ->value();                                 \
    transform->setTranslation(QVector3D(x, y, z));            \
    LINE_EDIT->setText(QString::number(SLIDER->value()));     \
  });                                                         \
                                                              \
  connect(LINE_EDIT, &QLineEdit::returnPressed, this, [=]() { \
    float x = moveX->value();                                 \
    float y = moveY->value();                                 \
    float z = moveZ->value();                                 \
    transform->setTranslation(QVector3D(x, y, z));            \
    SLIDER->setValue(LINE_EDIT->text().toFloat());            \
  });

class SettingsWindow : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsWindow(QWidget *parent = nullptr);
  void add_move_sliders(Qt3DCore::QTransform *);
  void add_rotate_sliders(Qt3DCore::QTransform *);
  void add_scale_slider(Qt3DRender::QCamera *cameraObj);
  void projection_settings(Qt3DRender::QCamera *, Qt3DExtras::Qt3DWindow *view);
  void line_type_settings(Qt3DRender::QMesh *);
  void line_color_settings(Qt3DCore::QEntity *,
                           Qt3DExtras::QDiffuseSpecularMaterial *);
  void background_settings(Qt3DExtras::Qt3DWindow *);
  void save_settings(QSettings *, Qt3DRender::QCamera *, Qt3DRender::QMesh *,
                     Qt3DExtras::QDiffuseSpecularMaterial *,
                     Qt3DExtras::Qt3DWindow *);
  void load_settings(QSettings *, Qt3DRender::QCamera *, Qt3DRender::QMesh *,
                     Qt3DExtras::Qt3DWindow *, Qt3DCore::QEntity *,
                     Qt3DExtras::QDiffuseSpecularMaterial *);

 private:
  QLabel *label;
  QVBoxLayout *layout = nullptr;
  QSlider *moveX = nullptr;
  QSlider *moveY = nullptr;
  QSlider *moveZ = nullptr;
  QLabel *moveXlabel = nullptr;
  QLabel *moveYlabel = nullptr;
  QLabel *moveZlabel = nullptr;
  QLineEdit *lineEditX = nullptr;
  QLineEdit *lineEditY = nullptr;
  QLineEdit *lineEditZ = nullptr;

  QSlider *rotateX = nullptr;
  QSlider *rotateY = nullptr;
  QSlider *rotateZ = nullptr;
  QLabel *rotateXlabel = nullptr;
  QLabel *rotateYlabel = nullptr;
  QLabel *rotateZlabel = nullptr;
  QLineEdit *lineEditRX = nullptr;
  QLineEdit *lineEditRY = nullptr;
  QLineEdit *lineEditRZ = nullptr;

  QLineEdit *scaleEdit = nullptr;

  QSlider *scaleObject = nullptr;
  QLabel *scaleObjectLabel = nullptr;

  QPushButton *parallelProjection = nullptr;
  QPushButton *centralProjection = nullptr;
  QPushButton *backgroundColor = nullptr;
  QPushButton *lineColor = nullptr;
  QPushButton *lineType = nullptr;
  QPushButton *pointType = nullptr;
  QColor background_color;
  QColor line_color;
  QColor point_color;
  QLabel *typeLabel = nullptr;
  QRadioButton *lineTypeRadioButton = nullptr;
  QRadioButton *dotTypeRadioButton = nullptr;
  QHBoxLayout *LineTypeLayout;
  Qt3DExtras::QDiffuseSpecularMaterial *point_material;
};

#endif  // SETTINGSWINDOW_H
