#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

char *palabra;
 //Variable para guardar las letras
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

void esPalindroma(char* sPalindroma, char * primera) {
  int haciaDerecha = 0;
  char *palindroma = malloc (sizeof(palabra)/sizeof(char));
  strcat(palindroma,primera);
  strcat(palindroma,sPalindroma);
  int haciaIzquierda =strlen(palindroma)-1;
  if (haciaIzquierda > 1){
    while (haciaIzquierda > haciaDerecha) {
      if (palindroma[haciaDerecha] != palindroma[haciaIzquierda]) {
        printf("no es palíndroma\n");
      }else {
        printf("es palindrome\n");
      }
      haciaDerecha=haciaDerecha+1;
      haciaIzquierda= haciaIzquierda-1;
    }
  }
}

//creador de palabras
void creaPalabras() {
  char *primera; //El nodo raíz siempre será el mismo así que se guarda como constante
  primera = malloc (sizeof(palabra)/sizeof(char));
  primera [0] = palabra[0];

  char *palabraPalindroma; //Se crea la variable para guardar la palabra hecha
  palabraPalindroma = malloc (sizeof(palabra)/sizeof(char));
  int cont = 1; //Contador para que empiece a crear palabras a partir del segundo

  while (palabra[cont] != '!') { //Mientras que no encuentre un "!" en el array, seguirá agregando letras al array
  //  strcat(palabraPalindroma, palabra[cont]);
  int len = strlen(palabraPalindroma);
        palabraPalindroma[len] = palabra[cont];
        palabraPalindroma[len+1] = '\0'; //Esto es el strcat para anexar un char a un string
  //palabraPalindroma[cont] = palabra[cont];
    cont++;
  }
  printf("%s\n",palabraPalindroma);
  esPalindroma(palabraPalindroma,primera);
}

int main(void) {
  palabra = malloc (256);
  listar("test-directorios", 0);

  printf("%s\n",palabra);

  creaPalabras();

  return 0;
}
