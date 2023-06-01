#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree_primitives.h"

s_base_t chercher(tree_t magasin, int prix);
s_base_t chercher_biggestSmaller(tree_t magasin, int prix);

int main()
{
  s_base_t mini = {"MacMini",600};
  s_base_t macbook = {"MacBook",1300};
  s_base_t iphone = {"iPhone",900};
  s_base_t macpro = {"MacPro",3000};
  s_base_t ipad = {"iPad",850};
  s_base_t imac = {"iMac",1100};

  tree_t Ajb = cons_empty();

  printf("\n----------- INSERT --------------------\n");
  insert(&Ajb,macbook);
  insert(&Ajb,iphone);
  insert(&Ajb,mini);
  insert(&Ajb,macpro);
  insert(&Ajb,ipad);
  insert(&Ajb,imac);
  /*   graphical_print(Ajb,0); */
  int h = height(Ajb);
  int trace_Ajb[h];
  graphical_print_link(Ajb,0,trace_Ajb);
  printf("\n--------------------------------------\n");

  printf("\n----------- MIN/MAX --------------------\n");
  printf("MIN = ");
  print(find_min(Ajb));
  printf("\nMAX = ");
  print(find_max(Ajb));
  printf("\n--------------------------------------\n");

  printf("\n----------- SEARCH --------------------\n");
  print(chercher(Ajb,850));
  printf("\n");
  print(chercher(Ajb,500));
  printf("\n--------------------------------------\n");

  printf("\n----------- REMOVE --------------------\n");
  remove_value(&Ajb,iphone);
  remove_value(&Ajb,macbook);
  remove_value(&Ajb,macpro);
  remove_value(&Ajb,mini);
  remove_value(&Ajb,ipad);
  remove_value(&Ajb,imac);
  graphical_print(Ajb,0);
  h = height(Ajb);
  graphical_print_link(Ajb,0,trace_Ajb);
  printf("\n--------------------------------------\n");

  printf("\n----------- INSERT AVL --------------------\n");
  insert_AVL(&Ajb,mini);
  insert_AVL(&Ajb,macbook);
  insert_AVL(&Ajb,iphone);
  insert_AVL(&Ajb,macpro);
  insert_AVL(&Ajb,ipad);
  insert_AVL(&Ajb,imac);
  h = height(Ajb);
  graphical_print_link(Ajb,0,trace_Ajb);
  /*   graphical_print(Ajb,0); */
  printf("\n--------------------------------------\n");

  printf("\n----------- AFFORDABLE --------------------\n");
  print(chercher_biggestSmaller(Ajb,950));
  printf("\n--------------------------------------\n");

  free_tree(Ajb);

}


s_base_t chercher(tree_t magasin, int prix)
{
  s_base_t article = {"",prix};
  return search(magasin,article);
}

s_base_t chercher_biggestSmaller(tree_t magasin, int prix)
{
  s_base_t article = {"",prix};
  return search_biggestSmaller(magasin,article);
}
