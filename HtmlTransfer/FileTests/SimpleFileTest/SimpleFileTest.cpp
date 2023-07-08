// SimpleFileTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 

#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include <cstdint>
#include <filesystem>


#include <iostream>
#include <array>


std::string readFileContent(const std::filesystem::path& inFileName)
{
    std::ifstream ifs(inFileName);
    return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

size_t getFileSize(const std::filesystem::path& fileName)
{
    return std::filesystem::file_size(fileName);
}

bool fileExists(const std::filesystem::path& fileName)
{
    return std::filesystem::exists(fileName);
}


void writeFileContent(const std::filesystem::path& outFileName, const std::string& content)
{
    std::ofstream ofs(outFileName);
    ofs << content;
    ofs.close();
}

bool checkFileSize(const std::filesystem::path& fileName, size_t expectedSize)
{
    const size_t fileSize = getFileSize(fileName);
    if (fileSize != expectedSize)
    {
        std::cout << "This should never happen: fileName=" << fileName << ", fileSize=" << fileSize << ", expectedSize=" << expectedSize << std::endl;
        return false;
    }
    return true;
}

void copyFile(const std::filesystem::path& inFileName, const std::filesystem::path& outFileName)
{
    const std::string content = readFileContent(inFileName);
    checkFileSize(inFileName, content.length());    // sanity check
    writeFileContent(outFileName, content);
    checkFileSize(outFileName, content.length());   // sanity check
    std::cout << "Copied " << inFileName << ", size=" << content.length() << ", to " << outFileName << std::endl;
}

bool MakePair(const std::string& src, char separator, std::string& lhs, std::string& rhs)
{
    size_t index = src.find(separator);
    if (index != std::string::npos)
    {
        lhs.assign(src.c_str(), index);
        rhs.assign(src.begin() + index + 1, src.end());
        return true;
    }
    return false;
}


int main(int count, const char* args[])
{
    const std::filesystem::path exeDir(std::filesystem::path(args[0]).remove_filename());

    std::filesystem::path inFileName;   // "t.txt"
    std::filesystem::path outFileName;  // "t - Copy.txt"

    // return the dir + folder separator, + filename
    auto pathConcat = [](std::filesystem::path dir, const std::string& filename)
    {
        return dir /= std::filesystem::path(filename);  // the /= operator implementation on std::filesystem::path also inserts the folder separator
    };

    for (int i = 1; i < count; ++i)
    {
        std::string key;
        std::string value;
        if (MakePair(args[i], '=', key, value))
        {
            if (key == "in")
            {
                inFileName = pathConcat(exeDir, value);
            }
            else if (key == "out")
            {
                outFileName = pathConcat(exeDir, value);
            }
        }
    }

    if (inFileName.empty())
    {
        inFileName = pathConcat(exeDir, "t.txt");
    }
    if (outFileName.empty())
    {
        outFileName = pathConcat(exeDir, "t - Copy.txt");
    }

    if (!fileExists(inFileName.string()))
    {
        const std::string content("0123456789");  // create a test content
        writeFileContent(inFileName.string(), content);
    }

    copyFile(inFileName.string(), outFileName.string());

    return 0;
}

