#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Row.h"
#include "sorting.cpp"

std::vector<Row> LoadCSVRows(string file) {
    ifstream infile(file);
    string line;

    vector<Row> rows; // list of data

    if (infile.is_open()) {
        getline(infile, line); // done for first line

        while (getline(infile, line)) {
            istringstream stream(line);
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
    return rows;
}

int main() {
    std::vector<Row> rows = LoadCSVRows("../covidFull.csv");

    bool running = true;
    // Initial messages
    cout << "Hello! Welcome to COVID++\n";
    int input = 0;

    while (running) {
        // Separate screens
        cout << "------------------------------------" << endl << endl;

        cout << "Please select an option to continue\n";
        cout << "1. Days with most cases\n2. Days with most deaths\n3. Country Statistics\n4. Day Statistics\n-1. Exit program\n";
        cin >> input;
        string userInput;

        switch (input) {
            case 1:
                // Prints the Country/date for top 5 highest cases days 
                getMaxCases(rows);
                break;
            case 2:
                // Prints the Country/date for top 5 highest death days
                getMaxDeaths(rows);
                break;
            case 3:
                // string country;
                cout << "Enter a Country (case-sensitive). Example: United States of America" << endl;
                std::getline(cin, userInput);
                std::getline(cin, userInput);
                getCountryStatistics(rows,userInput);
                break;
            case 4:
                // string country;
                cout << "Enter a Date in Month Day Year: \nExample: 12 06 2022" << endl;
                int day,month,year;
                cin >> month;
                cin >> day;
                cin >> year;
                getDayStatistics(rows,day, month, year);
                break;
            case -1: // exit
                running = false;
                break;
            default:
                cout << "Invalid selection! Please pass in the number of the desired operation." << endl;
        }
    }
    return 0;
}