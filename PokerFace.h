
#ifndef POKERFACE_H
#define POKERFACE_H

#include <string>

class PokerFace {

private:
    std::string hexSequence = "4d5a90000300";   // Indicator of DOS mode
    std::string rawData;        // Raw string to store in buffer
    std::string extractedData;  // Extracted data after processing
    std::string fileName;       // File name user is interested in parsing
    std::string outputName;       // Name of output file

public:
    bool loadStream();           // Loads the file into rawData
    void pullChecksum();        // Extracts data based on hexSequence
    bool saveChecksum();           // Saves extracted data to an output file
    void menu();        // Displays the menu and handles user input
};
#endif //POKERFACE_H
