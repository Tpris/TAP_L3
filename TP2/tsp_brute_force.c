#include "tools.h"

//
//  TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans "tools.h"
// -> tsp_main peut être testé dès les 3 premières fonctions codées
//

double dist(point A, point B) {
  return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

double value(point *V, int n, int *P) {
  double val = 0;
  for(int i = 0; i<n;i++){
    val+=dist(V[P[i%n]], V[P[(i+1)%n]]);
  }
  return val;
}


double tsp_brute_force(point *V, int n, int *Q) {
  int perm[n];
  for(int i = 0; i<n;i++){
    perm[i]=i;
  }
  double min = DBL_MAX;
  do{
    double w = value(V,n,perm);
    if(w<min) {
      min = w;
      for(int i = 0; i<n; i++) {Q[i]=perm[i];}
    }
  }while(NextPermutation(perm,n) && perm[0]==0 && running);
  return min;
}


void MaxPermutation(int *P, int n, int k) {
  int perm[n];
  int r = n-k;
  for(int i = 0; i<k;i++){
    perm[i] = P[i];
  }
  for(int i = k; i<n; i++){
    perm[i]= P[k+r-i];
  }
  P = perm;
  return;
}


double value_opt(point *V, int n, int *P, double w) {
  double distance = 0;
  for(int i = 0; i<n-1;i++){
    distance +=dist(V[P[i]], V[P[i+1]]);
    if(distance+dist(V[P[i+1]],V[P[0]])>w){
      return -(i+2);
    }
  }
  distance += dist(V[P[n-1]],V[P[0]]);
  return distance;
}

double tsp_brute_force_opt(point *V, int n, int *Q) {
  int perm[n];
  for(int i = 0; i<n;i++){
    perm[i]=i;
  }
  double min = DBL_MAX;
  do{
    double w = value_opt(V,n,perm,min);
    if(w<0){MaxPermutation(perm,n,-w);}
    else{
      if(w<min) min = w;
      for(int i = 0; i<n; i++) {Q[i]=perm[i];}
    }
  }while(NextPermutation(perm,n) && perm[0]==0 && running);
  return min;
}


