#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "base.h"

int compare(s_data_t t1, s_data_t t2){
  return t1-t2;
/*   int cmpNom=strcmp(t1.nom,t2.nom); */
/*   int cmpPrenom=strcmp(t1.prenom,t2.prenom); */
/*   if(cmpNom==0){ */
/*     return cmpPrenom; */
/*   }else{ */
/*     return cmpNom; */
/*   } */
}

void print(s_data_t t){
  printf("%d ",t);
/*  printf("%s %s (%d)  ",t.nom, t.prenom,t.dateNaissance); */
}
