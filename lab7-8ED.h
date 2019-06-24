#include<stdio.h>
#include<stdlib.h>

#define t 2 //el grado de arbol
//#define punterosNodo	(t*2)
//#define clavesNodo punterosNodo - 1
//peor de los casos log base 3 cantidad de nodos

typedef struct _nodoB{
  int claves[2*t-1];
  int hijos[2*t];
  int esHoja;
  int cantidadActual;
  int miNombre;
}nodoB;

typedef struct _arbolB{
	int raiz;
	int cantidadNodos;
}arbolB;

nodoB *creaNodo();
int insertaArchivo(nodoB *);
nodoB *leerArchivo(int);
void imprimirNodo(nodoB *);
nodoB *insertarEnArbolB(arbolB *T, int k);
nodoB *divideHijoArbolB(int, int);
nodoB *insertaNoLLenoArbol(nodoB*, int);

nodoB *creaNodo(){
  nodoB *nuevoNodo = malloc(sizeof(nodoB));
  int i;
  for(i = 0; i < (2*t - 1); i++){
    nuevoNodo->claves[i] = i;
  }
  for(int j = 0; j < 2*t; j++){
      nuevoNodo->hijos[j] = j;
  }
  nuevoNodo->esHoja = 1;
  nuevoNodo->cantidadActual = i;
  nuevoNodo->miNombre = 1;
  return nuevoNodo;
}



nodoB *creaNodoVacio(){
  nodoB *nuevoNodo = malloc(sizeof(nodoB));
  for(int i = 0; i < (2*t - 1); i++){
    nuevoNodo->claves[i] = 0;
  }
  for(int j = 0; j < 2*t; j++){
      nuevoNodo->hijos[j] = 0;
  }
  nuevoNodo->cantidadActual = 0;
  return nuevoNodo;
}

int insertaArchivo(nodoB *nodo){
  FILE *p;
  char strNombreNodo[12];
  sprintf(strNombreNodo,"%i",(nodo->miNombre));
  p = fopen(strNombreNodo,"wb");
  fwrite(nodo,sizeof(nodoB),1,p);
  fclose(p);
}

nodoB *leerArchivo(int nombreNodo){
  FILE *p;
  char strNombreNodo[12];
  sprintf(strNombreNodo,"%d",nombreNodo);
  p = fopen(strNombreNodo,"rb");
  nodoB *nuevoNodo = malloc(sizeof(nodoB));
  fread(nuevoNodo,sizeof(nodoB),1,p);
  return nuevoNodo;
  fclose(p);
}

void imprimirNodo(nodoB *nodo){
  for(int i = 0; i < (2*t - 1); i++){
      printf("clave[%i] : %i ",i,nodo->claves[i]);
  }
  printf("cantidadActual: %i", nodo->cantidadActual);
  printf("\n");
  for(int j = 0; j < 2*t; j++){
      printf("hijo[%i] : %i ",j,nodo->hijos[j]);
  }
  printf("\n");
}

nodoB *insertarEnArbolB(arbolB *T, int k){
    printf("entra\n");
		nodoB *r = leerArchivo(T->raiz);
    printf("cantidad actual: %i\n",r->cantidadActual);
		if(r->cantidadActual == (2*t - 1)){ //si el nodo está lleno, divide.
      printf("\nlleno\n");
			nodoB *s = creaNodoVacio();
			T->raiz = s->miNombre; //Set the new node to T's Root.
			s->esHoja = 0;
			s->cantidadActual = 0;
			s->hijos[0] = r->miNombre; // el primer hijo será 'r'
		  divideHijoArbolB(s->miNombre, 0);//Raiz es el primer hijo de s
			//insertaNoLLenoArbol(s, k); //Insert X into non-full node.
		//}else{
			//insertaNoLLenoArbol(r, k);
		}
	return r;
}

nodoB *divideHijoArbolB(int nombreRaiz, int i){
  int j;
  nodoB *hermanoZ = creaNodoVacio();
  nodoB *padreX = leerArchivo(nombreRaiz);
  nodoB *hermanoY = leerArchivo(padreX->hijos[i]);
  hermanoZ->esHoja = hermanoY->esHoja;
  hermanoZ->cantidadActual = (t - 1);
  for(int j = 0; j < (t - 1); j++){
    hermanoZ->claves[j] = hermanoY->claves[j+t];
  }
  if(!(hermanoY->esHoja)){
    for(j = 0; j < t; j++){
      hermanoZ->hijos[j] = hermanoY->hijos[j+t];
    }
  }
  hermanoY->cantidadActual = (t - 1);
  for(j = (padreX->cantidadActual + 1); j > (i + 1); j--){
    padreX->hijos[i + 1] = padreX->hijos[j];
  }
  padreX->hijos[i + 1] = hermanoZ->miNombre;
  for(j = (padreX->cantidadActual); j > i; j--){
    padreX->claves[j+1] = padreX->claves[j];
  }
  padreX->claves[i] = hermanoY->claves[t];
  padreX->cantidadActual = (padreX->cantidadActual + 1);
  imprimirNodo(hermanoY);
  imprimirNodo(hermanoZ);
  imprimirNodo(padreX);
  insertaArchivo(hermanoY);
  insertaArchivo(hermanoZ);
  insertaArchivo(padreX);
}
