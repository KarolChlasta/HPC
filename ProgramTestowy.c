#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define WYMIAR 5000
#define ROZMIAR 25000000


//PROCEDURA DO OPTYMALIZACJI

void mat_vec(double* a, double* x, double* y, int n)
{
  
  int i,j;
  
  for(i=0;i<n;i++){
    y[i]=0.0;
    for(j=0;j<n;j++){
      y[i]+=a[i+n*j]*x[j];
    }
  }

}


main ()
{
  clock_t start, stop; //inicjacja zmiennych zegarowych	
  static double a[ROZMIAR],x[WYMIAR],y[WYMIAR],z[WYMIAR];
  int n,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;
  double t;


  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
  for(i=0;i<WYMIAR;i++) x[i]=1.0*(WYMIAR-i);

  n=WYMIAR;

  printf("poczatek\n");
  
  start=clock();

  mat_vec2(a,x,y,n);

  stop=clock(); 
  
  t=(stop-start)/(double)CLOCKS_PER_SEC;
  
  printf("koniec - czas wykonania: %lf\n",t);

  // test
  printf("TEST\n");

  for(i=0;i<n;i++){
    z[i]=0.0;
    for(j=0;j<n;j++){
      z[i]+=a[i+n*j]*x[j];
    }
  }

  for(i=0;i<WYMIAR;i++){
    if(fabs(y[i]-z[i])>1.e-9*z[i]) printf("Blad!\n");
  }

}
