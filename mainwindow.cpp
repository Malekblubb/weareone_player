#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QProcess>

#include <iostream>
#include <cstdlib>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , mUi{new Ui::MainWindow} {
    mUi->setupUi(this);
}

MainWindow::~MainWindow() {
    delete mUi;
}

void MainWindow::on_pushButton_clicked() {
    QStringList args;
    args.append("http://listen.housetime.fm/tunein-dsl-ram");
    mProcess.start("ffplay", args);
}

void MainWindow::on_pushButton_2_clicked() {
    mProcess.terminate();
}
