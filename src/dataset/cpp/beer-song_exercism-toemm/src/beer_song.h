#if !defined(BEER_SONG_H)
#define BEER_SONG_H

#include <string>

namespace beer_song {

std::string verse(int i);
std::string sing(int begin, int ending=0);

}  // namespace beer_song

#endif  // BEER_SONG_H