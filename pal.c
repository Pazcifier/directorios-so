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


//IGNORAR
/*void imprimir(char unaPalabra[][256]) {

  int len = sizeof(unaPalabra)/sizeof(char);

  for (int i = 0; i < len; i++) {
    printf("%s", unaPalabra[i]);
  }
}

//Revisa si la palbra es palíndroma

void esPalindroma(char palindroma[][256]) {
  int haciaDerecha = 0;
  int len = sizeof(palindroma)/sizeof(char);
  int haciaIzquierda = len - 1;

  while (haciaIzquierda > haciaDerecha) {
    if (palindroma[haciaDerecha++] != palindroma[haciaIzquierda--]) {
      imprimir(palindroma);
      printf(" no es palíndroma\n");
      return;
    }
  }
  imprimir(palindroma);
  printf(" es palíndroma\n");
}

//creador de palabras
void creaPalabras() {
  char primera[256][256]; //El nodo raíz siempre será el mismo así que se guarda como constante
  strcpy(primera[0], palabra[0]);

  char palabraPaldinroma[256][256]; //Se crea la variable para guardar la palabra hecha

  int cont = 1; //Contador para que empiece a crear palabras a partir del segundo

  while (!strcmp(palabra[cont], "!")) { //Mientras que no encuentre un "!" en el array, seguirá agregando letras al array
    strcpy(palabraPaldinroma[cont], palabra[cont]);
    cont++;
  }

  esPalindroma(palabraPaldinroma);
}
*/
int main(void) {
  palabra = malloc (256);
  listar("test-directorios", 0);

  printf("%s",palabra);

  //creaPalabras();

  return 0;
}
