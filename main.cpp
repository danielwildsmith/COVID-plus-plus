#include <iostream>
#include <fstream>
using namespace std;

int main()
{
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


}