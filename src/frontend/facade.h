#ifndef CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_
#define CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_

#include <string>

#include "../backend/auxiliary_modules.h"
#include "../controller/s21_controller.h"
#include "command.h"
#include "qgifimage.h"
#include "settingswindow.h"

namespace s21 {
class Facade {
 public:
  Facade() {
    view_ = new Qt3DExtras::Qt3DWindow();
    controller_ = new Controller();
    settings_window_ = new SettingsWindow(nullptr, controller_);
  }
  ~Facade() {
    delete settings_window_;
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
                     Qt3DCore::QTransform *transform, QSettings *settings,
                     Qt3DExtras::Qt3DWindow *view,
                     Qt3DExtras::QDiffuseSpecularMaterial *line_material,
                     QVBoxLayout *layout, Qt3DRender::QCamera *camera_obj) {
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
    settings_window_->LoadSettings(settings, camera_obj, mesh, view,
                                   entity_object, line_material);
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

 private:
  Qt3DExtras::Qt3DWindow *view_;
  Controller *controller_;
  SettingsWindow *settings_window_;
  QGifImage *gif_image_ = nullptr;
  QString gif_file_name_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_FACADE_H_
