#include "filewriter.h"
#include "utils.h"


FileWriter::FileWriter()
{

}

FileWriter::~FileWriter()
{
    close();
}

void FileWriter::initialize(const std::string &file)
{
    close();
    file_.open(file.c_str(), std::ofstream::out);
}

void FileWriter::close()
{
    if(!file_.is_open())
        file_.close();
}

void FileWriter::addNewLine()
{
    if(!file_.is_open())
        return;

    add("\n");
}

bool FileWriter::addFloatValues(const float v1, const float v2)
{
    if(!file_.is_open())
        return false;

    file_ << Utils::floatToString(v1) << "," << Utils::floatToString(v2);
    return true;
}

bool FileWriter::add(const float value)
{
    if(!file_.is_open())
        return false;

    return add(Utils::floatToString(value));
}

bool FileWriter::add(const std::string &data)
{
    if(!file_.is_open())
        return false;

    file_ << data;

    return true;
}
