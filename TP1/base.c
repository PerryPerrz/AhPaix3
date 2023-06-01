#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "base.h"

int compare(s_base_t t1, s_base_t t2){
  int res=0;
  if(t1.nature==t2.nature){
    switch(t1.nature){
    case Constante:
      if(t1.val==t2.val){
        res=1;
      }
      break;
    case Variable:
    case Binaire:
    case Fonction:
      if(strcmp(t1.oper,t2.oper)==0){
        res=1;
      }
      break;
    }
  }
  return res;
}

void print(s_base_t t){
  switch(t.nature){
    case Constante:
      printf("%d",t.val);
      break;
    case Variable:
    case Binaire:
    case Fonction:
      printf("%s",t.oper);
      break;
  }
}
