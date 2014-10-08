#ifndef PLAYER_H
#define PLAYER_H

#include "streams.hpp"

#include <phonon/VideoPlayer>

namespace Ui {
class MainWindow;
}

class Player{
    Phonon::VideoPlayer mPlayer;
    int mCurrentStreamId;

    Ui::MainWindow* mUi;

public:
    Player();

    void setStream(int s);
    void setVolume(float vol);
    void setUi(Ui::MainWindow* ui) { mUi = ui; }

    void start();
    void stop();

private:
    void onStreamLoaded();
};

#endif // PLAYER_H
