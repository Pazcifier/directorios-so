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
//Revisa si la palbra es palíndroma

void esPalindroma(char* palindroma) {
  int haciaDerecha = 0;
  int haciaIzquierda = strlen(palindroma) - 1;
  if (haciaIzquierda > 1) {
    while (haciaIzquierda > haciaDerecha) {
      if (palindroma[haciaDerecha++] != palindroma[haciaIzquierda--]) {
        return;
      }else {
        printf("%s es palindroma\n", palindroma);
      }
    }
  }
}

//creador de palabras
void creaPalabras() {
  char *palabraPalindroma; //El nodo raíz siempre será el mismo así que se guarda como constante
  palabraPalindroma = malloc (sizeof(palabra)/sizeof(char));
  palabraPalindroma[0] = palabra[0];

  int cont = 0; //Contador de "!" para eliminar letras de las palabras
  int indexPalindroma = 1; //Posición del crea palabras
  int indexPalabra = 1; //Posicion de la palabra
  int len = strlen(palabra); //Conocer el tamaño de la palabra
  printf("%d",len);
  while (indexPalabra < len) {

    while (cont != 0) {
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

    printf("%s\n",palabraPalindroma);
    if (strlen(palabraPalindroma) >= 3) {
      esPalindroma(palabraPalindroma);
    }

    len--;
    //palabraPalindroma="";
  }
  free(palabraPalindroma);
}

int main(void) {
  palabra = malloc (256);
  listar("test-directorios", 0);
  creaPalabras();
  free(palabra);
  return 0;
}
