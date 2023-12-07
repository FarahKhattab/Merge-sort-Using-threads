#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <string>
using namespace std;

struct arg_struct {    //struct of parameters for the threads.
    int low;  
    int high; 
};


int* arr;            //input array

int n;             //array size

float time_taken;  


int* createArray(int n) //function to allocate the matrices in memory
{
    // Create a new dynamic array of integer pointers
    int* array = (int*)malloc(n* sizeof(int));
    return array;
}

void Load(const char* input_file)//function that reads input matrices from a given file  
{
    FILE *pRead;        //pointer for the input file
    pRead=fopen(input_file,"r");
    
    if (pRead== NULL) 
    {
        printf("Error!");
        return ;
    }
    
    fscanf(pRead,"%d",&n);
    
    arr = createArray(n);
    
    int i=0;

    while(!feof(pRead) && i<n)
    {
         fscanf(pRead,"%d",&arr[i]);		
    	 i++;
    }   
    
    fclose(pRead);
}
void save()//function that writes ouput matrices and time taken for each approach
{
    FILE *pWrite;   //pointer for the output file
    pWrite=fopen("output.txt","w");
    
    int i;

    for (i = 0; i <n; i++) 
    {
         fprintf(pWrite,"%d ", arr[i]);
    } 
    
    fprintf(pWrite,"\nTime taken: %.9f \n\n", time_taken);
    
    fclose(pWrite);
}

void display_arr()//function that displays matrices
{
    int i;
    
    printf("\nArray:\n");
	
	for (i = 0; i <n; i++) 
	{ 
	      printf("%d ", arr[i]);
	} 
	printf("\n");
}

void merge(int low, int mid, int high)
{
	int i, j, k;
	int n1 = mid - low + 1;// First subarray is arr[l..m]
	int n2 = high - mid;// Second subarray is arr[m+1..r]
	int *L=new int[n1], *R=new int[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[low + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	i = j = 0;
	k = low;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void *merge_sort(void *arguments)
{
    struct arg_struct *args = (struct arg_struct *)arguments;
    
    if(args->low < args->high)
    {
         int mid= args->low +(args->high - args->low)/2;
         
         arg_struct* args1 = (struct arg_struct*) malloc(sizeof(struct arg_struct));
         args1->low = args->low ;
         args1->high = mid;
         
         arg_struct* args2 = (struct arg_struct*) malloc(sizeof(struct arg_struct));
         args2->low =  mid+1;
         args2->high = args->high;
         
         pthread_t thread1,thread2;
         
         
         if (pthread_create(&thread1, NULL, &merge_sort, (void *)args1) != 0) 
         {
              printf("Uh-oh!\n");        
              return NULL;
         }
         
         if (pthread_create(&thread2, NULL, &merge_sort, (void *)args2) != 0) 
         {
              printf("Uh-oh!\n");
              return NULL ;
         }
         pthread_join(thread1, NULL);
         pthread_join(thread2, NULL);
         
         merge(args->low, mid, args->high);
    
    
    }
    
      
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
         fprintf(stderr, "usage: %s <input_file>\n", argv[0]);
         return -1;
    }
    
    
    int i,j;

    const char* filename= argv[1];

    Load(filename);	  

    
    pthread_t thread;
    
    auto start = std::chrono::high_resolution_clock::now();
    arg_struct* args = (struct arg_struct*) malloc(sizeof(struct arg_struct));
    args->low = 0;
    args->high = n-1;
              
    if (pthread_create(&thread, NULL, &merge_sort, (void *)args) != 0) 
    {
         printf("Uh-oh!\n");
         return -1;
    }

    pthread_join(thread, NULL);
    
    auto end = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(end-start).count();
    time_taken= static_cast<float>(seconds);
    
  
    save();
    return 0;
}
