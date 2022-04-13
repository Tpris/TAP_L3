#include "tools.h"
#include "tsp_brute_force.h"

//
//  TSP - HEURISTIQUES
//

void reverse(int *T, int p, int q) {
  // Renverse la partie T[p]...T[q] du tableau T avec p<q si
  // T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau tableau T sera
  // {0,1, 5,4,3,2, 6}.
  int d = q-p+1;
  for(int i = 0; i<d/2;i++){
    int tmp = T[p+i];
    T[p+i] = T[q-i];
    T[q-i] = tmp;
  }
}

double first_flip(point *V, int n, int *P) {
  // Renvoie le gain>0 du premier flip réalisable, tout en réalisant
  // le flip, et 0 s'il n'y en a pas.
  double gain = 0;
  for(int i = 0; i<=n-3;i++){
    int M = (i==0) ? n-2 : n-1;
    for(int j= i+2; j<=M; j++){
      gain = dist(V[P[j]], V[P[(j+1)%n]]) +
             dist(V[P[i]], V[P[i+1]])     -
             dist(V[P[i]], V[P[j]])       -
             dist(V[P[(j+1)%n]], V[P[i+1]]);
      if(gain>0){
        reverse(P,i+1,j);
        return gain;
      }
    }
  }
  return gain;
}


double tsp_flip(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
  // drawTour() pour visualiser chaque flip.
  for(int i = 0; i<n; i++) { P[i]=i; }
  while(first_flip(V,n,P) && running) drawTour(V,n,P);
  return value(V,n,P);
}

int plusProche(point *V, int n, int *P, int pos){
  double dist_min = dist(V[P[pos]],V[P[pos+1]]);
  int pos_min = pos+1;
  for(int i = pos+2; i<n; i++) {
    double d = dist(V[P[pos]],V[P[i]]);
    if(d<dist_min){
      dist_min = d;
      pos_min = i;
    }
  }
  return pos_min;
}

double tsp_greedy(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i.
  for(int i = 0; i<n; i++) { P[i]=i; }
  for(int i = 0; i<n-1; i++){
    int posProche = plusProche(V,n,P,i);
    reverse(P,i+1,posProche);
  }
  return value(V,n,P);
}
