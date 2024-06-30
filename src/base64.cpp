/**
 * Base64 encoder and decoder for C++
 * Author: Hossein Khosravi
 * Encoder inspired by https://josefsson.org/base-encoding/
 *
 *
 * MIT License
 *
 * Copyright (c) Hossein Khosravi (@thehxdev)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * Includes
 */

#include <string>
#include <sstream>
#include "base64.hpp"



/**
 * Types
 */

typedef char byte;
typedef unsigned char ubyte;



/**
 * Constants
 */

const static std::string base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
const static std::string safe_base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"};



/**
 * Private API
 */

static inline __attribute__((always_inline))
size_t base64_char_idx(const std::string charset, char ch) {
    return charset.find(ch);
}



/**
 * Public API
 */

namespace base64 {


std::string encode(const char *in, size_t inlen, int mode) {
    ubyte idx{0};
    std::stringstream buff{};
    const char padd_char = (mode & BS64Mode::NO_PADDING) ? '\0' : '=';
    const std::string &charset = (mode & BS64Mode::URL_SAFE) ? safe_base64_chars : base64_chars;

    while (inlen) {
        idx = ((ubyte)in[0] >> 2) & 0x3f;
        buff << (charset[idx]);

        idx = (((ubyte)in[0] << 4) | ((inlen -= 1) ? ((ubyte)in[1] >> 4) : 0)) & 0x3f;
        buff << (charset[idx]);

        idx = (((ubyte)in[1] << 2) | ((inlen - 1) ? ((ubyte)in[2] >> 6) : 0)) & 0x3f;
        buff << ((inlen) ? charset[idx] : padd_char);
        if (inlen)
            inlen -= 1;

        idx = ((ubyte)in[2] & 0x3f);
        buff << ((inlen) ? (charset[idx]) : padd_char);

        if (inlen)
            inlen -= 1;

        if (inlen)
            in += 3;
    }

    // buff << '\0';
    return buff.str();
}


std::string decode(std::string in, size_t inlen, int mode) {
    std::stringstream buff;
    size_t idx1, idx2, idx3, idx4;
    const std::string &charset = (mode & BS64Mode::URL_SAFE) ? safe_base64_chars : base64_chars;

    for (size_t i = 0; i < inlen; i += 4) {
        idx1 = base64_char_idx(charset, in[i]);
        if (idx1 == charset.npos)
            break;

        idx2 = ((i+1) >= inlen) ? 0 : base64_char_idx(charset, in[i+1]);
        if (idx2 == charset.npos)
            break;

        buff << ((byte)((((ubyte)idx1 & 0x3f) << 2) | (((ubyte)idx2 & 0x3f) >> 4)));

        idx3 = ((i+2) >= inlen) ? 0 : base64_char_idx(charset, in[i+2]);
        if (idx3 == charset.npos)
            break;

        buff << ((byte)((((ubyte)idx2 & 0x3f) << 4) | (((ubyte)idx3 & 0x3f) >> 2)));

        idx4 = ((i+3) >= inlen) ? 0 : base64_char_idx(charset, in[i+3]);
        if (idx4 == charset.npos)
            break;

        buff << ((byte)((((ubyte)idx3 & 0x3f) << 6) | ((ubyte)idx4 & 0x3f)));
    }

    return buff.str();
}


} // namespace base64
