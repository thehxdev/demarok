#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include "types.hpp"
#include "base64.hpp"
#include "hider.hpp"


namespace demarok {
namespace hider {


BasicHider::BasicHider(std::string path_str) {
    this->path = std::filesystem::path{path_str};
    if (!std::filesystem::exists(this->path))
        throw std::runtime_error("Given path does not exist.");
    this->isDir = std::filesystem::is_directory(this->path);
}



ObfsHider::ObfsHider(std::string path_str) : BasicHider{path_str} {
    if (this->isDir)
        this->mark = std::string("!amk");
    else
        this->mark = std::string("!amk2");
}

void ObfsHider::hide() {
    using namespace std;
    namespace bs64 = demarok::base64;

    stringstream newFileName;
    string fileName = path.filename();

    if (fileName.find(this->mark) != fileName.npos)
        return;

    newFileName
        << (path.has_parent_path() ? (path.parent_path().string().append("/")) : "")
        << '.'
        << (bs64::encode(fileName.c_str(),
                         fileName.length(),
                         BS64Mode::URL_SAFE | BS64Mode::NO_PADDING));
        // << this->mark;

    filesystem::path newPath{newFileName.str()};

    if (!this->isDir)
        this->processHeader();
    filesystem::rename(path, newPath);

    // filesystem::copy(path, newPath,
    //                  filesystem::copy_options::overwrite_existing);
    // if (!this->isDir)
    //     this->processHeader();
}

void ObfsHider::unhide() {
    using namespace std;
    namespace bs64 = demarok::base64;

    string fileName = path.filename();

    // if (fileName.find(this->mark) != fileName.npos)
    //     return;

    size_t mark_idx = fileName.find("!amk");
    fileName = fileName.substr(1,
                               ((mark_idx == fileName.npos) ? fileName.length() - 1 : mark_idx - 1));
    stringstream newFileName;

    newFileName
        << (path.has_parent_path() ? (path.parent_path().string().append("/")) : "")
        << bs64::decode(fileName, fileName.length(), BS64Mode::URL_SAFE);

    filesystem::path newPath{newFileName.str()};

    if (!this->isDir)
        this->processHeader();
    filesystem::rename(path, newPath);

    // filesystem::copy(path, newPath,
    //                  filesystem::copy_options::overwrite_existing);
    // if (!this->isDir)
    //     this->processHeader();
}

void ObfsHider::processHeader() {
    using namespace demarok;

    int i;
    std::fstream f{this->path};
    byte bytes[BYTES_TO_READ] = { 0 };

    f.read(bytes, BYTES_TO_READ)
        .seekg(0);

    for (i = 0; i < BYTES_TO_READ; i++)
        bytes[i] = (ubyte)(~(bytes[i]));

    f.write(bytes, BYTES_TO_READ)
        .seekp(0);

    f.close();
}



ChmodHider::ChmodHider(std::string path_str) : BasicHider{path_str} {}

void ChmodHider::hide() {
    chmod(this->path.c_str(), 0);
}

void ChmodHider::unhide() {
    unsigned int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if (this->isDir)
        mode |=  S_IXUSR | S_IXGRP | S_IXOTH;
    chmod(this->path.c_str(), mode);
}



BasicHider *chooseHider(std::string mode, std::string path_str) {
    if (mode == "obfs")
        return (new demarok::hider::ObfsHider(path_str));
    return (new demarok::hider::ChmodHider(path_str));
}


} // namespace hider
} // namespace demarok
