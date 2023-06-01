#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tree_primitives.h"


#define PI 3.14159265


void tree_print_reference(tree_t a)
{
  if( ! is_empty(a)){
    switch(value(a).nature){
      case Constante:
      case Variable:
        print(value(a));
        break;
      case Binaire:
        printf("(");
        tree_print_reference(left(a));
        print(value(a));
        tree_print_reference(right(a));
        printf(")");
        break;
      case Fonction:
        print(value(a));
        printf("(");
        tree_print_reference(left(a));
        printf(")");
        break;
      default:
        printf("ERROR");
    }
  }
}

tree_t build_tree_reference(const char* exp, int debut, int* fin){
  tree_t res=cons_empty();

  if(exp[debut]=='('){ // Expression paranthesee
    int finop1,finop2;
    tree_t op1=build_tree_reference(exp,debut+1,&finop1);
    char* oper=(char*)malloc(2);
    oper[0]=exp[finop1+1];    
    oper[1]='\0';
    s_base_t opr={Binaire,0,oper};
    tree_t op2=build_tree_reference(exp,finop1+2,&finop2);
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
        tree_t arg=build_tree_reference(exp,debut+1,&finop);
        *fin=finop+1;
        res=cons(funct,arg,cons_empty());
      }
    }
  }
  return res;
}

double evaluate_reference(tree_t a, int val){
  double res=0;
  if( ! is_empty(a)){
    double ev_left=evaluate_reference(left(a),val);
    double ev_right=evaluate_reference(right(a),val);
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

tree_t copy_tree_reference(tree_t a){
  tree_t res=cons_empty();
  if( ! is_empty(a)){
    tree_t copy_left=copy_tree_reference(left(a));
    tree_t copy_right=copy_tree_reference(right(a));
    res=cons(value(a),copy_left,copy_right);
  }
  return res;
}

tree_t derivate_reference(tree_t a){
  tree_t res=cons_empty();
  if( ! is_empty(a)){
    tree_t deriv_left=derivate_reference(left(a));
    tree_t deriv_right=derivate_reference(right(a));
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
              tree_t copieFG=copy_tree_reference(left(a));
              tree_t copieFD=copy_tree_reference(right(a));
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
          tree_t copieFG=copy_tree_reference(left(a));
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


int compare_tree(tree_t a, tree_t b)
{
  if(is_empty(a)) {
    if(is_empty(b)) {
      return 1;
    }else{
      return 0;
    }
  }else{
    if(is_empty(b)) {
      return 0;
    }else{
      if(compare(value(a),value(b))==1){
        return compare_tree(left(a),left(b))==1 && compare_tree(right(a),right(b))==1;
      }else{
        return 0;
      }
    }
  }
}




int main()
{
  int fin;

  tree_t arb = build_tree_reference("(3+2)",0,&fin);
  tree_print(arb);
  printf("\n");
  double ev = evaluate(arb,10);
  double ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  tree_t der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);    

  arb = build_tree_reference("((3+2)*(1+4))",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);   
 
  arb = build_tree_reference("(33+22)",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);    

  arb = build_tree_reference("(X+2)",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);    

  arb = build_tree_reference("((X+2)*(1+X))",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);    
  
  arb = build_tree_reference("(1+sin(X))",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);    

  arb = build_tree_reference("((1+sin(X))*(cos(X)+5))",0,&fin);
  tree_print(arb);
  printf("\n");
  ev = evaluate(arb,10);
  ev_ref = evaluate_reference(arb,10);
  if(ev != ev_ref){
    printf("  Error EVALUATE\n");
  }
  der = derivate(arb);
  ev = evaluate(der,10);
  free_tree(der);
  der = derivate_reference(arb);
  ev_ref = evaluate_reference(der,10);
  free_tree(der);
  if(ev != ev_ref){
    printf("  Error DERIVATE \n");
  }
  free_tree(arb);

  // TEST build_tree

  tree_t arb_ref = build_tree_reference("(3+2)",0,&fin);
  arb = build_tree("(3+2)",0,&fin);
  tree_print(arb);
  printf("\n");
  /* ev = evaluate(arb,10); */
  /* ev_ref = evaluate_reference(arb_ref,10); */
  if(compare_tree(arb,arb_ref)==0){
    /* printf("  Error BUILD. Val=%f. Val ref=%f \n",ev,ev_ref); */
    printf("  Error BUILD. \n");
  }
  free_tree(arb);    
  free_tree(arb_ref);    

  arb_ref = build_tree_reference("((3+2)*(1+4))",0,&fin);
  arb = build_tree("((3+2)*(1+4))",0,&fin);
  tree_print(arb);
  printf("\n");
  /* ev = evaluate(arb,10); */
  /* ev_ref = evaluate_reference(arb_ref,10); */
  if(!compare_tree(arb,arb_ref)){
    /* printf("  Error BUILD. Val=%f. Val ref=%f \n",ev,ev_ref); */
    printf("  Error BUILD. \n");
  }
  free_tree(arb);    
  free_tree(arb_ref);    

  arb_ref = build_tree_reference("((X+2)*(1+X))",0,&fin);
  arb = build_tree("((X+2)*(1+X))",0,&fin);
  tree_print(arb);
  printf("\n");
  /* ev = evaluate(arb,10); */
  /* ev_ref = evaluate_reference(arb_ref,10); */
  if(!compare_tree(arb,arb_ref)){
    /* printf("  Error BUILD. Val=%f. Val ref=%f \n",ev,ev_ref); */
    printf("  Error BUILD. \n");
  }
  free_tree(arb);    
  free_tree(arb_ref);    

  arb_ref = build_tree_reference("(1+sin(X))",0,&fin);
  arb = build_tree("(1+sin(X))",0,&fin);
  tree_print(arb);
  printf("\n");
  /* ev = evaluate(arb,10); */
  /* ev_ref = evaluate_reference(arb_ref,10); */
  if(!compare_tree(arb,arb_ref)){
    /* printf("  Error BUILD. Val=%f. Val ref=%f \n",ev,ev_ref); */
    printf("  Error BUILD. \n");
  }
  free_tree(arb);    
  free_tree(arb_ref);    

  /* int h = height(arb); */
  /* int traced[h]; */
  /* graphical_print_link(arb,0,traced); */
  /* h = height(arb); */
  /* graphical_print_link(arb_ref,0,traced); */

}
