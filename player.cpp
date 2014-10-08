#include "player.hpp"
#include "ui_mainwindow.h"

#include <phonon/MediaSource>
#include <iostream>

Player::Player()
    : mPlayer{Phonon::Category::MusicCategory}
    , mCurrentStreamId{Streams::Stream::technobase} { }

void Player::setStream(int s) {
    mCurrentStreamId = s;
}

void Player::setVolume(float vol) {
    mPlayer.setVolume(vol);
}

void Player::start() {
    Phonon::MediaSource source{QUrl{Streams::getUrlFromStreamId(mCurrentStreamId).c_str()}};
    mPlayer.play(source);
    onStreamLoaded();
}

void Player::stop() {
    mPlayer.stop();
}

void Player::onStreamLoaded() {
    mUi->lbStreamStatus->setText(Streams::getUrlFromStreamId(mCurrentStreamId).c_str());
}
