#include "infograbber.h"

#include <QWebFrame>

#include <iostream>

InfoGrabber::InfoGrabber()
    : QWidget{nullptr} {
    connect(&mPage, SIGNAL(loadFinished(bool)), this, SLOT(siteLoaded(bool)));
}

bool InfoGrabber::grabStreamInfos() {
    openSite();
    return true;
}

void InfoGrabber::openSite() {
    mPage.mainFrame()->load({"http://www.weareone.fm/"});
}


void InfoGrabber::parse() {
    static const std::vector<Streams::Stream> streamOrder {
                Streams::Stream::technobase,
                Streams::Stream::housetime,
                Streams::Stream::hardbase,
                Streams::Stream::trancebase,
                Streams::Stream::coretime,
                Streams::Stream::clubtime
    };

    std::cout << mWorkData.length() << std::endl;

    for(auto i(0), streamIndex(0);; ++i) {
        auto begin(mWorkData.find('\n'));
        auto end(mWorkData.find('\n', begin + 1));
        if(begin == std::string::npos || end == std::string::npos)
            break;

        auto str(mWorkData.substr(begin, end));
        if(i > 4) mInfos[streamOrder[streamIndex]][i] = str;
        if(str.empty()) i = 0;
        if(i == 8) { i = 0; ++streamIndex;}
        mWorkData.erase(begin, end);
    }

    emit gotInfo();
}

void InfoGrabber::siteLoaded(bool ok) {
    if(!ok) {
        std::cout << "Siteloaded returned false" << std::endl;
        return;
    }

    mWorkData = mPage.mainFrame()->toPlainText().toStdString();
    parse();
}
