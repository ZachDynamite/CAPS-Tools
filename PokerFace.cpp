#include "PokerFace.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

using namespace std;

//quick program that accepts raw data from tcp streams and if any scripts have attempted to run in DOS mode it will
//extract just the raw data needed to generate a SHA-256 hash and perform a checksum.

bool PokerFace::saveChecksum() {
    ofstream strippedRawFile(outputName);
    if (strippedRawFile.is_open()) {
        strippedRawFile << extractedData;
        strippedRawFile.close();
        cout << "\n" << "Stripped data has successfully been written to " << outputName << " in the " << filesystem::current_path() << " directory." << "\n\n";
        return true;
    }
    cerr << "Failed to save checksum" << "\n";
    return false;
}

void PokerFace::pullChecksum() {
    size_t pos = rawData.find(hexSequence);
    if (pos != string::npos) {
        extractedData = rawData.substr(pos);
        cout << "******************** Embedded executable detected! ******************" << "\n";
    } else {
        cout << "******************** No embedded executables detected ********************" << "\n";
    }
}

bool PokerFace::loadStream() {
    ifstream dataRawFile(fileName);

    if (dataRawFile.is_open()) {
        stringstream buffer;
        buffer << dataRawFile.rdbuf();
        rawData = buffer.str();
        if (rawData.empty()) {
            cout << "[!] The file is empty" << "\n";
            return false;
        }
        dataRawFile.close();
        return true;
    }
    cout << "[!] There was an issue opening the file" << "\n";
    return false;
}

void PokerFace::menu() {
    string menuOption;
    cout << "          _____" << "\n";
    cout << "         |A .  | _____" << "\n";
    cout << "         | /.\\ ||A ^  | _____" << "\n";
    cout << "         |(_._)|| / \\ ||A _  | _____" << "\n";
    cout << "Poker    |  |  || \\ / || ( ) ||A_ _ |" << "\n";
    cout << " Face    |____V||  .  ||(_'_)||( v )|" << "\n";
    cout << "                |____V||  |  || \\ / |" << "\n";
    cout << "                       |____V||  .  |" << "\n";
    cout << "                              |____V|" << "\n";
    while (true) {
        cout << "1. Housecalling scanner" << "\n";
        cout << "2. Quit program" << "\n";
        cout << "PokerShell>";
        cin >> menuOption;
        if (menuOption == "1") {
            cout << "Save your raw TCP stream to a txt file in the PokerFace directory then enter it here" << "\n";
            cout <<"PokerShell>Scanner>";
            cin >> fileName;
            if (loadStream()) {
                pullChecksum();
                cout << "File loaded successfully: Enter the name of your output file" << "\n";
                cout << "PokerShell>Scanner>";
                cin >> outputName; //fileName
                saveChecksum();
            }
        } else if (menuOption =="2") {
            break;
        } else {
            cout << "[!] What are you doing bud 1 or 2?" << "\n";
        }
    }
}