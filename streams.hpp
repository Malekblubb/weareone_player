#ifndef STREAMS_HPP
#define STREAMS_HPP

#include <string>

namespace Streams
{
	enum Stream : int
	{
		technobase = 0,
		hardbase,
		trancebase,
		coretime,
		clubtime,
		housetime
	};

	inline std::string getUrlFromStreamId(int s)
	{
		std::string ret = "";
		switch(s)
		{
			case Stream::technobase:
				ret = "technobase.fm/";
				break;
			case Stream::hardbase:
				ret = "hardbase.fm/";
				break;
			case Stream::trancebase:
				ret = "trancebase.fm/";
				break;
			case Stream::coretime:
				ret = "coretime.fm/";
				break;
			case Stream::clubtime:
				ret = "clubtime.fm/";
				break;
			case Stream::housetime:
				ret = "housetime.fm/";
				break;
			default:
				break;
		}
		return ret;
	}
}// namespace Streams

#endif// STREAMS_HPP
