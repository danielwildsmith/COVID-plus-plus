#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Row.h"
using namespace std;

int main() {

    string file = "covidFull.csv";
    ifstream infile(file);
    string linefromfile;

    vector<Row> rows; // list of data

    if (infile.is_open()) {
        getline(infile, linefromfile); // done for first line

        while (getline(infile, linefromfile)) {
            istringstream stream(linefromfile);
            string buffer;

            getline(stream, buffer, ',');
            int day = stoi(buffer);

            getline(stream, buffer, ',');
            int month = stoi(buffer);

            getline(stream, buffer, ',');
            int year = stoi(buffer);

            getline(stream, buffer, ',');
            int cases = stoi(buffer);

            getline(stream, buffer, ',');
            int deaths = stoi(buffer);

            getline(stream, buffer, ',');
            string country = buffer;

            getline(stream, buffer, ',');
            getline(stream, buffer, ',');
            getline(stream, buffer, ',');
            getline(stream, buffer, ',');
            int rate = stoi(buffer);

            Row row = Row(day, month, year, cases, deaths, country, rate);
            rows.push_back(row);

        }
    }

    //cout<< rows[0].getCountry();
    bool running = true;

    // Initial messages
    cout << "Hello! Welcome to COVID++\n";
    int input = 0;

    while (running) {
        cout << "Please select an option to continue\n";
        cout << "1. option1\n2. option2\n3. option3\n-1. Exit program\n";
        cin >> input;

        if (input == -1) { // exit
            running = false;
            break;
        }
    }
//comment
    return 0;
}