#include "lab7-8ED.h"

int main(){
  int opc,k;
  nodoB *nodo = creaNodo();
  arbolB *T = malloc(sizeof(arbolB));
  T->raiz = nodo->miNombre;
  T->cantidadNodos = 1;
  int nombreNodo = 1;
  printf("1.- Insertar nodo en archivo\n2.- Leer nodo del archivo\n3.-Insertar valor en arbol\n");
  scanf("%i",&opc);
  switch (opc) {
    case 1: insertaArchivo(nodo);
    break;
    case 2:
    nodo = leerArchivo(nombreNodo);
    imprimirNodo(nodo);
    break;
    case 3:
      printf("Digite un valor para insertar en el arbol: ");
      scanf("%i",&k);
      nodo = insertarEnArbolB(T,k);
    break;
  }
}

//https://gist.github.com/yorickdewid/d86e14cb2f3929823841
