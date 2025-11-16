#include "secret_handshake.h"
#include <algorithm>

using namespace std;

vector<string> secret_handshake::commands(unsigned int code) {
    
    auto handshake = vector<string>{};

    if (code & wink) 
        handshake.insert(handshake.end(), "wink");
    if (code & double_blink) 
        handshake.insert(handshake.end(), "double blink");
    if (code & close_eyes) 
        handshake.insert(handshake.end(), "close your eyes");
    if (code & jump) 
        handshake.insert(handshake.end(), "jump");
    if (code & mask_16) 
        reverse(handshake.begin(), handshake.end());

    return handshake;
}
