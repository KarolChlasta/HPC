#include<stdio.h>

//Funkcja uruchamiana na karcie graficznej (kernel)

__global__ void add(int *a, int *b, int *c) 
{
	*c = *a + *b;
}

int main(void) {
	int a, b, c; // Tablice przechowywane w pamieci hosta
	int *d_a, *d_b, *d_c; // Tablice przechowywane na urządzeniu CUDA
	int size = sizeof(int);
	// Alokacja pamieci na urządzeniu CUDA
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);
	// Przykłdowe wartości
	a = 2;
	b = 7;
	// Kopiowanie wartosci na urządzenie
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	// Uruchomienie kernela na urządzeniu CUDA - 1 blok - 1 wątek
	add<<<1,1>>>(d_a, d_b, d_c);
	// Kopiowanie uzyskanych wartości
	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);
	// Czyszczenie
	printf("%d+%d=%d\n",a,b,c);
	cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
	return 0;
}
