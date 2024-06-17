#include <iostream>
#include <string>
#include <memory>
#include "hider.hpp"


void usage(const char *progname);


int main(int argc, char **argv) {
    using namespace demarok;

    if (argc != 4) {
        usage(argv[0]);
        return 1;
    }

    std::unique_ptr<hider::BasicHider> hider;
    try {
        hider = std::unique_ptr<hider::BasicHider>{hider::chooseHider(argv[1], argv[3])};
    } catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::string cmd = std::string(argv[2]);
    if (cmd == "hide")
        hider->hide();
    else if (cmd == "unhide")
        hider->unhide();
    else {
        usage(argv[0]);
        return 1;
    }
    return 0;
}


void usage(const char *progname) {
    std::cerr << "Usage: "
        << progname
        << " <chmod/obfs>"
        << " <hide/unhide>"
        << " <file-path>"
        << std::endl;
}
