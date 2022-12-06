void mergeSortByCases(vector<Row> &rows, int left, int right)
{
    if (left >= right) // base case
        return;

    int mid = left + (right - left) / 2;
    mergeSortByCases(rows, left, mid);
    mergeSortByCases(rows, mid + 1, right);
    // merge the two sorted subarrays
    //mergeCases(rows, left, mid, right);

    // print results
}

void mergeCases(vector<Row> &rows, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
}

void mergeSortByDeaths()
{

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
}

