#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>

using namespace std;
//headripper

//quick program that accepts raw data from tcp streams and if any scripts have attempted to run in DOS mode it will
//extract just the raw data needed to generate a SHA-256 hash and perform a checksum.
int main() {
    string hexSequence ="4d5a90000300";  //indicator of DOS mode
    ifstream dataRawFile;  //Input stream that can store a string such as text file
    string rawData;        //Raw string to store in buffer
    string extractedData;  //String post processing
    string userFile;       //File name user is interested in parsing
    string fileName;       //Name of output file
    string menu = "1";  //1 while the menu is open.
    string fileOpen = "1";  //1 while the file is open

    while (menu != "0") {    //0 closes the manu

        while (fileOpen != "0") {

            cout << "What file are you interesting in stripping?" << endl;
            cin >> userFile;
            //Opens the user's file in the input stream if it exists
            dataRawFile.open(userFile); //make sure your file is in the working directory

            if (dataRawFile.is_open()) {

                stringstream buffer;     //string stream that can hold the contents of an input file stream
                buffer << dataRawFile.rdbuf(); //input file stream is written into the ifstream buffer

                rawData = buffer.str();  //string function is used on the buffer and saved in rawData
                if (rawData.empty()) {
                    cerr << "The file is empty or unreadable." << endl;
                    fileOpen = "1";
                } else {
                    fileOpen = "0";
                }
                dataRawFile.close();
            }
            else {
                //Some options if the file does not load
                cout << "File did not open." << endl;
                cout << "1. Run the program again" << endl;
                cout << "2. Exit the program" << endl;
                cin >> fileOpen;
                if (fileOpen != "1") {
                    return 0;
                }
            }
        }

    size_t pos = rawData.find(hexSequence);   //determine the positions of the first instance of the sequence

    if (pos != string::npos) {
        extractedData = rawData.substr(pos);   //writes the data to the extractedData variable starting with the position of hex
        cout << "******************** An embedded executable was identified please contact your security administrator ******************" << endl;
    }
    else {
        cout << "******************** No embedded executables detected ********************" << endl;
    }
    cout << "What would you like to name your output file?" << endl;
    cin >> fileName;
    ofstream strippedRawFile(fileName);      //Creates an output file stream named stripped.. based off of the user's filename

    if (strippedRawFile.is_open()) {
        strippedRawFile << extractedData;     //extracted data is written into the output file stream
        strippedRawFile.close();
        cout << "Stripped data has successfully been written to " + fileName + " in the " << filesystem::current_path() << " directory." << endl;
    }
    else {
        cerr << "The stripped data was not able to be loaded" << endl;
    }
    cout << "1. Run the program again" << endl;
    cout << "2. Exit the program" << endl;
    cin >> menu;
    if (menu != "1") {
        return 0;
    }
    }

    return 0;
}