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