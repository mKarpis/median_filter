#include <stdio.h>
#include <sstream>

#include "fileparser.h"
#include "medianholder.h"
#include "filewriter.h"

const unsigned defaultWindowSize_ = 100000;
const unsigned initialWindow_ = 100000;

bool inputArgumensValid(int argc, char* argv[], std::string &errorMsg, unsigned &windowSize);



int main(int argc, char* argv[])
{    
    std::string errorMsg;
    unsigned windowSize;

    // INPUT ARGUMENTS CHECK
    if(!inputArgumensValid(argc, argv, errorMsg, windowSize)){
        std::cout << errorMsg << std::endl;
        exit(0);
    }

    const std::string inputFile = argv[1];
    const std::string outputFile = argv[2];
    FileParser *fileParser = new FileParser;


    // INPUT FILE CHECK
    if(!fileParser->initialize(inputFile, errorMsg)){
        std::cout << errorMsg;
        delete fileParser;
        exit(0);
    }


    FileParser::RecordItem record;
    MedianHolder medianHolderVoltage;
    MedianHolder medianHolderCapacity;


    // INITIALIZE OUTPUT FILE
    FileWriter *fileWriter = new FileWriter;
    fileWriter->initialize(outputFile);
    unsigned elementsCounter = 0;


    // INITIALIZE WINDOW (100,000 zeros)
    const int initialWindowSize = initialWindow_;
    for(unsigned i=0; i<initialWindowSize; i++){

        elementsCounter++;

        if(elementsCounter == defaultWindowSize_){
            //add values to output file
            if(!fileWriter->addFloatValues(0, 0)){
                std::cout << "Got problem writing output data!";
                exit(0);
            }
            fileWriter->addNewLine();

            elementsCounter = 0;
        }
    }

    // PARSING
    std::cout << "parsing";
    elementsCounter = 0;
    unsigned int counter = 0;
    const unsigned int progressCheck = 100000; //number of iterations needed for a progress update

    while(!fileParser->readFinished())
    {
        if(!fileParser->getNextRecord(record)){
            continue;
        }

        medianHolderVoltage.insert(record.voltage);
        medianHolderCapacity.insert(record.current);

        elementsCounter++;

        if(elementsCounter == windowSize){
            const float medianCapacity = medianHolderCapacity.getMedian();
            const float medianVoltage = medianHolderVoltage.getMedian();

            // std::cout << "capacity: " << medianCapacity << " voltage: " << medianVoltage << std::endl;

            //add values to output file
            if(!fileWriter->addFloatValues(medianCapacity, medianVoltage)){
                std::cout << "Got problem writing output data!";
                exit(0);
            }
            fileWriter->addNewLine();

            medianHolderVoltage.clear();
            medianHolderCapacity.clear();
            elementsCounter = 0;
        }

        if(counter == progressCheck){
            std::cout << ".";
            std::cout.flush();
            counter = 0;
        }

        counter++;
    }

    delete fileParser;
    delete fileWriter;

    return 0;
}

bool inputArgumensValid(int argc, char* argv[], std::string &errorMsg, unsigned &windowSize)
{
    std::string windowSizeString;
    std::stringstream out;
    out << defaultWindowSize_;
    windowSizeString = out.str();

    const std::string programUseInfo =
            std::string("Usage is <input-file> <output-file> <(optional) window-size (default ")
            .append(windowSizeString).append(")>\n");


    //argument check
    if (argc < 3) {
        errorMsg += "Incorrect number of input parameters. \n" + programUseInfo;
        return false;
    }

    windowSize = defaultWindowSize_;

    if(argc > 3){
        std::istringstream iss( argv[3] );
        unsigned userInputWindowSize = 0;

        if (iss >> userInputWindowSize){
            std::cout << "setting filter window size to: " << userInputWindowSize << std::endl;
            windowSize = userInputWindowSize;
        }else{
            errorMsg += "Wrong window size! \n" + programUseInfo;
            return false;
        }
    }

    return true;
}
