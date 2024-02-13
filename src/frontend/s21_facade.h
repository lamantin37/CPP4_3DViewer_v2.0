#ifndef CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_
#define CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_

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
#include <string>

#include "../backend/s21_auxiliary_modules.h"
#include "../controller/s21_controller.h"
#include "s21_command.h"
#include "qgifimage.h"
// #include "settingswindow.h"

namespace s21 {
class Facade {
 public:
  Facade() {
    view_ = new Qt3DExtras::Qt3DWindow();
    controller_ = new Controller();
  }
  ~Facade() {
    delete controller_;
    delete view_;
  }

  Object LoadObject(const QString &filename) {
    Object object_info;
    Command *command = new LoadObjectCommand(
        controller_, filename.toStdString(), &object_info);
    command->Execute();
    delete command;
    return object_info;
  }

  void ImageRender(const QString &filename, Qt3DExtras::Qt3DWindow *view) {
    Command *command = new SaveImageCommand(controller_, filename, view);
    command->Execute();
    delete command;
  }

  QLabel *UpdateView(const QString &filename, Object *object_info,
                     Qt3DRender::QMesh *mesh, Qt3DCore::QEntity *entity_object,
                     Qt3DCore::QTransform *transform, QVBoxLayout *layout) {
    QString file_info = QString("<b>File:</b> %1<br>").arg(filename);
    QString vertices_info =
        QString("<b>Number of vertices:</b> %1<br>")
            .arg(QString::number(object_info->num_of_vertices));
    QString polygons_info =
        QString("<b>Number of polygons:</b> %1")
            .arg(QString::number(object_info->num_of_polygons));
    QLabel *file_label = new QLabel(file_info + vertices_info + polygons_info);
    layout->addWidget(file_label);
    file_label->setMaximumHeight(60);
    const std::string filename_std = filename.toStdString();
    Command *command = new UpdateViewCommand(
        controller_, mesh, entity_object, transform, filename_std, object_info);
    command->Execute();
    delete command;
    return file_label;
  }

  void StartGifCreation(const QString &filename, int fps) {
    gif_file_name_ = filename;
    gif_image_ = new QGifImage();
    gif_image_->setDefaultDelay(1000 / fps);
  }

  void CaptureFrameForGif(Qt3DExtras::Qt3DWindow *view) {
    Command *command = new CreateGifCommand(controller_, gif_image_, view);
    command->Execute();
    delete command;
  }

  void FinishGifCreation() {
    if (gif_image_ != nullptr) {
      gif_image_->save(gif_file_name_);
      delete gif_image_;
      gif_image_ = nullptr;
    }
  }

  void ProjectionSettings(Qt3DRender::QCamera *camera_obj, short int type) {
    Command *command = nullptr;
    if (type == 0)
      command =
          new SetParallelProjectionCommand(controller_, camera_obj, view_);
    else
      command = new SetCentralProjectionCommand(controller_, camera_obj, view_);
    command->Execute();
    delete command;
  }

  void LineTypeSettings(Qt3DRender::QMesh *mesh, short int type) {
    Command *command = nullptr;
    command =
        (type == 0)
            ? new ChangeLineTypeCommand(controller_, mesh,
                                        Qt3DRender::QGeometryRenderer::Lines)
            : new ChangeLineTypeCommand(controller_, mesh,
                                        Qt3DRender::QGeometryRenderer::Points);
    command->Execute();
    delete command;
  }

  void LineColorSettings(QColor line_color, Qt3DCore::QEntity *object,
                         Qt3DExtras::QDiffuseSpecularMaterial *line_material) {
    Command *command =
        new LineColorCommand(controller_, object, line_color, line_material);
    command->Execute();
    delete command;
  }

  void BackgroundSettings(Qt3DExtras::Qt3DWindow *view, QColor color) {
    Command *command = new BackgroundColorCommand(controller_, view, color);
    command->Execute();
    delete command;
  }

 private:
  Qt3DExtras::Qt3DWindow *view_;
  Controller *controller_;
  QGifImage *gif_image_ = nullptr;
  QString gif_file_name_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_
