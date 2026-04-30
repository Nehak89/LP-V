#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Print
void print(vector<int>& a){
    for(int x : a) cout<<x<<" ";
    cout<<"\n";
}

// Bubble
void b(vector<int> &a){
    for (int i = 0; i < a.size() - 1; i++)
        for (int j = 0; j < a.size() - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void pb(vector<int> &a){
    for (int i = 0; i < a.size() - 1; i++)
    #pragma omp parallel for
        for (int j = 0; j < a.size() - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

// Merge
void m(vector<int> &a, int l, int r){
    if (l < r){
        int m1 = (l + r) / 2;
        m(a, l, m1);
        m(a, m1 + 1, r);

        vector<int> t;
        int i = l, j = m1 + 1;

        while (i <= m1 && j <= r)
            t.push_back(a[i] < a[j] ? a[i++] : a[j++]);

        while (i <= m1) t.push_back(a[i++]);
        while (j <= r) t.push_back(a[j++]);

        for (int k = 0; k < t.size(); k++)
            a[l + k] = t[k];
    }
}

void pm(vector<int> &a, int l, int r){
    if (l < r){
        int m1 = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            pm(a, l, m1);

            #pragma omp section
            pm(a, m1 + 1, r);
        }

        m(a, l, r);
    }
}

// Main
int main(){
    int n;
    cout << "Enter size: ";
    cin >> n;

    vector<int> a(n), b1, c, d;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cout << "\nOriginal Array: ";
    print(a);

    b1 = c = d = a;

    double t;

    t = omp_get_wtime();
    b(b1);
    cout << "\nSorted (Sequential Bubble): ";
    print(b1);
    cout << "Time: " << omp_get_wtime() - t << "\n";

    t = omp_get_wtime();
    pb(c);
    cout << "\nSorted (Parallel Bubble): ";
    print(c);
    cout << "Time: " << omp_get_wtime() - t << "\n";

    t = omp_get_wtime();
    m(a, 0, n - 1);
    cout << "\nSorted (Sequential Merge): ";
    print(a);
    cout << "Time: " << omp_get_wtime() - t << "\n";

    t = omp_get_wtime();
    pm(d, 0, n - 1);
    cout << "\nSorted (Parallel Merge): ";
    print(d);
    cout << "Time: " << omp_get_wtime() - t << "\n";

    return 0;
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
