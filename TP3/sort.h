#include "base.h"
#include <stdio.h>
#include <stdbool.h>

void print_tab(s_data_t tab[], int tab_size);

void bubble_sort(s_data_t tab[], int tab_size);

void insertion_sort(s_data_t tab[], int tab_size);

void selection_sort(s_data_t tab[], int tab_size);

void heap_sort(s_data_t tab[], int tab_size);

void swapDown(s_data_t tab[], int tab_size, int n, int pos);

void tab2heap(s_data_t tab[], int tab_size);

int supprimerMax(s_data_t tab[], int tab_size, int taille);

void quick_sort(s_data_t tab[], int lower, int upper);

int partition(s_data_t tab[], int deb, int fin);