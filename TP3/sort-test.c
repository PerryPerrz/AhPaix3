#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#include "sort.h"

#define MAX 100

// Optional printing of tab
void print_optional(s_data_t tab[], int tab_size, int print){
  if(print){
    print_tab(tab,tab_size);
  }
}

// Check if elements of tab are in increasing order
void check_sorted(s_data_t tab[], int size)
{
  int i;
  char sorted = 1;

  for(i=0; i<size-1 && sorted; ++i){
    if(tab[i] > tab[i+1]){
      sorted = 0;
    }
  }
  if(sorted == 1){
    printf("Contents of tab is ordered\n");
  }else{
    printf("Contents of tab is NOT ordered : %d %d -> %d %d\n", i-1, i, tab[i-1], tab[i]);
  }  
}

// Main program
int main()
{
  int size=1000;
  int print=0;

  struct timeval start, stop;
 
  // Dynamic allocation of tabs
  s_data_t *tab=(int*)malloc(size*sizeof(s_data_t));
  s_data_t *tab_copy=(int*)malloc(size*sizeof(s_data_t));

  // Random initialization of tab
  srand(time(NULL));
  for(int i=0; i<size; i++){
    tab[i]=rand()%size;
  }
  // Printing of tab
  print_optional(tab,size,print);

  // Copy of tab into tab_copy for successive sorts
  memcpy(tab_copy, tab, size*sizeof(s_data_t));

  // Bubble sort
  printf("BUBLE sort: \n");
  gettimeofday(&start,NULL);
  bubble_sort(tab,size);
  gettimeofday(&stop,NULL);
  print_optional(tab,size,print);
  check_sorted(tab, size);
  printf("Finished in %.0f milliseconds. \n", (stop.tv_sec - start.tv_sec) * 1e3
                                            + (stop.tv_usec - start.tv_usec) * 1e-3);
  
  // Copy and printing of initial tab
  memcpy(tab, tab_copy, size*sizeof(s_data_t));
  print_optional(tab,size,print);

  // Insertion sort
  printf("INSERTION sort: \n");
  gettimeofday(&start,NULL);
  insertion_sort(tab,size);
  gettimeofday(&stop,NULL);
  print_optional(tab,size,print);
  check_sorted(tab, size);
  printf("Finished in %.0f milliseconds. \n", (stop.tv_sec - start.tv_sec) * 1e3
                                            + (stop.tv_usec - start.tv_usec) * 1e-3);

  // Copy and printing of initial tab
  memcpy(tab, tab_copy, size*sizeof(s_data_t));
  print_optional(tab,size,print);

  // Selection sort
  printf("SELECTION_SORT sort: \n");
  gettimeofday(&start,NULL);
  selection_sort(tab,size);
  gettimeofday(&stop,NULL);
  print_optional(tab,size,print);
  check_sorted(tab, size);
  printf("Finished in %.0f milliseconds. \n", (stop.tv_sec - start.tv_sec) * 1e3
                                            + (stop.tv_usec - start.tv_usec) * 1e-3);

  // Copy and printing of initial tab
  memcpy(tab, tab_copy, size*sizeof(s_data_t));
  print_optional(tab,size,print);

  // Heap sort
  printf("HEAP sort: \n");
  gettimeofday(&start,NULL);
  heap_sort(tab,size);
  gettimeofday(&stop,NULL);
  print_optional(tab,size,print);
  check_sorted(tab, size);
  printf("Finished in %.0f milliseconds. \n", (stop.tv_sec - start.tv_sec) * 1e3
                                            + (stop.tv_usec - start.tv_usec) * 1e-3);

  // Copy and printing of initial tab
  memcpy(tab, tab_copy, size*sizeof(s_data_t));
  print_optional(tab,size,print);

  // Quick sort
  printf("QUICK sort: \n");
  gettimeofday(&start,NULL);
  quick_sort(tab,0,size-1);
  gettimeofday(&stop,NULL);
  print_optional(tab,size,print);
  check_sorted(tab, size);
  printf("Finished in %.0f milliseconds. \n", (stop.tv_sec - start.tv_sec) * 1e3
                                            + (stop.tv_usec - start.tv_usec) * 1e-3);

  // Deallocation of tabs
  free(tab);
  free(tab_copy);

  return 0;
}

