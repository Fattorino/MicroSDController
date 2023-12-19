#include "ToroSDController.h"

LogFile::LogFile(String path)
{
    if (!SDC::ready())
        return;

    if (path[0] != '/')
        path = '/' + path;

    File fileMG = SD.open(path.c_str(), FILE_WRITE);
    if (!fileMG)
    {
        Serial.println("[TSD] Failed to create the file");
    }
    fileMG.close();
    m_path = path;
}

bool LogFile::log(String &&data)
{
    File fileMG = SD.open(m_path.c_str(), FILE_APPEND);

    if (!fileMG)
    {
        Serial.println("[TSD] Failed to open the file");
        return false;
    }

    fileMG.print(data);

    fileMG.close();

    return true;
}

// ===========================================================================================

bool SDC::init_impl()
{
    if (!SD.begin())
    {
        Serial.println("[TSD] Init Failed");
        return false;
    }

    m_cardType = SD.cardType();

    if (m_cardType == CARD_NONE)
    {
        Serial.println("[TSD] No SD card attached");
        return false;
    }

    m_cardSize = SD.cardSize() / (1024 * 1024);
    if (m_cardSize == 4)
        m_cardType = 4;
    Serial.println("[TSD] Init done successfully");

    m_ready = true;
    return true;
}

bool SDC::makedir_impl(String &path) const
{
    if (!m_ready)
        return false;

    return SD.mkdir(path);
}

std::vector<String> SDC::listFiles_impl(String &path)
{
    File root = SD.open(path);
    if (!root)
    {
        Serial.println("[TSD] Failed to load path");
        return {};
    }
    if (!root.isDirectory())
    {
        Serial.println("[TSD] Path doesn't point to a directory");
        return {};
    }

    std::vector<String> files;
    File currFile = root.openNextFile();
    while (currFile)
    {
        if (!currFile.isDirectory())
        {
            files.emplace_back(currFile.name());
        }
        currFile = root.openNextFile();
    }
    return files;
}

std::vector<String> SDC::listDirs_impl(String &path)
{
    File root = SD.open(path);
    if (!root)
    {
        Serial.println("[TSD] Failed to load path");
        return {};
    }
    if (!root.isDirectory())
    {
        Serial.println("[TSD] Path doesn't point to a directory");
        return {};
    }

    std::vector<String> dirs;
    File currDir = root.openNextFile();
    while (currDir)
    {
        if (currDir.isDirectory())
        {
            dirs.emplace_back(currDir.name());
        }
        currDir = root.openNextFile();
    }
    return dirs;
}
