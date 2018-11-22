#include "player.hpp"
#include "ui_mainwindow.h"

#include <iostream>
#include <phonon/MediaSource>

Player::Player()
	: mPlayer{Phonon::Category::MusicCategory},
	  mCurrentStreamId{Streams::Stream::technobase}
{
}

Player::~Player() { mPlayer.stop(); }

void Player::setStream(int s) { mCurrentStreamId = s; }

void Player::setVolume(float vol) { mPlayer.setVolume(vol); }

void Player::start()
{
    Phonon::MediaSource source{QUrl{buildStreamUrl().c_str()}};
    mPlayer.play(source);
    onStreamLoaded();
}

void Player::stop() { mPlayer.stop(); }

void Player::onStreamLoaded()
{
	mUi->lbStreamStatus->setText(
		Streams::getUrlFromStreamId(mCurrentStreamId).c_str());
}

std::string Player::buildStreamUrl()
{
    auto webUrl(Streams::getUrlFromStreamId(mCurrentStreamId));
    return "http://listen." + webUrl + "tunein-dsl-ram";
}
