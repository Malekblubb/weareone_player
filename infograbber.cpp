#include "infograbber.hpp"

#include <mlk/log/log.h>
#include <mlk/tools/stl_string_utl.h>

#include <QWebFrame>

#include <iostream>

InfoGrabber::InfoGrabber() : QWidget{nullptr}
{
    connect(&mPage, SIGNAL(loadFinished(bool)), this, SLOT(siteLoaded(bool)));
	connect(&mTracklistPage, SIGNAL(loadFinished(bool)), this,
			SLOT(tracklistSiteLoaded(bool)));
}

void InfoGrabber::grabStreamInfos() { openSite(); }

void InfoGrabber::grabTracklist(int streamId) { openTracklistSite(streamId); }

void InfoGrabber::openSite()
{
    mPage.mainFrame()->load({"http://www.weareone.fm/"});
}

void InfoGrabber::parse()
{
	static const std::vector<Streams::Stream> streamOrder{
		Streams::Stream::technobase, Streams::Stream::housetime,
		Streams::Stream::hardbase,   Streams::Stream::trancebase,
		Streams::Stream::coretime,   Streams::Stream::clubtime};

	for(auto i(0), streamIndex(0);; ++i)
	{
        auto begin(mWorkData.find('\n'));
        auto end(mWorkData.find('\n', begin + 1));
		if(begin == std::string::npos || end == std::string::npos) break;

        auto str(mWorkData.substr(begin, end));
        if(i > 4) mInfos[streamOrder[streamIndex]][i] = str;
        if(str.empty()) i = 0;
		if(i == 8)
		{
			i = 0;
			++streamIndex;
		}
        mWorkData.erase(begin, end);
    }

    emit gotInfo();
}

void InfoGrabber::openTracklistSite(int streamId)
{
	mTracklistPage.mainFrame()->load(QString{"http://www.%1tracklist/"}.arg(
		Streams::getUrlFromStreamId(streamId).c_str()));
}

void InfoGrabber::parseTracklist()
{
    auto str(mTracklistData.str());
    str.erase(0, str.find("Tracks"));
    mTracklistData.str(str);

    // prepare storage
    mlk::cnt::free_vec(mTracklist);
    mTracklist.emplace_back();

    std::string line;
    auto entryIndex(0), itemIndex(0);
    auto end(false), show(true);
	while(std::getline(mTracklistData, line))
	{
		if(line.empty() || line == "Tracks" ||
		   (mlk::stl_string::contains("Charts", line) && line.length() == 10))
            continue;
		if(line == "Bookmarks") break;

		if(itemIndex == 2)
		{
			if(!mlk::stl_string::contains("Show:", line))
			{
                mTracklist.emplace_back();
                ++entryIndex;
                itemIndex = 0;
                show = false;
			}
			else
				show = true;
            end = true;
        }

        mTracklist[entryIndex][itemIndex] = line;

		if(end)
		{
            end = false;
			if(show)
			{
                mTracklist.emplace_back();
                ++entryIndex;
                itemIndex = -1;
            }
        }

        ++itemIndex;
    }

    emit gotTracklist();
}

void InfoGrabber::siteLoaded(bool ok)
{
	if(!ok)
	{
        mlk::lout("InfoGrabber") << "Failed to load http://www.weareone.fm/";
        return;
    }

    mWorkData = mPage.mainFrame()->toPlainText().toStdString();
    parse();
}

void InfoGrabber::tracklistSiteLoaded(bool ok)
{
	if(!ok)
	{
        mlk::lout("InfoGrabber") << "Failed to load tracklistsite";
        return;
    }

    mTracklistData << mTracklistPage.mainFrame()->toPlainText().toStdString();
    parseTracklist();
}
