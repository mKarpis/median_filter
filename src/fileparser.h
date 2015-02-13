#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <iostream>
#include <fstream>

class DataBlock;

class FileParser
{
public:
    FileParser();
    ~FileParser();

    struct RecordItem{
        float voltage;
        float current;
    };

    bool initialize(const std::string &inputFile, std::string &errorMsg);

    bool readFinished() {return readFinished_;}

    bool getNextRecord(RecordItem &record);

private:
    void clear();

    //! returns endian type
    bool isArchBigEndian();
    bool safeRead(char* s, const std::streamsize size);

    //! returns FALSE if validation fails
    bool validateHash();

    std::fstream file_;
    bool readFinished_;

    const unsigned int hashByteSize_;
    const unsigned int blockByteSize_;
    const unsigned int recordByteSize_;

    int fileLength_;

    int currentBlockSize_;
    int currentBlockPointer_;

};


#endif // FILEPARSER_H
