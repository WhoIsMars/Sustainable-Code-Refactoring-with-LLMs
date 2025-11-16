#include "atbash_cipher.h"
#include <algorithm>

std::string atbash_cipher::transform(const std::string& text, bool add_space) {
  std::string cipher;
  cipher.reserve(text.length() + (add_space ? text.length() / 4 : 0));
  
  int count = 0;
  for (char c : text) {
    if (c == ' ' || (c >= 33 && c <= 47) || (c >= 58 && c <= 64) || 
        (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) continue;
    
    if (add_space && count > 0 && (count % 5 == 0)) {
      cipher += ' ';
    }
    
    if (c >= '0' && c <= '9') {
      cipher += c;
    } else {
      char lower_c = (c >= 'A' && c <= 'Z') ? c + 32 : c;
      cipher += 'a' + 'z' - lower_c;
    }
    ++count;
  }
  return cipher;
}

std::string atbash_cipher::encode(const std::string& text) {
  return transform(text, true);
}

std::string atbash_cipher::decode(const std::string& text) {
  return transform(text, false);
}