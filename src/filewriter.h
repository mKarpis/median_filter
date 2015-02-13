#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>


class FileWriter
{
public:
    FileWriter();
    ~FileWriter();

    void initialize(const std::string &file);

    void close();

    bool add(const std::string &data);
    bool add(const float value);
    bool addFloatValues(const float v1, const float v2);

    void addNewLine();

private:
    std::ofstream file_;
};

#endif // FILEWRITER_H
