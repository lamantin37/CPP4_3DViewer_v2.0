#ifndef CPP4_3DVIEWER_V2_0_1_FRONTEND_SETTINGSWINDOW_H_
#define CPP4_3DVIEWER_V2_0_1_FRONTEND_SETTINGSWINDOW_H_
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

namespace s21 {
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
  void connectRotateSlider(
      QSlider *slider, QLineEdit *lineEdit, Qt3DCore::QTransform *transform,
      void (Qt3DCore::QTransform::*rotationFunction)(float)) {
    connect(slider, &QSlider::valueChanged, this, [=]() {
      float angle = slider->value();
      (transform->*rotationFunction)(angle);
      lineEdit->setText(QString::number(angle));
    });

    connect(lineEdit, &QLineEdit::returnPressed, this, [=]() {
      float angle = lineEdit->text().toFloat();
      (transform->*rotationFunction)(angle);
      slider->setValue(angle);
    });
  }

  void connectMoveSlider(QSlider *slider, QLineEdit *lineEdit,
                         Qt3DCore::QTransform *transform, int axis) {
    connect(slider, &QSlider::valueChanged, this, [=]() {
      QVector3D translation = transform->translation();
      translation[axis] = slider->value();
      transform->setTranslation(translation);
      lineEdit->setText(QString::number(slider->value()));
    });

    connect(lineEdit, &QLineEdit::returnPressed, this, [=]() {
      QVector3D translation = transform->translation();
      translation[axis] = lineEdit->text().toFloat();
      transform->setTranslation(translation);
      slider->setValue(translation[axis]);
    });
  }

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
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_FRONTEND_SETTINGSWINDOW_H_
