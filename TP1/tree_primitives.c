#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tree_primitives.h"

#define PI 3.14159265

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
    /* free(value(a).oper); */
    free(a);
  }
}

/* Parcours préfixe : donnée préfixe(fils_gauche) préfixe(fils_droit) */
void prefix(tree_t a)
{
  /* Test pour traiter le cas de l'arbre vide */
  if (!is_empty(a)) {
    /* Affichage de la donnée de l'arbre */
    print(value(a));
    // Appels récursifs sur les fils gauche et droit
    prefix(left(a));
    prefix(right(a));
  }
}

/* On passe la profondeur en paramètre pour obtenir une indentation cohérente */
void graphical_print(tree_t a, int depth)
{
  if (!is_empty(a)) {
    // affichage de la racine 
    for(int i=0;i<depth;i++) {
      printf(" ");
    }
    printf("@--"); 
    print(value(a));
    printf("\n");
    // Appels récursifs sur le fils gauche, en augmentant le décalage
    graphical_print(left(a),depth+3);
    // Appels récursifs sur le fils droit, en augmentant le décalage
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
    printf("@--");
    print(value(a));
    printf("\n");
    // Appels récursifs sur le fils gauche, en augmentant le décalage, en précisant qu'on va à droite
    trace[depth]=1;
    graphical_print_link(right(a), depth+1, trace);
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
 * Partie specifique aux expressions mathematiques
 *****************************************************/

void tree_print(tree_t a)
{
  if( ! is_empty(a)){
    switch(value(a).nature){
      case Constante:
      case Variable:
        print(value(a));
        break;
      case Binaire:
        printf("(");
        tree_print(left(a));
        print(value(a));
        tree_print(right(a));
        printf(")");
        break;
      case Fonction:
        print(value(a));
        printf("(");
        tree_print(left(a));
        printf(")");
        break;
      default:
        printf("ERROR");
    }
  }
}


double evaluate(tree_t a, int val){
  double res=0;
  if( ! is_empty(a)){
    int ev_left=evaluate(left(a),val);
    int ev_right=evaluate(right(a),val);
    switch(value(a).nature){
      case Constante:
        res=value(a).val;
        break;
      case Variable:
        res=val;
        break;
      case Binaire:
        if(strcmp(value(a).oper,"+")==0){
          res=ev_left+ev_right;
        }else{
          if(strcmp(value(a).oper,"*")==0){
            res=ev_left*ev_right;
          }else{
            if(strcmp(value(a).oper,"-")==0){
              res=ev_left-ev_right;
            }
          }
        };
        break;
      case Fonction:
        if(strcmp(value(a).oper,"sin")==0){
          res=sin(ev_left*PI/180);
        }else{
          if(strcmp(value(a).oper,"cos")==0){
            res=cos(ev_left*PI/180);
          }
        };
        break;
    }
  }
  return res;
}



tree_t copy_tree(tree_t a){
  tree_t res=cons_empty();
  if( ! is_empty(a)){
    tree_t copy_left=copy_tree(left(a));
    tree_t copy_right=copy_tree(right(a));
    res=cons(value(a),copy_left,copy_right);
  }
  return res;
}

tree_t derivate(tree_t a){
  tree_t res=cons_empty();
  if( ! is_empty(a)){
    tree_t deriv_left=derivate(left(a));
    tree_t deriv_right=derivate(right(a));
    s_base_t opplus={Binaire,0,"+"};
    s_base_t optimes={Binaire,0,"*"};
    s_base_t opminus={Binaire,0,"-"};
    s_base_t funcos={Fonction,0,"cos"};
    s_base_t funsin={Fonction,0,"cos"};
    s_base_t zero={Constante,0,""};
    switch(value(a).nature){
      case Constante:
        {
          s_base_t cnst={Constante,0,""};
          res=cons(cnst,cons_empty(),cons_empty());
        }
        break;
      case Variable:
        {
          s_base_t cnst={Constante,1,""};
          res=cons(cnst,cons_empty(),cons_empty());
        }
        break;
      case Binaire:
        {
          if(strcmp(value(a).oper,"+")==0){
            res=cons(opplus,deriv_left,deriv_right);
          }else{
            if(strcmp(value(a).oper,"*")==0){
              tree_t copieFG=copy_tree(left(a));
              tree_t copieFD=copy_tree(right(a));
              res=cons(opplus,cons(optimes,deriv_left,copieFD),cons(optimes,deriv_right,copieFG));
            }else{
              if(strcmp(value(a).oper,"-")==0){
                res=cons(opminus,deriv_left,deriv_right);
              }
            }
          }
        }
        break;
      case Fonction:
        {
          tree_t copieFG=copy_tree(left(a));
          if(strcmp(value(a).oper,"sin")==0){
            res=cons(optimes,deriv_left,cons(funcos,copieFG,cons_empty()));
          }else{
            if(strcmp(value(a).oper,"cos")==0){
              res=cons(optimes,deriv_left,cons(opminus,cons(zero,cons_empty(),cons_empty()),cons(funsin,copieFG,cons_empty())));              
            }
          };
        }
        break;
    }
  }
  return res;
}

tree_t build_tree(const char* exp, int debut, int* fin){
  tree_t res=cons_empty();

  if(exp[debut]=='('){ // Expression paranthesee
    int finop1,finop2;
    tree_t op1=build_tree(exp,debut+1,&finop1);
    char* oper=(char*)malloc(2);
    oper[0]=exp[finop1+1];    
    oper[1]='\0'; 
    s_base_t opr={Binaire,0,oper};
    tree_t op2=build_tree(exp,finop1+2,&finop2);
    *fin=finop2+1;
    res=cons(opr,op1,op2);
  }else{
    if(exp[debut]=='X'){ //Variable
      char* nomVar="X";    
      s_base_t var={Variable,0,nomVar};
      *fin=debut;
      res=cons(var,cons_empty(),cons_empty());
    }else{ 
      if(exp[debut]>'0' && exp[debut]<='9'){ // Constante
        char ct[10];
        int i=0;
        while(exp[debut]>='0' && exp[debut]<='9'){
          ct[i++]=exp[debut++];
        }
        int nb=atoi(ct);
        s_base_t cnst={Constante,nb,""};
        *fin=debut-1;
        res=cons(cnst,cons_empty(),cons_empty());
      }else{ // Function
        char* fun=malloc(10*sizeof(char));
        int i=0;
        while((exp[debut]>='a' && exp[debut]<='z') || (exp[debut]>='A' && exp[debut]<='Z') ){
          fun[i++]=exp[debut++];
        } // debut on '('
        fun[i]='\0';
        char* nomFun = (char*)malloc(i);
        strcpy(nomFun,fun);
        free(fun);
        s_base_t funct={Fonction,0,nomFun};
        int finop;
        tree_t arg=build_tree(exp,debut+1,&finop);
        *fin=finop+1;
        res=cons(funct,arg,cons_empty());
      }
    }
  }
  return res;
}


