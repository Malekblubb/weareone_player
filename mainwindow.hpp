#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <infograbber.hpp>
#include <player.hpp>

#include <QMainWindow>
#include <QProcess>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    Ui::MainWindow *mUi;
    InfoGrabber mInfoGrabber;
    Player mPlayer;
    QTimer mInfoRealoadTimer;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void startStreamInfoReload();
    void startTracklistReload();
    void setupRadioTable();
    void setupTracklistTable();

    void on_pbStart_clicked();
    void on_pbStop_clicked();
    void on_hsVolme_valueChanged(int value);
};

#endif // MAINWINDOW_H
