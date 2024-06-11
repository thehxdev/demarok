/**
 * Base64 implementation inspired by https://josefsson.org/base-encoding/
 */

#include <string>
#include <sstream>
#include "types.hpp"
#include "base64.hpp"


#define BASE64_LENGTH(inlen) ((((inlen) + 2) / 3) * 4)

const static std::string base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
const static std::string safe_base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};


static inline __attribute__((always_inline))
size_t base64_char_idx(const std::string charset, char ch) {
    return charset.find(ch);
}

namespace demarok {

static inline __attribute__((always_inline))
ubyte to_ubyte(byte b) {
    return ((ubyte)b);
}


std::string base64::encode(const char *in, size_t inlen, int mode) {
    std::stringstream s;
    size_t outlen = 1 + BASE64_LENGTH(inlen);
    const char padd_char = (mode & BS64Mode::NO_PADDING) ? '\0' : '=';
    const std::string charset = (mode & BS64Mode::URL_SAFE) ? safe_base64_chars : base64_chars;

    while (inlen && outlen) {
        // first 6 bit of 24 bit block
        s << (charset[(to_ubyte(in[0]) >> 2) & 0x3f]);
        if ((outlen -= 1) == 0)
            break;

        // second 6 bit
        s << (charset[(((to_ubyte(in[0])) << 4)
                        | ((inlen -= 1) ? (to_ubyte(in[1]) >> 4) : 0))
                        & 0x3f]);
        if ((outlen -= 1) == 0)
            break;

        // third 6 bit
        s << (((inlen)
            ? charset[(((to_ubyte(in[1]) << 2))
                        | ((inlen -= 1) ? (to_ubyte(in[2]) >> 6) : 0))
                        & 0x3f]
            : padd_char));
        if ((outlen -= 1) == 0)
            break;

        // fourth 6 bit
        s << ((inlen) ? (charset[(to_ubyte(in[2])) & 0x3f]) : padd_char);
        if ((outlen -= 1) == 0)
            break;

        if (inlen)
            inlen -= 1;
        if (inlen)
            in += 3;
    }

    if (outlen)
        s << '\0';

    return s.str();
}


std::string base64::decode(std::string in, size_t inlen, int mode) {
    size_t idx1, idx2, idx3, idx4;
    std::stringstream buff;
    const std::string charset = (mode & BS64Mode::URL_SAFE) ? safe_base64_chars : base64_chars;

    for (size_t i = 0; i < inlen; i += 4) {
        idx1 = base64_char_idx(charset, in[i]);
        if (idx1 == charset.npos)
            break;

        idx2 = ((i+1) >= inlen) ? 0 : base64_char_idx(charset, in[i+1]);
        if (idx2 == charset.npos)
            break;

        buff << ((char)((((ubyte)idx1 & 0x3f) << 2) | (((ubyte)idx2 & 0x3f) >> 4)));

        idx3 = ((i+2) >= inlen) ? 0 : base64_char_idx(charset, in[i+2]);
        if (idx3 == charset.npos)
            break;

        buff << ((char)((((ubyte)idx2 & 0x3f) << 4) | (((ubyte)idx3 & 0x3f) >> 2)));

        idx4 = ((i+3) >= inlen) ? 0 : base64_char_idx(charset, in[i+3]);
        if (idx4 == charset.npos)
            break;

        buff << ((char)((((ubyte)idx3 & 0x3f) << 6) | ((ubyte)idx4 & 0x3f)));
    }

    return buff.str();
}

}// namespace demarok
