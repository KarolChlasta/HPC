#include<stdio.h>
#include<omp.h>

omp_lock_t lock;

int main()
{
	omp_init_lock(&lock);
	srand(time(NULL));
	int a=0,i;
	omp_set_num_threads(4);
	printf("Petla firstprivate:\n");
	#pragma omp parallel for firstprivate(a) 
		for(i=0;i<10;i++)
		{
			printf("Watek %d a=%d\n",omp_get_thread_num(),a);			
			a++;						
		}
	printf("Po petli z firstprivate a=%d\n\n",a);
	
	printf("Petla private:\n");
	#pragma omp parallel for private(a) 
		for(a=0;a<10;a++)
		{			
			printf("Watek %d a=%d\n",omp_get_thread_num(),a);
		}
	printf("Po petli z private a=%d\n\n",a);
	printf("Petla lastprivate:\n");
	#pragma omp parallel for lastprivate(a) 
		for(i=0;i<10;i++)
		{
			//1. spróbuj zmieniæ na losowy numer i zaobserwuj wynik
			a=omp_get_thread_num();//rand()%11;			
			printf("Watek %d a=%d\n",omp_get_thread_num(),a);
		}
	printf("Po petli z lastprivate a=%d\n\n",a);
	
	printf("Petla shared:\n");	
	a=0;
	#pragma omp parallel for shared(a) 
	for(i=0;i<10;i++)
	{
		//2. Co sie stanie jak wy³¹czymy zamek(trzeba kilka razy uruchomiæ by zauwa¿yæ zmianê)?
		omp_set_lock(&lock);
		a=omp_get_thread_num();
		printf("Watek %d a=%d\n",omp_get_thread_num(),a);	
		omp_unset_lock(&lock);				
	}
	//3. Jaka jest wartoœæ "a" przy kilkukrotnym uruchomieniu? 
	printf("Po petli z shared a=%d\n\n",a);
	
	printf("Petla bez klauzuli wspoldzielenia zmiennych:\n");	
	a=0;
	#pragma omp parallel for 
	for(i=0;i<10000
	;i++)
	{		
		a++;
		//printf("Watek %d Iteracja %d a=%d\n",omp_get_thread_num(),i,a);
	}
	//4. Jaki jest domyœlny sposób dzilenia zmiennych gdy nie damy zadnej klauzuli? 
	printf("Po petli bez klauzuli wspoldzielenia zmiennych a=%d\n",a);	
}	

