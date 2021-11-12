#include<stdio.h>
#include<omp.h>

#define N 500

int main()
{
   int square=0, number, i;
	
   printf("Wpisz numer:\n");
   scanf("%d",&number);
   //#pragma omp parallel for 
   for(i=0;i<N;i++)
   {
	square+=number*number;
   }
   
   printf("Wynik=%d\n",square);
}
