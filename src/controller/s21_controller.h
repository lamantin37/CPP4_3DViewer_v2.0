#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_

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

namespace s21 {
class Controller {
 public:
  Controller(Qt3DExtras::Qt3DWindow *view);
  ~Controller();

  void StartParsing(const std::string &filename, Object &object_info);
  Qt3DExtras::Qt3DWindow *getView();

 private:
  AuxiliaryModules *auxiliary_modules;
  Qt3DExtras::Qt3DWindow *view_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_S21_CONTROLLER_H_
