#ifndef CPP4_3DVIEWER_V2_0_1_FRONTEND_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_0_1_FRONTEND_MAINWINDOW_H_

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
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void OpenObjectFile(QLineEdit *lineEdit, QPushButton *button);
  void UpdateView(QString &filename);
  void Settings();
  void ObjectInfo(const Object &object, const char *filename);
  void ImageRender();
  void CreateGif();
  void CaptureFrameForGif();

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
  bool settings_flag_ = false;
  int frame_count_;
  int fps_ = 15;
  int gif_time_ = 5;
  SettingsWindow *settings_win_;
  Object object_info_;
  Qt3DCore::QEntity *parent_win_ = nullptr;  // корневое окно
  Qt3DCore::QEntity *entity_object_ = nullptr;
  Qt3DCore::QTransform *transform_ = nullptr;
  Qt3DRender::QCamera *camera_obj_ = nullptr;  // камера
  Qt3DRender::QMesh *mesh_ = nullptr;
  Qt3DExtras::Qt3DWindow *view_;
  Qt3DExtras::QDiffuseSpecularMaterial *line_material_;
  QLabel *file_label_ = nullptr;
  QLabel *vertices_label_ = nullptr;
  QLabel *polygons_label_ = nullptr;
  QString previous_model_;
  QString gif_file_name_;
  QVBoxLayout *layout_ = nullptr;
  QPushButton *settings_button_ = nullptr;
  QWidget *widget_;
  QSettings re_settings_;
  QTimer *gif_timer_;
  QGifImage gif_image_;
};
#endif  // CPP4_3DVIEWER_V2_0_1_FRONTEND_MAINWINDOW_H_
