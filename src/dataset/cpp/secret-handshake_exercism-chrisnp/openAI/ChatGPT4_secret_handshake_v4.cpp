#include "secret_handshake.h"
#include <vector>
#include <string>

using namespace std;

vector<string> secret_handshake::commands(unsigned int code) {
    vector<string> handshake;
    handshake.reserve(4); // Reserve space for up to 4 elements to avoid reallocations

    if (code & wink) handshake.emplace_back("wink");
    if (code & double_blink) handshake.emplace_back("double blink");
    if (code & close_eyes) handshake.emplace_back("close your eyes");
    if (code & jump) handshake.emplace_back("jump");
    if (code & mask_16) reverse(handshake.begin(), handshake.end());

    return handshake;
}