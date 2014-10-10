#ifndef STREAMS_HPP
#define STREAMS_HPP

#include <string>

namespace Streams {
enum Stream : int {
    technobase = 0,
    hardbase,
    trancebase,
    coretime,
    clubtime,
    housetime
};

inline std::string getUrlFromStreamId(int s) {
    switch(s) {
    case Stream::technobase: return "technobase.fm/";
        break;
    case Stream::hardbase: return "hardbase.fm/";
        break;
    case Stream::trancebase: return "trancebase.fm/";
        break;
    case Stream::coretime: return "coretime.fm/";
        break;
    case Stream::clubtime: return "clubtime.fm/";
        break;
    case Stream::housetime: return "housetime.fm/";
        break;
    default: break;
    }
    return "";
}
}

#endif // STREAMS_HPP
