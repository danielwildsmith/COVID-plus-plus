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

void getDayStatistics(vector<Row> &rows, int day, int month, int year)
{
    // output message for invalid dates
    if ((year < 2019) || (year > 2022) || (year == 2019 && day < 31) || (year == 2020 && month == 12 && day > 14))  {
        cout << "Please enter a valid date from 2020 to 2022\n";
        return;
    }

    // Determine maximum/minimum cases -> create a vector to hold cases on specific day
    vector<std::pair<string, int>> unsortedCases;
    for(const auto& row : rows) {
        if(row.getDay() == day && row.getMonth() == month && row.getYear() == year)
            unsortedCases.emplace_back(row.getCountry(), row.getCases());
    }

    // Call both merge and shell sort. Only one sorted vector should be displayed when showing results
    // Record time each sorting method takes
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<std::pair<string, int>> sortedCases = unsortedCases;
    sortedCases = shellSort(sortedCases);
    steady_clock::time_point end = steady_clock::now();
    cout << "Shell sort finished in " << duration_cast<microseconds>(end - begin).count() << " microseconds" << endl;

    begin = steady_clock::now();
    mergeSort(unsortedCases, 0, unsortedCases.size()-1);
    end = steady_clock::now();
    cout << "Merge sort finished in " << duration_cast<microseconds>(end - begin).count() << " microseconds" << endl;
    cout << endl;

    int numbered = 1;
    cout << "Countries with the Highest Cases on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = sortedCases.size() - 1; i > sortedCases.size() - 6; i--)
        cout << numbered++ << ". " << sortedCases.at(i).first << ": " << sortedCases.at(i).second << endl;
    cout << endl;

    numbered = 1;
    cout << "Countries with the Lowest Cases on " << month << "/" << day << "/" << year << ": " << endl;
    for(int i = 0; i < 5; i++)
        cout << numbered++ << ". " << sortedCases.at(i).first << ": " << sortedCases.at(i).second << endl;
}

void getMaxDeaths(vector<Row> &rows)
{
    // Determine maximum deaths -> create a vector to hold deaths
    vector<std::pair<string, int>> unsortedDeaths;
    for(const auto& row : rows) {
        unsortedDeaths.emplace_back(row.getCountry(), row.getDeaths());
    }

    // Call both merge and shell sort. Only one sorted vector should be displayed when showing results
    // Record time each sorting method takes
    steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<std::pair<string, int>> sortedDeaths = unsortedDeaths;
    sortedDeaths = shellSort(sortedDeaths);
    steady_clock::time_point end = steady_clock::now();
    cout << "Shell sort finished in " << duration_cast<microseconds>(end - begin).count() << " microseconds" << endl;

    begin = steady_clock::now();
    mergeSort(unsortedDeaths, 0, unsortedDeaths.size()-1);
    end = steady_clock::now();
    cout << "Merge sort finished in " << duration_cast<microseconds>(end - begin).count() << " microseconds" << endl;
    cout << endl;

    int numbered = 1;
    cout << "Countries with the Highest Cases: " << endl;
    for(int i = sortedDeaths.size() - 1; i > sortedDeaths.size() - 6; i--)
        cout << numbered++ << ". " << sortedDeaths.at(i).first << ": " << sortedDeaths.at(i).second << endl;
    cout << endl;
}