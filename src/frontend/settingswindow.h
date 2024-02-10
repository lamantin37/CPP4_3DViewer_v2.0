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
    float x = move_x_->value();                               \
    float y = move_y_->value();                               \
    float z = move_z_->value();                               \
    transform->setTranslation(QVector3D(x, y, z));            \
    LINE_EDIT->setText(QString::number(SLIDER->value()));     \
  });                                                         \
                                                              \
  connect(LINE_EDIT, &QLineEdit::returnPressed, this, [=]() { \
    float x = move_x_->value();                               \
    float y = move_y_->value();                               \
    float z = move_z_->value();                               \
    transform->setTranslation(QVector3D(x, y, z));            \
    SLIDER->setValue(LINE_EDIT->text().toFloat());            \
  });

class SettingsWindow : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsWindow(QWidget *parent = nullptr);
  void AddMoveSliders(Qt3DCore::QTransform *transform);
  void AddRotateSliders(Qt3DCore::QTransform *transform);
  void AddScaleSliders(Qt3DRender::QCamera *camera_obj);
  void ProjectionSettings(Qt3DRender::QCamera *camera_obj,
                          Qt3DExtras::Qt3DWindow *view);
  void LineTypeSettings(Qt3DRender::QMesh *mesh);
  void LineColorSettings(Qt3DCore::QEntity *object,
                         Qt3DExtras::QDiffuseSpecularMaterial *line_material);
  void BackgroundSettings(Qt3DExtras::Qt3DWindow *view);
  void SaveSettings(QSettings *setts, Qt3DRender::QCamera *camera_obj,
                    Qt3DRender::QMesh *mesh,
                    Qt3DExtras::QDiffuseSpecularMaterial *line_material,
                    Qt3DExtras::Qt3DWindow *view);
  void LoadSettings(QSettings *setts, Qt3DRender::QCamera *camera_obj,
                    Qt3DRender::QMesh *mesh, Qt3DExtras::Qt3DWindow *view,
                    Qt3DCore::QEntity *object,
                    Qt3DExtras::QDiffuseSpecularMaterial *line_material);

 private:
  QVBoxLayout *layout_ = nullptr;
  QSlider *move_x_ = nullptr;
  QSlider *move_y_ = nullptr;
  QSlider *move_z_ = nullptr;
  QLabel *move_x_label_ = nullptr;
  QLabel *move_y_label_ = nullptr;
  QLabel *move_z_label_ = nullptr;
  QLineEdit *line_edit_x_ = nullptr;
  QLineEdit *line_edit_y_ = nullptr;
  QLineEdit *line_edit_z_ = nullptr;

  QSlider *rotate_x_ = nullptr;
  QSlider *rotate_y_ = nullptr;
  QSlider *rotate_z_ = nullptr;
  QLabel *rotate_x_label_ = nullptr;
  QLabel *rotate_y_label_ = nullptr;
  QLabel *rotate_z_label_ = nullptr;
  QLineEdit *line_edit_rx_ = nullptr;
  QLineEdit *line_edit_ry_ = nullptr;
  QLineEdit *line_edit_rz_ = nullptr;

  QLineEdit *scale_edit_ = nullptr;

  QSlider *scale_object_ = nullptr;
  QLabel *scale_object_label_ = nullptr;

  QPushButton *background_color_button_ = nullptr;
  QPushButton *line_color_button_ = nullptr;
  QColor background_color_;
  QColor line_color_;
  QColor point_color_;
  QLabel *type_label_ = nullptr;
  QRadioButton *line_type_radio_button_ = nullptr;
  QRadioButton *dot_type_radio_button_ = nullptr;
  QHBoxLayout *line_type_layout_;
};

#endif  // SETTINGSWINDOW_H
