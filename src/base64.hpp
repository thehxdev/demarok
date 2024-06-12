#ifndef DEMAROK_BASE64_H
#define DEMAROK_BASE64_H


// encoding modes
enum BS64Mode : int {
    NORMAL      =   (1<<0),
    URL_SAFE    =   (1<<1),
    NO_PADDING  =   (1<<2),
};


namespace base64 {

std::string encode(const char *in, size_t inlen, int mode);

std::string decode(std::string in, size_t inlen, int mode);

} // namespace base64

#endif // DEMAROK_BASE64_H
