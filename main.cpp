#include <iostream>
#include <fstream>
#incude "Row.h"
using namespace std;

int main()
{

    string file = "covidFull.cvs";
    ifstream infile(file);
    string linefromfile;

    vector<Row> row; // list of data

    if(infile.is_open()){
        getline(infile, linefromfile) // done for first line

        while(getline(infile, linefromfile)){
            istringstream stream(linefromfile);
            string buffer;

            getline(steam, buffer, ',');
            int day = stoi(buffer);

            getline(steam, buffer, ',');
            int month = stoi(buffer);

            getline(steam, buffer, ',');
            int year = stoi(buffer);

            getline(steam, buffer, ',');
            int cases = stoi(buffer);

            getline(steam, buffer, ',');
            int deaths = stoi(buffer);

            getline(steam, buffer, ',');
            string country = buffer;

            getline(steam, buffer, ',');
            getline(steam, buffer, ',');
            getline(steam, buffer, ',');
            getline(steam, buffer, ',');
            int rate = stoi(buffer);

            Row row = Row(day, month, year, cases, deaths, country, rate);
            row.push_back(row);

        }
    }

    bool running = true;

    // Initial messages
    cout << "Hello! Welcome to COVID++\n";
    int input = 0;

    while(running) {
        cout << "Please select an option to continue\n";
        cout << "1. option1\n2. option2\n3. option3\n-1. Exit program\n";
        cin >> input;

        if (input == -1) { // exit
            running = false;
            break;
        }
    }
//comment

}