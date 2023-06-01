#include "sort.h"

void print_tab(s_data_t tab[], int tab_size)
{
    printf("tab : { ");
    for (int i = 0; i < tab_size; ++i)
    {
        print(tab[i]);
        printf(",");
    }
    printf("%d }", tab[tab_size - 1]);
}

void bubble_sort(s_data_t tab[], int tab_size)
{
    s_data_t temp;
    for (int i = 0; i < tab_size - 1; ++i)
    {
        for (int j = 0; j < tab_size - 1; ++j)
        {
            if (compare(tab[j], tab[j + 1]) > 0) //Si tab[j] > tab[j+1]
            {
                /* On swap les valeurs */
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(s_data_t tab[], int tab_size)
{
    int k;
    s_data_t v;
    bool find;
    for (int i = 1; i <= tab_size - 1; ++i)
    {
        v = tab[i];
        k = i;
        find = false;
        while (k > 0 && !find)
        {
            if (compare(v, tab[k - 1]) > 0)
            {
                find = true;
            }
            else
            {
                tab[k] = tab[k - 1];
                --k;
            }
        }
        tab[k] = v;
    }
}

void selection_sort(s_data_t tab[], int tab_size)
{
    s_data_t temp;
    for (int i = 0; i < tab_size - 1; ++i)
    {
        for (int j = i + 1; j < tab_size; ++j)
        {
            if (compare(tab[i], tab[j]) > 0)
            {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

void heap_sort(s_data_t tab[], int tab_size)
{
    int taille;
    s_data_t temp;
    tab2heap(tab, tab_size);
    taille = tab_size;
    for (int i = 0; i < tab_size - 1; ++i)
    {
        temp = supprimerMax(tab, tab_size, taille);
        tab[taille - 1] = temp;
        --taille;
    }
}

void swapDown(s_data_t tab[], int tab_size, int n, int pos)
{
    int left, right, posMax;
    s_data_t temp;
    if (pos < tab_size / 2)
    { //Pas une feuille
        left = 2 * pos + 1;
        right = 2 * pos + 2;
        if (right < tab_size)
        { //Right n'est pas vide
            if (compare(tab[left], tab[right]) > 0)
            {
                posMax = left;
            }
            else
            {
                posMax = right;
            }
        }
        else
        { //Right vide
            posMax = left;
        }
    }
    if (compare(tab[pos], tab[posMax]) < 0)
    {
        temp = tab[pos];
        tab[pos] = tab[posMax];
        tab[posMax] = temp;
        swapDown(tab, tab_size, n, pos);
    }
}

void tab2heap(s_data_t tab[], int tab_size)
{
    for (int i = tab_size / 2 - 1; i > 0; --i)
    {
        swapDown(tab, tab_size, tab_size, i);
    }
}

s_data_t supprimerMax(s_data_t tab[], int tab_size, int taille)
{
    s_data_t max;
    max = tab[0];
    tab[0] = tab[taille - 1];
    --taille;
    swapDown(tab, tab_size, taille, 0);
    return max;
}

void quick_sort(s_data_t tab[], int lower, int upper)
{
    int p;
    if (lower < upper)
    {
        p = partition(tab, lower, upper);
        quick_sort(tab, lower, p);
        quick_sort(tab, p + 1, upper);
    }
}

int partition(s_data_t tab[], int deb, int fin)
{
    int i, j;
    s_data_t pivot, temp;
    i = deb;
    j = fin;
    pivot = tab[deb];

    while (true)
    {
        while (compare(tab[j], pivot) <= 0)
        {
            --j;
        }

        while (compare(tab[i], pivot) >= 0)
        {
            ++i;
        }

        if (i < j)
        {
            temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
        else
        {
            return j;
        }
    }
}