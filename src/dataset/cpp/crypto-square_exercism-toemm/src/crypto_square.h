#if !defined(CRYPTO_SQUARE_H)
#define CRYPTO_SQUARE_H

#include <string>

namespace crypto_square {

using namespace std;

class crypto_square {

    public:
    crypto_square(string msg);
    string normalized_cipher_text();

    private:
    string _msg;

};

crypto_square cipher(string msg);


}  // namespace crypto_square

#endif  // CRYPTO_SQUARE_H