#ifndef INFOGRABBER_H
#define INFOGRABBER_H

#include "streams.hpp"

#include <QWebPage>

#include <map>

enum StreamInfoIndex : int{
    moderator = 5,
    show,
    musicStyle,
    numListeners
};

class InfoGrabber : public QWidget {
    Q_OBJECT

    std::map<int, std::map<int, std::string>> mInfos;
    QWebPage mPage;
    std::string mWorkData;
    bool mSiteAvailable{false};

public:
    InfoGrabber();
    virtual ~InfoGrabber() { }

    const auto& getStreamInfos() const noexcept { return mInfos; }

public slots:
    bool grabStreamInfos();

signals:
    void gotInfo();

private:
    void openSite();
    void parse();

private slots:
    void siteLoaded(bool ok);
};

#endif // INFOGRABBER_H
