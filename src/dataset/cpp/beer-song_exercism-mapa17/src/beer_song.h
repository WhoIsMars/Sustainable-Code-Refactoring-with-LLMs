#if !defined(BEER_SONG_H)
#define BEER_SONG_H

#include <string>
#include <boost/format.hpp>

namespace beer_song {

    std::string sing(int nbottels_start, int nbottels_stop=0);
    std::string verse(int nbottels);


    std::string p1(int nbottels);
    std::string p2(int nbottels);
}  // namespace beer_song

#endif // BEER_SONG_H