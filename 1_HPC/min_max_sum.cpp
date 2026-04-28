#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter size: ";
    cin >> n;

    int a[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int sum = 0, min = a[0], max = a[0];

// Parallel Reduction
#pragma omp parallel for reduction(+ : sum) reduction(min : min) reduction(max : max)
    for (int i = 0; i < n; i++)
    {
        sum += a[i];

        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }

    double avg = (double)sum / n;

    cout << "\nSum = " << sum;
    cout << "\nMin = " << min;
    cout << "\nMax = " << max;
    cout << "\nAverage = " << avg;

    return 0;
}

/*
Input-
Enter size: 5
Enter elements:
1 2 3 4 5

Output-
Sum = 15
Min = 1
Max = 5
Average = 3

--------------------------------------------------------------

Time Complexity:
Sequential → O(n)
Parallel → O(n) (faster due to threads)

*/