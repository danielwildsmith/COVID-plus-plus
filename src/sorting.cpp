#include "Row.h"
#include <chrono>
using namespace chrono;
using std::cout;
using std::endl;

void merge(vector<pair<string, int>> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<pair<string, int>> L;
    vector<pair<string, int>> R;

    // fill these sub arrays
    for (int i = 0; i < n1; i++)
        L.push_back(arr[left + i]);
    for (int i = 0; i < n2; i++)
        R.push_back(arr[mid + 1 + i]);

    // merge the arrays together
    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < n1 && j < n2) {
        if (L[i].second <= R[j].second) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // append remaining elements in L or R
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<pair<string, int>> &arr, int left, int right)
{
     if (left >= right) // base case
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    // merge the two sorted subarrays
    merge(arr, left, mid, right);
}

// Inspired from Discussion 8 slides
vector<std::pair<string, int>> shellSort(vector<std::pair<string, int>>& arr) {
    int n = (int)arr.size();

    // gap starts at n/2 and is divided by 2 until gap is 1 (insertion sort last pass)
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            std::pair<string, int> temp = std::make_pair(arr.at(i).first, arr.at(i).second);

            int j;
            for(j = i; j >= gap && arr.at(j - gap).second > temp.second; j-= gap)
                arr.at(j) = arr.at(j - gap);

            arr[j] = temp;
        }
    }
    return arr;
}

vector<std::pair<string, int>> runSorts(vector<std::pair<string, int>>& unsortedArr, string unit) {
    // Call both merge and shell sort. Only one sorted vector should be displayed when showing results
    // Record time each sorting method takes
    vector<std::pair<string, int>> sortedArr = unsortedArr;
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    sortedArr = shellSort(sortedArr);
    steady_clock::time_point end = steady_clock::now();

    int shellTime = 0;
    if(unit == "microseconds") {
        shellTime = duration_cast<microseconds>(end - begin).count();
        cout << "Shell sort finished in " << shellTime << " microseconds" << endl;
    }
    else if(unit == "milliseconds") {
        shellTime = duration_cast<milliseconds>(end - begin).count();
        cout << "Shell sort finished in " << shellTime << " milliseconds" << endl;
    }

    begin = steady_clock::now();
    mergeSort(unsortedArr, 0, unsortedArr.size()-1);
    end = steady_clock::now();
    int mergeTime = 0;
    if(unit == "microseconds") {
        mergeTime = duration_cast<microseconds>(end - begin).count();
        cout << "Merge sort finished in " << mergeTime << " microseconds" << endl;
    }
    else if(unit == "milliseconds") {
        mergeTime = duration_cast<milliseconds>(end - begin).count();
        cout << "Merge sort finished in " << mergeTime << " milliseconds" << endl;
    }

    // Print percentage faster
    if (shellTime < mergeTime) { // shell was faster
        float percent = (1 - (float)shellTime / mergeTime) * 100.0;
        cout << "Shell sort was " << fixed << showpoint << setprecision(2) << percent << "% faster than merge sort.\n\n";
    } else { // merge was faster
        float percent = (1 - (float)mergeTime / shellTime) * 100.0;
        cout << "Merge sort was " << fixed << showpoint << setprecision(2) << percent << "% faster than shell sort.\n\n";
    }
    return sortedArr;
}

void getDayStatistics(vector<Row> &rows, int day, int month, int year)
{
    // output message for invalid dates
    if ((year < 2019) || (year > 2022) || (year == 2019 && day < 31) || (year == 2020 && month == 12 && day > 14) || (month>12) || (day >31))  {
        cout << "Please enter a valid date from 2020 to 2022\n";
        return;
    }

    // Determine maximum/minimum cases -> create a vector to hold cases on specific day
    vector<std::pair<string, int>> unsortedCases;
    for(const auto& row : rows) {
        if(row.getDay() == day && row.getMonth() == month && row.getYear() == year)
            unsortedCases.emplace_back(row.getCountry(), row.getCases());
    }

    vector<std::pair<string, int>> sortedCases = runSorts(unsortedCases, "microseconds");

    int numbered = 1;
    cout << "Countries with the Highest Cases on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = sortedCases.size() - 1; i > sortedCases.size() - 6; i--)
        cout << numbered++ << ". " << sortedCases.at(i).first << ": " << sortedCases.at(i).second << endl;
    cout << endl;

    numbered = 1;
    cout << "Countries with the Lowest Cases on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = 0; i < 5; i++)
        cout << numbered++ << ". " << sortedCases.at(i).first << ": " << sortedCases.at(i).second << endl;
    cout << endl;

    vector<std::pair<string, int>> unsortedDeaths;
    for(const auto& row : rows) {
        if(row.getDay() == day && row.getMonth() == month && row.getYear() == year)
            unsortedDeaths.emplace_back(row.getCountry(), row.getDeaths());
    }

    vector<std::pair<string, int>> sortedDeaths = unsortedDeaths;
    sortedDeaths = shellSort(sortedDeaths);
    mergeSort(unsortedDeaths, 0, unsortedDeaths.size()-1);

    // Printing results
    numbered = 1;
    cout << "Countries with the Highest Deaths on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = sortedDeaths.size() - 1; i > sortedDeaths.size() - 6; i--)
        cout << numbered++ << ". " << sortedDeaths.at(i).first << ": " << sortedDeaths.at(i).second << endl;
    cout << endl;

    numbered = 1;
    cout << "Countries with the Lowest Deaths on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = 0; i < 5; i++)
        cout << numbered++ << ". " << sortedDeaths.at(i).first << ": " << sortedDeaths.at(i).second << endl;
    cout << endl;
}

void getMaxCases(vector<Row> &rows)
{
    // Determine maximum deaths -> create a vector to hold deaths
    vector<std::pair<string, int>> unsortedCases;
    for(const auto& row : rows) {
        string countryOnDate = row.getCountry() + " on " + std::to_string(row.getMonth()) + "/";
        countryOnDate += std::to_string(row.getDay()) + "/" + std::to_string(row.getYear());
        unsortedCases.emplace_back(countryOnDate, row.getCases());
    }

    vector<std::pair<string, int>> sortedCases = runSorts(unsortedCases, "milliseconds");

    int numbered = 1;
    cout << "Countries with the Highest Cases in a Day: " << endl;
    for(int i = sortedCases.size() - 1; i > sortedCases.size() - 6; i--)
        cout << numbered++ << ". " << sortedCases.at(i).first << ": " << sortedCases.at(i).second << endl;
    cout << endl;
}


void getMaxDeaths(vector<Row> &rows) {
    // Determine maximum deaths -> create a vector to hold deaths
    vector<std::pair<string, int>> unsortedDeaths;
    for (const auto &row: rows) {
        string countryOnDate = row.getCountry() + " on " + std::to_string(row.getMonth()) + "/";
        countryOnDate += std::to_string(row.getDay()) + "/" + std::to_string(row.getYear());
        unsortedDeaths.emplace_back(countryOnDate, row.getDeaths());
    }

    vector<std::pair<string, int>> sortedDeaths = runSorts(unsortedDeaths, "milliseconds");

    int numbered = 1;
    cout << "Countries with the Highest Death Counts in a Day: " << endl;
    for (int i = sortedDeaths.size() - 1; i > sortedDeaths.size() - 6; i--)
        cout << numbered++ << ". " << sortedDeaths.at(i).first << ": " << sortedDeaths.at(i).second << endl;
    cout << endl;
}

// Assumes input name is given with spaces rather than underscores
void getCountryStatistics(vector<Row> &rows, string name) {
    // CSV file records country names with spaces in two ways: stores spaces as ' ' or '_'
    // to get all info about a country, parse through dataset with both possible strings
    string nameUnderscored = "";
    if(name.find(' ')) {
        nameUnderscored = name;
        for(int i = 0; i < nameUnderscored.length(); i++) {
            if(nameUnderscored[i] == ' ')
                nameUnderscored[i] = '_';
        }
    }

    // Total Cases and Deaths
    int cases = 0;
    int deaths = 0;
    for(auto row : rows) {
        if(row.getCountry() == name || row.getCountry() == nameUnderscored) {
            cases += row.getCases();
            deaths += row.getDeaths();
        }
    }
    // if country is invalid
    if(cases == 0 || deaths == 0) {
        cout << "Please enter a valid country name. Example: 'Japan'" << endl << endl;
        return;
    }

    // Deadliest Day
    vector<std::pair<string, int>> unsortedDeathsOfCountry;
    for(const auto& row : rows) {
        if(row.getCountry() == name || row.getCountry() == nameUnderscored) {
            string countryOnDate = std::to_string(row.getMonth()) + "/";
            countryOnDate += std::to_string(row.getDay()) + "/" + std::to_string(row.getYear());
            unsortedDeathsOfCountry.emplace_back(countryOnDate, row.getDeaths());
        }
    }

    vector<std::pair<string, int>> sortedDeathsOfCountry = runSorts(unsortedDeathsOfCountry, "microseconds");

    // display statistics
    cout << name << " Statistics:" << endl;
    cout << "Total Deaths: " << deaths << endl;
    cout << "Total Cases: " << cases << endl;
    cout << "Deadliest Day: " << sortedDeathsOfCountry.at(sortedDeathsOfCountry.size() - 1).second << " deaths on ";
    cout << sortedDeathsOfCountry.at(sortedDeathsOfCountry.size() - 1).first << endl;
    cout << endl;
}

void getHighestCasesPerCapita(vector<Row> &rows) {
    vector<std::pair<string, int>> unsortedRates;
    for (const auto &row: rows) {
        string countryOnDate = row.getCountry() + " on " + std::to_string(row.getMonth()) + "/";
        countryOnDate += std::to_string(row.getDay()) + "/" + std::to_string(row.getYear());
        unsortedRates.emplace_back(countryOnDate, row.getRate());
    }

    vector<std::pair<string, int>> sortedRates = runSorts(unsortedRates, "milliseconds");

    int numbered = 1;
    cout << "Cumulative Number of Cases Recorded for 14 Days Per 100,000 People: " << endl;
    for (int i = sortedRates.size() - 1; i > sortedRates.size() - 6; i--)
        cout << numbered++ << ". " << sortedRates.at(i).first << ": " << sortedRates.at(i).second << endl;
    cout << endl;

}