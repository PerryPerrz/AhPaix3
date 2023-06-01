#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "base.h"

int compare(s_base_t t1, s_base_t t2){
  return t1.prix - t2.prix;
}

void print(s_base_t t){
  printf("%s (%d euros)  ",t.nom, t.prix);
}
