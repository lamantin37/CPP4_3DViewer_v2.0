#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QFileDialog>
#include <QImageWriter>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QScreen>

#include "settingswindow.h"
#include "../controller/s21_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void open_object_file(Qt3DExtras::Qt3DWindow *, QLineEdit *,
                        QPushButton *);                          //
  void object_info(const Object &object, const char *filename);  //
  void settings(Qt3DExtras::Qt3DWindow *);                       //

  void start_parsing(const std::string &filename, Object &objInfo);
  void image_render();
  void UpdateView(QString& filename);

 private:
  Ui::MainWindow *ui;
  Controller *controller;
  Qt3DCore::QEntity *parentWin = nullptr;    // корневое окно
  Qt3DRender::QCamera *cameraObj = nullptr;  // камера
  Qt3DCore::QEntity *sceneLoader = nullptr;  // базовая сущность
  Qt3DRender::QSceneLoader *loader = nullptr;  // для загрузки файлов
  Qt3DRender::QMesh *mesh = nullptr;
  Qt3DCore::QEntity *object = nullptr;
  Qt3DCore::QTransform *transform = nullptr;
  QVBoxLayout *layout = nullptr;
  QPushButton *settingsButton = nullptr;
  Qt3DRender::QRenderCapture *capture;
  SettingsWindow *settingsWin;
  Qt3DRender::QRenderCaptureReply *captureReply;
  Qt3DExtras::Qt3DWindow *view;
  QWidget *widget;
  QSettings re_settings;
  Qt3DExtras::QDiffuseSpecularMaterial *line_material;
  Object objInfo;
  QLabel *fileLabel = nullptr;
  QLabel *verticesLabel = nullptr;
  QLabel *polygonsLabel = nullptr;
  QString prevModel;
  bool settings_flag = false;
};
#endif  // MAINWINDOW_H
