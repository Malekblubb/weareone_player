#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <mlk/containers/container_utl.h>

#include <QMessageBox>
#include <QProcess>
#include <QTableWidgetItem>

#include <phonon/MediaSource>
#include <phonon/VideoPlayer>

#include <iostream>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow{parent}, mUi{new Ui::MainWindow}
{
    mUi->setupUi(this);
    // connect
	/*connect(mUi->pbManInfoRefresh, SIGNAL(clicked()), this,
									SLOT(startStreamInfoReload()));*/ // TODO: implement this with the new weareone.fm site
	connect(mUi->pbRefreshTracklist, SIGNAL(clicked()), this,
			SLOT(startTracklistReload()));
	connect(&mInfoRealoadTimer, SIGNAL(timeout()), this,
			SLOT(startStreamInfoReload()));
    connect(&mInfoGrabber, SIGNAL(gotInfo()), this, SLOT(setupRadioTable()));
	connect(&mInfoGrabber, SIGNAL(gotTracklist()), this,
			SLOT(setupTracklistTable()));

    // get info from the website
	// startStreamInfoReload(); // TODO
	startTracklistReload();

    // player
    mPlayer.setUi(mUi);
	on_hsVolme_valueChanged(50);// set default volume

    // reload timer
	// mInfoRealoadTimer.start(600000); // TODO
}

MainWindow::~MainWindow() { delete mUi; }

void MainWindow::startStreamInfoReload()
{
    mUi->lbStreamInfos->setText("Lade infos...");
    mInfoGrabber.grabStreamInfos();
}

void MainWindow::startTracklistReload()
{
    mInfoGrabber.grabTracklist(mUi->twStreams->currentRow());
}

void MainWindow::setupRadioTable()
{
    const auto& infos(mInfoGrabber.getStreamInfos());

    // insert infos
	for(auto row(0); row < 6; ++row)
	{
		for(auto col(0), infoIndex(5); col < 3; ++col, ++infoIndex)
		{
            QTableWidgetItem* item{nullptr};
			if(infoIndex < 7)
				item =
					new QTableWidgetItem{infos.at(row).at(infoIndex).c_str()};
			else
				item = new QTableWidgetItem{
					infos.at(row).at(StreamInfoIndex::numListeners).c_str()};
            mUi->twStreams->setItem(row, col, item);
        }
    }

    mUi->lbStreamInfos->setText("Infos geladen");
}

void MainWindow::setupTracklistTable()
{
    const auto& tracklist(mInfoGrabber.getTracklist());

    mUi->twTracklist->clearContents();
    mUi->twTracklist->setRowCount(0);
    mUi->twTracklist->setRowCount(tracklist.size());
	for(auto row(0); row < static_cast<int>(tracklist.size()); ++row)
	{
		for(auto col(0); col < 3; ++col)
		{
			if(!mlk::cnt::exists_map_first(col, tracklist.at(row))) continue;
			auto* item =
				new QTableWidgetItem{tracklist.at(row).at(col).c_str()};
            mUi->twTracklist->setItem(row, col, item);
        }
	}
}

// events
void MainWindow::on_pbStart_clicked()
{
	if(mUi->twStreams->currentRow() < 0)
	{
        QMessageBox::critical(this, "Fehler", "Kein Radio ausgewählt!");
        return;
    }

    mPlayer.setStream(mUi->twStreams->currentRow());
    mPlayer.start();
}

void MainWindow::on_pbStop_clicked() { mPlayer.stop(); }

void MainWindow::on_hsVolme_valueChanged(int value)
{
    mPlayer.setVolume(static_cast<float>(value) / 100.f);
    mUi->lbVolume->setText(QString{"%1"}.arg(value));
}

void MainWindow::on_pbManInfoRefresh_clicked()
{
	QMessageBox::warning(this, "Fehler",
						 "Diese Funktion ist nicht implementiert!");
}
