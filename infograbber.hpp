#ifndef INFOGRABBER_H
#define INFOGRABBER_H

#include "streams.hpp"

#include <QWebPage>

#include <map>
#include <sstream>

enum StreamInfoIndex : int
{
    moderator = 5,
    show,
    musicStyle,
    numListeners
};

enum TracklistItem : int
{
	trackName = 0,
    timeAndMod,
    tracklistShow
};

class InfoGrabber : public QWidget
{
    Q_OBJECT

    std::map<int, std::map<int, std::string>> mInfos;
    std::vector<std::map<int, std::string>> mTracklist;
    QWebPage mPage, mTracklistPage;
    std::string mWorkData;
    std::stringstream mTracklistData;
    bool mSiteAvailable{false};

public:
    InfoGrabber();
	virtual ~InfoGrabber() {}

    const auto& getStreamInfos() const noexcept { return mInfos; }
    const auto& getTracklist() const noexcept { return mTracklist; }

public slots:
    void grabStreamInfos();
    void grabTracklist(int streamId);

signals:
    void gotInfo();
    void gotTracklist();

private:
    void openSite();
    void parse();

    void openTracklistSite(int streamId);
    void parseTracklist();

private slots:
    void siteLoaded(bool ok);
    void tracklistSiteLoaded(bool ok);
};

#endif// INFOGRABBER_H
