#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

char *palabra; //Variable para guardar las letras
int contador = 0;     //Variable para guardar la posicion de las letras

void listar(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry; //Entrada del directorio a iterar

    if (!(dir = opendir(name))) // Si no existe el directorio, se sale
        return;

    while ((entry = readdir(dir)) != NULL) { // ciclo para leer el directorio hasta que no haya osubdirectorios o archivos
        if (entry->d_type == DT_DIR) { // Si el tipo del archivo es un directorio entonces entra
            char path[1024]; // especificamos un array de char con el nombre del directorio
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue; // comparamos que el nombre sea igual
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            //printf("%*s[%s]\n", indent, "", entry->d_name);
            strcat(palabra, entry->d_name); //Agrega la letra en el array
            contador++;
            //printf("Path: %s\n", path); Path para revisar como recorre los directorios
            listar(path, indent + 2);
        }
    }
    closedir(dir);
    strcat(palabra, "!"); //Agrega un "!" para indicar fin de rama
    contador++;
}

//Voltea el string
void voltear(char* reverso) {
	int j, copia;
	for (int i = 0, j = strlen(reverso)-1; i < j; i++, j--) {
		copia = reverso[i];
		reverso[i] = reverso[j];
		reverso[j] = copia;
	}
}
void copyAndPrint (char *palindroma,int i,int a){
  int k=0;
  char *p = malloc(sizeof(palabra)/sizeof(char));
    for (int j =i; j<strlen(palindroma);j++){
      p[k]= palindroma[j];
      k++;
    }
    if (a == 1){
      printf("%s es palindroma\n", p);
    }else {
       voltear(p);
      printf("%s es palindroma\n", p);
    }
}
//Revisa si la palbra es palíndroma
void esPalindroma(char* palindroma) {
  int len = strlen(palindroma);
  char palindromaReverso[200];
  strcpy(palindromaReverso, palindroma);
  voltear(palindromaReverso);
  char *p = malloc(sizeof(palabra)/sizeof(char));

/*  if (strcmp(palindroma, palindromaReverso) == 0) {
    printf("%s es palindroma\n", palindroma);
  }
*/
  for (int i=0; i <len;i++){
    if ((len-i) >= 3){
      if (palindroma[i] == palindroma[len-1]){
        copyAndPrint(palindroma,i,1);
      }
      if (palindromaReverso[i] == palindromaReverso[len-1]){
        copyAndPrint(palindromaReverso,i,0);
      }
    }
  }
/*  for (int i=len-1; i >=0 ;i--){
    if ((len-i) <= 3){
      if (palindroma[i] == palindroma[0]){
        copyAndPrint(palindroma,i,0);
      }
    }
  }*/
}

//creador de palabras
void creaPalabras() {
  char *palabraPalindroma; //El nodo raíz siempre será el mismo así que se guarda como constante
  palabraPalindroma = malloc (sizeof(palabra)/sizeof(char));

  char *palabraPalindromaEspejo;
  palabraPalindromaEspejo = malloc(sizeof(palabra)/sizeof(char));

  int cont = 0; //Contador de "!" para eliminar letras de las palabras
  int indexPalindroma = 1; //Posición del crea palabras
  int indexPalabra = 1; //Posicion de la palabra
  int len = strlen(palabra); //Conocer el tamaño de la palabra
  int borrador = 0;

  while (indexPalabra < len) {

    palabraPalindroma[0] = palabra[0];

    while (cont > 0) {
      palabraPalindroma[indexPalindroma] = '\0';
      indexPalindroma--;
      cont--;
    }

    while (palabra[indexPalabra] != '!') { //Mientras que no encuentre un "!" en el array, seguirá agregando letras al array
      palabraPalindroma[indexPalindroma] = palabra[indexPalabra];
      indexPalabra++;
      indexPalindroma++;
    }

    while (palabra[indexPalabra] == '!') {
      cont++;
      indexPalabra++;
    }

    strcpy(palabraPalindromaEspejo, palabraPalindroma);

    //bool turno = true;
    if (strlen(palabraPalindroma) >= 3) {
      esPalindroma(palabraPalindroma);
    /*  if (turno) {
        //Quita la primera letra
        memmove(palabraPalindromaEspejo, palabraPalindromaEspejo+1, strlen(palabraPalindromaEspejo));
        turno = !turno
      } else {
        //quita la última letra
        //memmove
        turno = !turno;
      }*/
    }
    len--;
  }
  free(palabraPalindroma);
}

int main(void) {
  int contD=0;
  palabra = malloc (256);
  listar("test-directorios", 0);
  printf("ARBOL [%s]\n", palabra);
  for (int i=0;i<strlen(palabra);i++){
    if (palabra[i] != "!") {
      contD++;
    }
  }
  //if (contD<= 20){
    creaPalabras();

  free(palabra);
  return 0;
}
