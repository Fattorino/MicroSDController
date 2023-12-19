#include "SD.h"
#include <vector>
#include <string>

class LogFile
{
public:
    explicit LogFile(String path);

    bool log(String &&data);

private:
    String m_path;
};

class SDC
{
public:
    SDC(SDC const &) = delete;
    SDC &operator=(SDC const &) = delete;

    static SDC &get()
    {
        static SDC _instance;
        return _instance;
    }

    static bool init() { return get().init_impl(); }

    static bool ready() { return get().ready_impl(); }
    static int8_t cardType() { return get().cardType_impl(); }
    static uint64_t cardSize() { return get().cardSize_impl(); }

    static bool makedir(String &&path) { return get().makedir_impl(path); }

    static std::vector<String> listFiles(String &&path) { return get().listFiles_impl(path); }
    static std::vector<String> listDirs(String &&path) { return get().listDirs_impl(path); }

protected:
    inline SDC(){};

    int8_t m_cardType = -1;
    uint64_t m_cardSize = 0;
    bool m_ready = false;

    bool init_impl();

    bool ready_impl() const { return m_ready; }
    int8_t cardType_impl() const { return m_cardType; }
    uint64_t cardSize_impl() const { return m_cardSize; }

    bool makedir_impl(String &path) const;

    std::vector<String> listFiles_impl(String &path);
    std::vector<String> listDirs_impl(String &path);
};
