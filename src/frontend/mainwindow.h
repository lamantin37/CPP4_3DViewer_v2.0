#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QFileDialog>
#include <QImageWriter>
#include <QLineEdit>
#include <QMainWindow>
#include <QMesh>
#include <QScreen>

#include "../controller/s21_controller.h"
#include "qgifimage.h"
#include "settingswindow.h"

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
  void OpenObjectFile(Qt3DExtras::Qt3DWindow *view, QLineEdit *lineEdit,
                      QPushButton *button);
  void ObjectInfo(const Object &object, const char *filename);
  void Settings(Qt3DExtras::Qt3DWindow *view);

  void ImageRender();
  void UpdateView(QString &filename);

  void CreateGif();
  void CaptureFrameForGif();

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
  Qt3DCore::QEntity *parent_win_ = nullptr;    // корневое окно
  Qt3DRender::QCamera *camera_obj_ = nullptr;  // камера
  Qt3DRender::QMesh *mesh_ = nullptr;
  Qt3DCore::QEntity *entity_object_ = nullptr;
  Qt3DCore::QTransform *transform_ = nullptr;
  QVBoxLayout *layout_ = nullptr;
  QPushButton *settings_button_ = nullptr;
  SettingsWindow *settings_win_;
  Qt3DExtras::Qt3DWindow *view_;
  QWidget *widget_;
  QSettings re_settings_;
  Qt3DExtras::QDiffuseSpecularMaterial *line_material_;
  Object object_info_;
  QLabel *file_label_ = nullptr;
  QLabel *vertices_label_ = nullptr;
  QLabel *polygons_label_ = nullptr;
  QString previous_model_;
  bool settings_flag_ = false;

  QTimer *gif_timer_;
  QGifImage gif_image_;
  int frame_count_;
  QString gif_file_name_;
  int fps_ = 15;
  int gif_time_ = 5;
};
#endif  // MAINWINDOW_H
