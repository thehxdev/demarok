#ifndef DEMAROK_HIDER_H
#define DEMAROK_HIDER_H


#include <filesystem>


namespace demarok {
namespace hider {


class BasicHider {
public:
    BasicHider(std::string path_str);

    virtual void hide() {}

    virtual void unhide() {}

protected:
    std::filesystem::path path;
    bool isDir;
};


class ObfsHider final : public BasicHider {
public:

    ObfsHider(std::string path_str);

    void hide() override;

    void unhide() override;

protected:
    static const int BYTES_TO_READ = 8;
    std::string mark;
    void processHeader();
};


class ChmodHider final : public BasicHider {
public:

    ChmodHider(std::string path_str);

    void hide() override;

    void unhide() override;
};


BasicHider *chooseHider(std::string mode, std::string path_str);


} // namespace hider
} // namespace demarok

#endif // DEMAROK_HIDER_H
