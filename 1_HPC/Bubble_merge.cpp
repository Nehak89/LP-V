#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Bubble Sort
void bubble(vector<int> &a, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void pbubble(vector<int> &a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
    }
}

// Merge Sort
void merge(vector<int> &a, int l, int m, int r)
{
    vector<int> t;
    int i = l, j = m + 1;
    while (i <= m && j <= r)
        t.push_back(a[i] < a[j] ? a[i++] : a[j++]);
    while (i <= m)
        t.push_back(a[i++]);
    while (j <= r)
        t.push_back(a[j++]);
    for (int k = 0; k < t.size(); k++)
        a[l + k] = t[k];
}

void msort(vector<int> &a, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        msort(a, l, m);
        msort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void pmsort(vector<int> &a, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            pmsort(a, l, m);
#pragma omp section
            pmsort(a, m + 1, r);
        }
        merge(a, l, m, r);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> a(n), b, c, d;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    b = c = d = a;

    double t1 = omp_get_wtime();
    bubble(b, n);
    double t2 = omp_get_wtime();
    double t3 = omp_get_wtime();
    pbubble(c, n);
    double t4 = omp_get_wtime();
    double t5 = omp_get_wtime();
    msort(a, 0, n - 1);
    double t6 = omp_get_wtime();
    double t7 = omp_get_wtime();
    pmsort(d, 0, n - 1);
    double t8 = omp_get_wtime();

    cout << "\nBub Seq: " << t2 - t1;
    cout << "\nBub Par: " << t4 - t3;
    cout << "\nMer Seq: " << t6 - t5;
    cout << "\nMer Par: " << t8 - t7;
}

/*
Input-
Enter size : 5
Enter elements : 5 3 1 4 2

Output-
Bub Seq: 0.00001
Bub Par: 0.00002
Mer Seq: 0.000005
Mer Par: 0.000003

----------------------------------------------------------------------------

Time complexity-

🔹Bubble Sort
Sequential: O(n²)
Parallel: O(n²) (no major improvement)

🔹Merge Sort
Sequential: O(n log n)
Parallel: O(log n) (with proper parallelization ideal case)

*/
