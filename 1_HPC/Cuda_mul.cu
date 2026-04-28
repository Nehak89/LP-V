% % writefile mul.cu

#include <iostream>
#include <cuda_runtime.h>
    using namespace std;

#define N 2

// Kernel
__global__ void mul(int A[N][N], int B[N][N], int C[N][N])
{
    int i = threadIdx.x;
    int j = threadIdx.y;

    C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j];
}

int main()
{
    int A[N][N] = {{1, 2}, {3, 4}};
    int B[N][N] = {{5, 6}, {7, 8}};
    int C[N][N];

    int (*d_A)[N], (*d_B)[N], (*d_C)[N];

    cudaMalloc(&d_A, sizeof(A));
    cudaMalloc(&d_B, sizeof(B));
    cudaMalloc(&d_C, sizeof(C));

    cudaMemcpy(d_A, A, sizeof(A), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeof(B), cudaMemcpyHostToDevice);

    // Launch kernel (2x2 threads)
    mul<<<1, dim3(2, 2)>>>(d_A, d_B, d_C);

    cudaMemcpy(C, d_C, sizeof(C), cudaMemcpyDeviceToHost);

    // Print result
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

/*
On google colab, compile with:
!nvcc -o mul run.cu

Run with:
!./run

*/