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
    //getDayStatistics(rows, 11, 3, 2020);

    bool running = true;
    // Initial messages
    cout << "Hello! Welcome to COVID++\n";
    int input = 0;

    while (running) {
        cout << "Please select an option to continue\n";
        cout << "1. Days with most cases\n2. Days with most deaths\n3. option3\n-1. Exit program\n";
        cin >> input;

        switch (input) {
            case 1:
                // Prints the Country/date for top 5 highest cases days 
                //mergeSortByCases(rows, 0, rows.size()-1);
                break;
            case -1: // exit
                running = false;
                break;
        }

    }
    return 0;
}