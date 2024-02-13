#ifndef CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_COMMAND_H_
#define CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_COMMAND_H_

#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QPushButton>
#include <QScreen>
#include <QWidget>
#include <Qt3DExtras>
#include <Qt3DRender/QRenderCapture>
#include <string>

#include "../backend/auxiliary_modules.h"
#include "../controller/s21_controller.h"
#include "qgifimage.h"

namespace s21 {

class Command {
 public:
  Command(Controller *controller) : controller_(controller) {}
  virtual ~Command() = default;
  virtual void Execute() = 0;

 protected:
  Controller *controller_;
};

class LoadObjectCommand : public Command {
 public:
  LoadObjectCommand(Controller *controller, std::string filename,
                    Object *object_info)
      : Command(controller), filename_(filename), object_info_(object_info) {}
  void Execute() override {
    controller_->StartParsing(filename_, *object_info_);
  }

 private:
  std::string filename_;
  Object *object_info_;
};

class SaveImageCommand : public Command {
 public:
  SaveImageCommand(Controller *controller, QString filename,
                   Qt3DExtras::Qt3DWindow *view)
      : Command(controller), filename_(filename), view_(view) {}
  void Execute() override {
    QScreen *screen = view_->screen();
    QPixmap screenshot = screen->grabWindow(view_->winId());
    if (!filename_.isEmpty()) screenshot.save(filename_);
  }

 private:
  QString filename_;
  Qt3DExtras::Qt3DWindow *view_;
};

class CreateGifCommand : public Command {
 public:
  CreateGifCommand(Controller *controller, QGifImage *gif_image,
                   Qt3DExtras::Qt3DWindow *view)
      : Command(controller), gif_image_(gif_image), view_(view) {}

  void Execute() override {
    QPixmap screenshot = view_->screen()->grabWindow(view_->winId());
    gif_image_->addFrame(screenshot.toImage());
  }

 private:
  QGifImage *gif_image_;
  Qt3DExtras::Qt3DWindow *view_;
};

class UpdateViewCommand : public Command {
 public:
  UpdateViewCommand(Controller *controller, Qt3DRender::QMesh *mesh,
                    Qt3DCore::QEntity *entity_object,
                    Qt3DCore::QTransform *transform,
                    const std::string &filename, Object *object_info)
      : Command(controller),
        mesh_(mesh),
        entity_object_(entity_object),
        transform_(transform),
        filename_(filename),
        object_info_(object_info) {}
  void Execute() override {
    mesh_->setSource(QUrl::fromLocalFile(QString::fromStdString(filename_)));
    mesh_->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    entity_object_->addComponent(mesh_);
    entity_object_->addComponent(transform_);
    controller_->StartParsing(filename_, *object_info_);
  }

 private:
  Qt3DRender::QMesh *mesh_;
  Qt3DCore::QEntity *entity_object_;
  Qt3DCore::QTransform *transform_;
  std::string filename_;
  Object *object_info_;
};

class SettingsCommand : public Command {
 public:
  SettingsCommand(Controller *controller) : Command(controller) {}
  virtual ~SettingsCommand() = default;
  virtual void Execute() = 0;
};

class BackgroundColorCommand : public SettingsCommand {
 public:
  BackgroundColorCommand(Controller *controller, Qt3DExtras::Qt3DWindow *view,
                         const QColor &color)
      : SettingsCommand(controller), view_(view), color_(color) {}

  void Execute() override { view_->defaultFrameGraph()->setClearColor(color_); }

 private:
  Qt3DExtras::Qt3DWindow *view_;
  QColor color_;
};

class LineColorCommand : public SettingsCommand {
 public:
  LineColorCommand(Controller *controller, Qt3DCore::QEntity *object,
                   QColor &line_color,
                   Qt3DExtras::QDiffuseSpecularMaterial *line_material)
      : SettingsCommand(controller),
        object_(object),
        line_color_(line_color),
        line_material_(line_material) {}

  void Execute() override {
    line_material_->setAmbient(line_color_);
    object_->addComponent(line_material_);
  }

 private:
  Qt3DCore::QEntity *object_;
  QColor line_color_;
  Qt3DExtras::QDiffuseSpecularMaterial *line_material_;
};

class ChangeLineTypeCommand : public SettingsCommand {
 public:
  ChangeLineTypeCommand(Controller *controller, Qt3DRender::QMesh *mesh,
                        Qt3DRender::QGeometryRenderer::PrimitiveType type)
      : SettingsCommand(controller), mesh_(mesh), type_(type) {}

  void Execute() override { mesh_->setPrimitiveType(type_); }

 private:
  Qt3DRender::QMesh *mesh_;
  Qt3DRender::QGeometryRenderer::PrimitiveType type_;
};

class SetProjectionCommand : public SettingsCommand {
 public:
  SetProjectionCommand(Controller *controller, Qt3DRender::QCamera *camera_obj,
                       Qt3DExtras::Qt3DWindow *view)
      : SettingsCommand(controller), camera_obj_(camera_obj), view_(view) {}

 protected:
  Qt3DRender::QCamera *camera_obj_;
  Qt3DExtras::Qt3DWindow *view_;
};

class SetParallelProjectionCommand : public SetProjectionCommand {
 public:
  SetParallelProjectionCommand(Controller *controller,
                               Qt3DRender::QCamera *camera_obj,
                               Qt3DExtras::Qt3DWindow *view)
      : SetProjectionCommand(controller, camera_obj, view) {}

  void Execute() override {
    float aspect_ratio = float(view_->width()) / view_->height();
    camera_obj_->lens()->setOrthographicProjection(
        -aspect_ratio * 2.0f, aspect_ratio * 2.0f, -2.0f, 2.0f, 0.1f, 10000.0f);
    camera_obj_->setPosition(QVector3D(0, 0, 20));
    // camera_obj->setPosition(QVector3D(0, 20, 0));
    // camera_obj->setPosition(QVector3D(20, 0, 0));
    camera_obj_->setViewCenter(QVector3D(0, 0, 0));
    camera_obj_->setUpVector(QVector3D(0, 1, 0));
  }
};

class SetCentralProjectionCommand : public SetProjectionCommand {
 public:
  SetCentralProjectionCommand(Controller *controller,
                              Qt3DRender::QCamera *camera_obj,
                              Qt3DExtras::Qt3DWindow *view)
      : SetProjectionCommand(controller, camera_obj, view) {}

  void Execute() override {
    float aspect_ratio = float(view_->width()) / view_->height();
    camera_obj_->lens()->setPerspectiveProjection(45.0f, aspect_ratio, 0.1f,
                                                  10000.0f);
    camera_obj_->setPosition(QVector3D(0, 2, 0));
    camera_obj_->setViewCenter(QVector3D(1, 1, 0));
    camera_obj_->setUpVector(QVector3D(1, 0, 0));
  }
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_FRONTEND_S21_COMMAND_H_
