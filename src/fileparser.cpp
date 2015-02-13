#include "fileparser.h"
#include "md5.h"
#include "utils.h"

#include <iostream>
#include <sstream>
#include <bitset>



FileParser::FileParser() :
    readFinished_(true),
    hashByteSize_(16),
    blockByteSize_(4),
    recordByteSize_(4),
    fileLength_(0),
    currentBlockSize_(0),
    currentBlockPointer_(-1)
{

}

FileParser::~FileParser()
{
    clear();
}

void FileParser::clear()
{
    if(file_.is_open())
        file_.close();

    fileLength_ = 0;
}

bool FileParser::initialize(const std::string & inputFile, std::string &errorMsg)
{
    clear();

    if(isArchBigEndian()){
        errorMsg += "You are running on a big endian architecture."
                    " Unfortunately only little endian is supported so far."
                    " Big endian arch should be in next release. Sorry..";
        return false;
    }

    if(file_.is_open())
        file_.close();

    file_.open(inputFile.c_str(), std::ifstream::in | std::ifstream::binary);

    if (!file_) {
        errorMsg += "Input file does not exist: " + inputFile + "\n";
        return false;
    }

    file_.seekg(0, file_.end);
    fileLength_ = file_.tellg();
    file_.seekg(0, file_.beg);


    if(!validateHash()){
        errorMsg += "Hash not validated!";
        return false;
    }

    //jump behind hash
    file_.seekg(16);
    readFinished_ = false;

    return true;
}

bool FileParser::getNextRecord(RecordItem &record)
{
    if(file_.eof()){
        readFinished_ = true;
        return false;
    }

    if(currentBlockSize_ == 0 || currentBlockPointer_ == currentBlockSize_){
        //get blocksize
        currentBlockPointer_ = 0;
        if(!safeRead((char *)(&currentBlockSize_), blockByteSize_))
            return false;

        //std::cout << "reading new block of size: " << currentBlockSize_ << std::endl;
    }

    //if we received a block with zero just skip it
    if(currentBlockSize_ == 0)
        return false;

    if(!safeRead((char *)(&record.voltage), recordByteSize_)){
        return false;
    }

    if(!safeRead((char *)(&record.current), recordByteSize_)){
        return false;
    }

    currentBlockPointer_++;
    return true;
}

bool FileParser::safeRead(char* s, const std::streamsize size)
{
    //cheeck if we reached eof
    const int currentFilePos = file_.tellg();
    if(fileLength_ <= currentFilePos + size){
        readFinished_ = true;
        std::cout << "\ndone" << ::std::endl;
        return false;
    }

    try{
        file_.read(s, size);
    }
    catch(const std::exception& e){
        std::cerr << "received read exception: " << e.what() << ::std::endl;
        return false;
    }

    return true;
}

bool FileParser::validateHash()
{
    std::cout << "checking hash value.. ";

    //get received hash
    unsigned char receivedHashValue[16];
    file_.seekg(0);
    file_.read((char *)(&receivedHashValue), hashByteSize_);

    char tmpBuff[1];
    std::string receivedHash;

    for(const unsigned char* p = receivedHashValue; *p; ++p){
        std::sprintf(tmpBuff, "%02x", *p);
        receivedHash.append(tmpBuff);
    }

    file_.seekg(16);
    std::string buffer =  std::string(std::istreambuf_iterator<char>(file_),
                                      std::istreambuf_iterator<char>());


    const std::string calculatedHash = md5(buffer);

    if(calculatedHash != receivedHash){
        std::cout << "Hash value does not match: " << std::endl;
        std::cout << "hash received:  " << receivedHash;
        std::cout << "hash generated: " << calculatedHash;
        return false;
    }

    std::cout << " ..hash correct" << std::endl;

    return true;
}

bool FileParser::isArchBigEndian()
{
    union {unsigned i; char c[4];} endianInt = {0x01020304};

    return (endianInt.c[0] == 1) ? true:false;
}
