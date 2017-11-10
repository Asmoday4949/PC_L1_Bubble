/*
    author : Bulloni Lucas & Fleury Malik
    date : 03.11.2017
    description : Laboratoire 1 - tri bulle concurrent
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "section.h"

void prototypeThreadedSort(int threadsCount, int array[], int sizeArray);
void* worker(void* param);
void threadSafeBubbleSort(Section* section);

struct structSubArrToSort {
   int* array;
   int  size;
};
typedef struct structSubArrToSort subArrToSort;

void swapValue(int* array, int a, int b);
void fillRandom(int* array, int size);
void printArray(int* array, int size);
void bubbleSort(int* array, int left, int right);

/*
    TODO : RECHANGER bubbleSort en tab + size avec arithm�tique des pointeurs, plus simple pour passer au thread
    TODO : Optimisation de la taille des threads
*/

int main()
{
    int sizeArray, numberOfThread;
    printf("Entrez la taille du tableau : ");
    scanf("%d", &sizeArray);
    printf("Entrez le nombre de threads : ");
    scanf("%d", &numberOfThread);

    //calculate the size of the subarray for each thread
    int sizesArrays[numberOfThread];
    int modSize = sizeArray % numberOfThread;
    int i;
    for(i = 0; i <= numberOfThread; i++)
    {
        sizeArray[i] = sizeArray / numberOfThread;
        if(modSize > 0)
        {
            sizeArray[i]++;
            modSize--;
        }
    }

    //creation du tableau de donn�es, malloc pour pouvoir faire un grand tableau
    int* arrData = malloc(sizeof(int)*sizeArray);
    fillRandom(arrData, sizeArray);

    pthread_t* arrThreads = malloc(sizeof(pthread_t)*numberOfThread);

    int* subArray = arrData;

    int i;
    for(i = 0; i < numberOfThread; i++)
    {
        subArrToSort data;
        data.array = subArray;
        data.size = sizesArrays[i];

        pthread_create(&arrThreads, NULL, bubbleSort, &data);
        subArray += sizesArrays[i];
    }

    //free memory
    free(arrData);
    free(arrThreads);
    return 0;
}

/*void prototypeThreadedSort(int threadsCount, int array[], int sizeArray)
{
    int mutexCount = threadsCount-1;
    pthread_t thread[threadsCount];
    pthread_mutex_t mutex[mutexCount];
    Section section[threadsCount];

    int sizeSection = sizeArray / threadsCount;
    int rest = sizeArray % threadsCount;

    int cnt;
    int leftIndex = 0;
    int rightIndex = sizeSection;

    initSection(section, array, leftIndex, rightIndex,
                thread, NULL, mutex);
    for(cnt = 1;cnt < (threadsCount-1); cnt++)
    {
        leftIndex = rightIndex + 2;
        rightIndex = leftIndex + (sizeSection);
        initSection(section+cnt, array, leftIndex, rightIndex,
                    thread+cnt, mutex+(cnt-1), mutex+cnt);
    }
    initSection(section+threadsCount-1, array, rightIndex+1-1, sizeArray-1,
                thread+(threadsCount-1),mutex+(mutexCount-1), NULL);

    int sectionCount = threadsCount;
    for(cnt = 0;cnt < sectionCount; cnt++)
    {
        pthread_create(section[cnt].thread, NULL, worker, section+cnt);
        printSection(section+cnt);
    }

    for(cnt = 0;cnt < sectionCount; cnt++)
    {
        pthread_join(*(section[cnt].thread), NULL);
        printf("Thread %d has joined\n",(cnt+1));
    }
}*/

void swapValue(int* array, int a, int b)
{
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void fillRandom(int* array, int size)
{
	srand(time(0)*getpid());
	int i;
	for (i=0; i < size; i++)
    {
        array[i] = rand()%(size*3);
	}
}

void printArray(int* array, int size)
{
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

double getTime()
{
	static double start = 0;
	struct timeval tv;
	double now;

	gettimeofday(&tv, 0);
	now = tv.tv_sec + tv.tv_usec / 1e6L;

	if (start)
    {
		now -= start;
	}
	else
	{
		start = now;
		now = 0.L;
	}
	return now;
}

void* multiThreadBubbleSort(void* param)
{
    int i;
    //Bubble sorting algorithm
    for(i = 0; i <= size; i++)
    {
        int j;
        for(j=0; j < size-i; j++)
        {
            if(array[j] > array[j+1])
            {
                swapValue(array, j, j+1);
            }
        }
    }
}

void bubbleSort(int* array, int size)
{
    int i;
    //Bubble sorting algorithm
    for(i = 0; i <= size; i++)
    {
        int j;
        for(j=0; j < size-i; j++)
        {
            if(array[j] > array[j+1])
            {
                swapValue(array, j, j+1);
            }
        }
    }
}
