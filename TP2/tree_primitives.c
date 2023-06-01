#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tree_primitives.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


tree_t cons_empty()
{
  /* Pas besoin d'allouer de la mémoire inutilement et de créer un nœud.
   * Retourner NULL suffit. */
  return NULL; 
}

tree_t cons(s_base_t v, tree_t fg, tree_t fd)
{
  /* On alloue uniquement la mémoire pour le nœud que l'on crée. v, fg et fd
   * ont déjà été créés, la mémoire a donc déjà été allouée.*/
  tree_t a = (tree_t) malloc(sizeof(s_node_t));
  /* affectations */
  a->val = v ;
  a->fg = fg;
  a->fd = fd ;
  a->height = 0 ;
  return a ; 
}

int is_empty(tree_t a)
{
  /* Dans le cas où la restitution de l'arbre vide serait implémentée
   * différemment, le test de vacuité serait différent : il faudrait tester les
   * pointeurs de a */
  return a == NULL;
}

s_base_t value(tree_t a)
{
  return a->val;
}

tree_t left(tree_t a)
{
  return a->fg ; 
}

tree_t right(tree_t a)
{
  return a->fd; 
}

void change_value(tree_t pa, s_base_t new_value)
{
  pa->val = new_value; 
}

void change_left(tree_t pa, tree_t new_left)
{
  pa->fg = new_left; 
}

void change_right(tree_t pa, tree_t new_right)
{
  pa->fd = new_right; 
}

void free_tree(tree_t a)
{
  /* test indispensable pour traiter le cas de l'arbre vide à libérer */
  if(!is_empty(a)) {
  /* On libére d'abord récursivement la mémoire sur les fils gauche et
   * droit, puis sur le nœud lui-même. */
    free_tree(left(a));
    free_tree(right(a));
    free(a);
  }
}

/* Parcours préfixe : donnée préfixe(fils_gauche) préfixe(fils_droit) */
void prefix(tree_t a)
{
  if (!is_empty(a)) {
    print(value(a));
    prefix(left(a));
    prefix(right(a));
  }
}

/* Parcours infixe :  préfixe(fils_gauche) donnée préfixe(fils_droit) */
void infix(tree_t a)
{
  if (!is_empty(a)) {
    infix(left(a));
    print(value(a));
    infix(right(a));
  }
}

/* On passe la profondeur en paramètre pour obtenir une indentation cohérente */
void graphical_print(tree_t a, int depth)
{
  if (!is_empty(a)) {
    for(int i=0;i<depth;i++) {
      printf(" ");
    }
    printf("+--"); 
    print(value(a));
    printf("\n");
    graphical_print(left(a),depth+3);
    graphical_print(right(a),depth+3);
  }
}

/* Affichage avec mise en forme "graphique" (indentation ET LIEN en fonction de la profondeur) 
   - la trace enregistre la direction: 0 Left, 1 Right
*/
void graphical_print_link(tree_t a, int depth, int trace[])
{
  if(!is_empty(a)){
    // Appels récursifs sur le fils gauche, en augmentant le décalage, en précisant qu'on va à gauche
    trace[depth]=0;
    graphical_print_link(left(a), depth+1, trace);
    // affichage de la racine 
    for(int i=0; i<depth; ++i){
      // si profondeur > 0 et changement de direction (dans la filiation) il faut afficher le lien
      if(i>0 && trace[i] != trace[i-1]){
        printf("|");
      }else{
        printf(" ");
      }
      // completer avec des espaces
      printf("  ");
    }
    printf("@----");
    print(value(a));
    printf("\n");
    // Appels récursifs sur le fils gauche, en augmentant le décalage, en précisant qu'on va à droite
    trace[depth]=1;
    graphical_print_link(right(a), depth+1, trace);
  }else{
    for(int i=0; i<depth; ++i){
      // si profondeur > 0 et changement de direction (dans la filiation) il faut afficher le lien
      if(i>0 && trace[i] != trace[i-1]){
        printf("|");
      }else{
        printf(" ");
      }
      // completer avec des espaces
      printf("  ");
    }
    printf("  \n");
  }
}

int size(tree_t a)
{
  int size_a=0;
  if (!is_empty(a)) {
    /* La taille d'un arbre correspond à la somme des tailles de ses fils + 1
     * (le nœud courrant. If faut donc faire deux appels récursifs. */
    size_a = 1 + size(left(a)) + size(right(a)); 
  }
  //Dans le cas de l'arbre vide, la taille vaut 0 (initialisation de size_a en
  //début de fonction)
  return size_a;
}


int height(tree_t a)
{
  int height_a=0;
  if (!is_empty(a)) {
    /* La hauteur d'un arbre correspond à 1 + le max des hauteurs de ses fils.
     * Il faut donc deux appels récursifs.
     * Comme il faut accéder deux fois à la hauteur d'un fils, on stocke les
     * hauteurs dans des variables pour plus d'efficacité.
     */
    int hfg=height(left(a));
    int hfd=height(right(a));
    height_a = 1+((hfg) > (hfd) ? hfg : hfd);
  }
  return height_a;
}

/* On peut aussi implémenter cette fonction en utilisant un _Bool. Mais on
 * tâche d'être cohérent si on a commencé à implémenter compare() sans _Bool
 * mais avec des int. */
int exists(tree_t a, s_base_t v)
{
  if (is_empty(a)) {
    return 0;
  } else {
    if (compare(value(a),v)==0) {
      return 1;
    } else {
      /* Appels récursifs : si on n'a pas trouvé v, il faut tester sa présence
       * dans les fils gauche et droit */
      return (exists(left(a),v) || exists(right(a),v));
    }
  }
}

/****************************************************
 * Partie specifique aux arbres ordones
 *****************************************************/

// q1
/* Inserer val a la bonne position dans l'arbre */
void insert(tree_t* a, s_base_t val){
  tree_t tree_temp;

  if(is_empty(*a)){
    *a = cons(val, cons_empty(),cons_empty());
  }
  else{
      if(compare(val,value(*a)) < 0){ //Insertion à gauche
        tree_temp = left(*a);
        insert(&tree_temp, val);
        change_left(*a,tree_temp);
      }
      else{ //Insertion à droite
        tree_temp = right(*a);
        insert(&tree_temp, val);
        change_right(*a,tree_temp);
      }
  }
}

// q2
/* Trouver le min dans l'arbre; article avec prix = -1 if empty tree */
s_base_t find_min(tree_t a){
  s_base_t res={"",-1}; //Si l'arbre est vide

  if(!is_empty(a)){
      if(is_empty(left(a))){
        res = value(a);
      }
      else{
        res = find_min(left(a));
      }
  }
  return res;
}

/* /\* Trouver le min dans l'arbre; article avec prix = -1 if empty tree *\/ */
s_base_t find_max(tree_t a){
  s_base_t res={"",-1}; //Si l'arbre est vide
  
  if(!is_empty(a)){
      if(is_empty(right(a))){
        res = value(a);
      }
      else{
        res = find_max(right(a));
      }
  }
  return res;
}

// q3
/* Chercher val dans l'arbre */
s_base_t search(tree_t a, s_base_t val){
  s_base_t res= {"",-1};

  if(!is_empty(a)){ //L'arbre n'est pas vide
    if(compare(val, value(a)) == 0){
      res = value(a);
    }
    else{ //val < value(a) || val > value(a)
      if(compare(val, value(a)) < 0){
        res = search(left(a),val);
      }
      else{ //val > value(a)
        res = search(right(a),val);
      }
    }
  }
  return res;
}

// q4
/* Enlever val de l'arbre */
void remove_value(tree_t *a, s_base_t val){
  tree_t tree_temp;
  if(!is_empty(*a)){ //Si l'arbre n'est pas vide
    if(compare(val, value(*a)) < 0){
      tree_temp = left(*a);
      remove_value(&tree_temp, val); //On supprime à gauche
      change_left(*a,tree_temp);
    }
    else if(compare(val, value(*a)) > 0){
      tree_temp = right(*a);
      remove_value(&tree_temp, val); //On supprime à droite
      change_right(*a,tree_temp);
    } 
    else{
      if(is_empty(left(*a)) && is_empty(right(*a))){ //compare(val, value(a) == 0 & si la racine est une feuille
        *a = cons_empty();
        free_tree(*a);
      }
      else if(is_empty(right(*a))){ //Si le fils droit est vide, on s'occupe du fils gauche
        *a = left(*a);
      }
      else if(is_empty(left(*a))){ //Si le fils gauche est vide, on s'occupe du fils droit
        *a = right(*a);
      }
      else{ //La racine à obligatoirement 2 fils
        change_value(*a, find_max(left(*a))); // On remplace la racine par le max du fils gauche
        //On supprime récursivement cette valeur du fils gauche
        tree_temp = left(*a);
        supprimer_max(&tree_temp);
      }
    }
  }
}

//Fonction qui supprime le max d'un arbre
void supprimer_max(tree_t* a){
  tree_t tree_temp;
  if(is_empty(right(*a))){
    tree_temp = *a;
    *a = left(*a);
    change_left(tree_temp, cons_empty());
    free_tree(tree_temp);
  }
  else{
    tree_temp = right(*a);
    supprimer_max(&tree_temp);
    change_right(*a, tree_temp);
  }
}

// q5
/* Inserer val a la bonne position dans l'arbre; l'arbre doit rester equilibre */
void insert_AVL(tree_t* a, s_base_t val){
  tree_t tree_temp,tree_tempbis;
  //Je m'occupe d'insérer la valeur
  if(is_empty(*a)){
    *a = cons(val, cons_empty(), cons_empty());
  }
  else{
    if(compare(val, value(*a)) > 0){
      tree_temp = right(*a);
      insert_AVL(&tree_temp, val);
      change_right(*a, tree_temp);
    }
    else{
      if(compare(val, value(*a)) < 0){
        tree_temp = left(*a);
        insert_AVL(&tree_temp, val);
        change_left(*a, tree_temp);
      }
    }
  }

  //Je m'occupe de ré-équilibrer l'arbre
  int fe = height(left(*a)) - height(right(*a));
  if(fe > 1 && compare(val, value(*a)) < 0){
    rotationDroite(a);
  }
  else if (fe > 1 && compare(val, value(*a)) >= 0){
    tree_tempbis = left(*a);
    rotationGauche(&tree_tempbis);
    change_left(*a, tree_tempbis);
    rotationDroite(a);
  }
  else if (fe < -1 && compare(val, value(*a)) <= 0){
    rotationDroite(a);
  }
  else if (fe < -1 && compare(val, value(*a)) > 0){
    tree_tempbis = right(*a);
    rotationDroite(&tree_tempbis);
    change_right(*a, tree_tempbis);
    rotationGauche(a);
  }
}

//Fonction qui permet d'effectuer une rotation droite sur un arbre
void rotationDroite(tree_t* a){
  tree_t fg;
  fg = left(*a);
  change_left(*a,right(fg));
  change_right(fg,*a);
  *a = fg;
}

//Fonction qui permet d'effectuer une rotation gauche sur un arbre
void rotationGauche(tree_t* a){
  tree_t fd;
  fd = right(*a);
  change_right(*a,left(fd));
  change_left(fd,*a);
  *a = fd;
}

// q6
/* Chercher la plus grande valeur plus petite que val dans l'arbre; article avec prix = -1 si pas possible */
s_base_t search_biggestSmaller(tree_t a, s_base_t val){
  s_base_t res={"",-1};
  if(!is_empty(a)){
    if(compare(val, value(a)) == 0){
      res = find_max(right(a));
    }
    else{
      if(compare(val, value(a)) < 0){
        res = search_biggestSmaller(left(a), val);
      }
      else{ //compare(val, value(a)) > 0
        res = value(a);
      }
    }
  }
  return res;
}

