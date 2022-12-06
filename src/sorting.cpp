#include "Row.h"

void mergeCases(vector<Row> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Row> L;
    vector<Row> R;

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
        if (L[i].getCases() <= R[j].getCases()) {
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

void mergeSortByCases(vector<Row> &arr, int left, int right)
{
    if (left >= right) // base case
        return;

    int mid = left + (right - left) / 2;
    mergeSortByCases(arr, left, mid);
    mergeSortByCases(arr, mid + 1, right);
    // merge the two sorted subarrays
    mergeCases(arr, left, mid, right);

    // print results
    if (left == 0 && right == arr.size() - 1)  {
        for (int i = arr.size() - 1; i > arr.size() - 6; i--) {
            cout << "# Cases in " << arr[i].getCountry() << " on the day " << arr[i].getMonth() << "/" << arr[i].getDay();
            cout << "/" << arr[i].getYear() << " : " << arr[i].getCases() << endl;
        }
    }
}

void mergeCasesOnDay(vector<pair<string, int>> &arr, int left, int mid, int right)
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

void mergeSortCasesOnDay(vector<pair<string, int>> &arr, int left, int right)
{
     if (left >= right) // base case
        return;

    int mid = left + (right - left) / 2;
    mergeSortCasesOnDay(arr, left, mid);
    mergeSortCasesOnDay(arr, mid + 1, right);
    // merge the two sorted subarrays
    mergeCasesOnDay(arr, left, mid, right);
}

// Inspired from Discussion 8 slides
void shellSort(vector<std::pair<string, int>>& arr) {
    int n = (int)arr.size();

    // gap starts at n/2 and is divided by 2 until gap is 1 (insertion sort last pass)
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = arr.at(i).second;

            int j;
            for(j = i; j >= gap && arr.at(j - gap).second > temp; j-= gap)
                arr.at(j) = arr.at(j - gap);

            arr[j].second = temp;
        }
    }
    for(int i = arr.size() - 1; i > arr.size() - 6; i--)
        std::cout << arr.at(i).first << ": " << arr.at(i).second << ", ";
    std::cout << std::endl;
}

void getDayStatistics(vector<Row> &rows, int day, int month, int year)
{
    // TODO: if invalid day/month/year or day inputted has no data -> output message

    // Determine maximum/minimum cases -> create a vector to hold cases on specific day
    vector<std::pair<string, int>> cases;
    for(const auto& row : rows) {
        if(row.getDay() == day && row.getMonth() == month && row.getYear() == year)
            cases.emplace_back(row.getCountry(), row.getCases());
    }
    // Call both merge and shell sort. Only one sorted vector should be displayed when showing results
    shellSort(cases);
    mergeSortCasesOnDay(cases, 0, cases.size()-1);
}