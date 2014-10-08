#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QProcess>
#include <QTableWidgetItem>

#include <phonon/MediaSource>
#include <phonon/VideoPlayer>

#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
    , mUi{new Ui::MainWindow} {
    mUi->setupUi(this);
    // connect
    connect(mUi->pbManInfoRefresh, SIGNAL(clicked()), this, SLOT(startStreamInfoReload()));
    connect(&mInfoRealoadTimer, SIGNAL(timeout()), this, SLOT(startStreamInfoReload()));
    connect(&mInfoGrabber, SIGNAL(gotInfo()), this, SLOT(setupRadioTable()));

    // get info from the website
    startStreamInfoReload();

    // player
    mPlayer.setUi(mUi);
    on_hsVolme_valueChanged(50); // set default volume

    // reload timer
    mInfoRealoadTimer.start(1200000);
}

MainWindow::~MainWindow() {
    delete mUi;
}

void MainWindow::startStreamInfoReload() {
    mUi->lbStreamInfos->setText("Lade infos...");
    mInfoGrabber.grabStreamInfos();
}

void MainWindow::setupRadioTable() {
    const auto& infos(mInfoGrabber.getStreamInfos());

    // insert infos
    std::cout << "clear" << std::endl;
    for(auto row(0); row < 6; ++row) {
        for(auto col(0), infoIndex(5); col < 3; ++col, ++infoIndex) {
            QTableWidgetItem* item{nullptr};
            if(infoIndex < 7) item = new QTableWidgetItem{infos.at(row).at(infoIndex).c_str()};
            else item = new QTableWidgetItem{infos.at(row).at(StreamInfoIndex::numListeners).c_str()};
            mUi->twStreams->setItem(row, col, item);
        }
    }

    mUi->lbStreamInfos->setText("Infos geladen");
}

// events
void MainWindow::on_pbStart_clicked() {
    if(mUi->twStreams->currentRow() < 0) {
        QMessageBox::critical(this, "Fehler", "Kein Radio ausgewählt!");
        return;
    }

    mPlayer.setStream(mUi->twStreams->currentRow());
    mPlayer.start();
}

void MainWindow::on_pbStop_clicked() {
    mPlayer.stop();
}

void MainWindow::on_hsVolme_valueChanged(int value) {
    mPlayer.setVolume(static_cast<float>(value) / 100.f);
    mUi->lbVolume->setText(QString{"%1"}.arg(value));
}
