//----------------------------------------------------------------
//  |M 1 M| 6 || 7 || 4 || 3 || 9 || 1 || 0 || 5 || 3 || 2 |M 2 M|
//----------------------------------------------------------------
//
//  Ce sch�ma repr�sente une section de tri.
//  Un seul thread s'occupe de cette section.
//  Il comporte au maximum 2 mutex par section (qui sont partag�s entre plusieurs sections)
//      - 1 mutex --> Premi�re section et derni�re section
//      - 2 mutex --> Toutes les sections qui se trouvent entre la premi�re et la derni�re
//

#include "section.h"

void initSection(Section* section, int* array, int leftIndex, int rightIndex, pthread_t* thread,
                 pthread_mutex_t* leftMutex, pthread_mutex_t* rightMutex)
{
    section->array = array;
    section->leftIndex = leftIndex;
    section->rightIndex = rightIndex;
    section->thread = thread;
    section->leftMutex = leftMutex;
    section->rightMutex = rightMutex;
}

void printSection(Section* section)
{
    printf("-------------------------------------------\n");
    printf("Adresse du tableau : %p\n",section->array);
    printf("Index gauche : %d\n",section->leftIndex);
    printf("Index droit : %d\n",section->rightIndex);
    printf("Adresse du thread : %p\n",section->thread);
    printf("Adresse du mutex gauche : %p\n",section->leftMutex);
    printf("Adresse du mutex droit : %p\n",section->rightMutex);
}
