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

#ifndef BASE64_H
#define BASE64_H

namespace base64 {


// encoding modes
enum BS64Mode {
    NORMAL      =   (1<<0),
    URL_SAFE    =   (1<<1),
    NO_PADDING  =   (1<<2),
};

std::string encode(const char *in, size_t inlen, int mode);

std::string decode(std::string in, size_t inlen, int mode);


} // namespace base64

#endif // BASE64_H
