#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <iostream>
#include <amp.h>
#include <chrono>
using namespace std;
using namespace concurrency;

void MatrixMulti(double* C, const double* A, const double* B, int M, int N, int K) {
	array_view<const double, 2> a(M, K, A), b(K, N, B);
	array_view<double, 2> c(M, N, C);
	c.discard_data();
	parallel_for_each(c.extent, [=](index<2> indx) restrict(amp) {
		int row = indx[0];
		int col = indx[1];
		double sum = 0;
		for (int i = 0; i < b.extent[0]; i++) {
			sum += a(row, i) * b(i, col);
		}
		c[indx] = sum;
		});
	c.synchronize();
}

int main()
{
	const int n = 2000;
	int M, N, K;
	M = N = K = n;
	double* pa = new double[n * n];
	for (int i = 0; i < n * n; i++)
		pa[i] = 1;
	double * pc = new double[n * n];
	double* pa1 = new double[n * n];
	auto start = std::chrono::high_resolution_clock::now();
	MatrixMulti(pa1, pa, pa, M, N, K);
	MatrixMulti(pc, pa, pa1, M, N, K);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << std::endl << "Time: " << duration.count() << " microseconds" << std::endl;
}
