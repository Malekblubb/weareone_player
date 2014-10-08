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
    case Stream::technobase: return "http://listen.technobase.fm/tunein-dsl-ram";
        break;
    case Stream::hardbase: return "http://listen.hardbase.fm/tunein-dsl-ram";
        break;
    case Stream::trancebase: return "http://listen.trancebase.fm/tunein-dsl-ram";
        break;
    case Stream::coretime: return "http://listen.coretime.fm/tunein-dsl-ram";
        break;
    case Stream::clubtime: return "http://listen.clubtime.fm/tunein-dsl-ram";
        break;
    case Stream::housetime: return "http://listen.housetime.fm/tunein-dsl-ram";
        break;
    default: break;
    }
    return "";
}
}

#endif // STREAMS_HPP
