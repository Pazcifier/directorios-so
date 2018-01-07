#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

char *palabra; //Variable para guardar las letras
int contador = 0;
int contP=0;    //Variable para guardar la posicion de las letras

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
void copyAndPrint (char *palindroma,int i,int a,int len,int inside){
  int k=0;
  char *p = malloc(sizeof(palabra)/sizeof(char));
  if (inside == 0){
    for (int j =i; j<strlen(palindroma);j++){
      p[k]= palindroma[j];
      k++;
    }
  } else {
    for (int j =i; j<=len;j++){
      p[k]= palindroma[j];
      k++;
    }
  }
  if (a == 1){
    printf("%s es palindroma\n", p);
  }else {
     voltear(p);
    printf("%s es palindroma\n", p); //Volteo el resutado, porque aqui agarramos el string volteado por usar a palindromaReverso
  }
}
//Revisa si la palbra es palíndroma
void esPalindroma(char* palindroma) {
  int len = strlen(palindroma);
  int chequeo=0;
  char *palindromaReverso = malloc (sizeof(palindroma)/sizeof(char));
  strcpy(palindromaReverso, palindroma);
  voltear(palindromaReverso);
 if (strcmp(palindroma, palindromaReverso) == 0) {
   chequeo = 1;
 }
  for (int i=0; i <len;i++){ // Recorro todos los caracteres
    if ((len-i) >= 3){ //Pregunto para asegurarme que sea mayor o igual a 3
      if (palindroma[i] == palindroma[len-1]){ //Comparo la palalabra con el ultimo, hago un recorrido del primero hasta 3 posiciones antes del ultimo
        copyAndPrint(palindroma,i,1,len,0);
        contP++; //Si se encuentra, llamo a una funcion que me mete en una variable el pedazo de string que deseo imprimir deps de saber que es palindrome
      }
      if (chequeo == 0){
        if (palindromaReverso[i] == palindromaReverso[len-1]){
          copyAndPrint(palindromaReverso,i,0,len,0);
          contP++;//Hago lo mismo con el reverso para segurarme de encontrar los que estan del "ultimo" al primero
        }
      } // El 0 o 1 que aparece ahi es para saber cuand hay q voltear el pedazo de string para imprimirlo
    }
  }
  int j=len-2;
  while(j>=2){
    for (int i=1;i<=j;i++){
      if ((j-i)>=2){
        if (palindroma[i] == palindroma[j]){ //Comparo la palalabra con el ultimo, hago un recorrido del primero hasta 3 posiciones antes del ultimo
          copyAndPrint(palindroma,i,1,j,1); //Si se encuentra, llamo a una funcion que me mete en una variable el pedazo de string que deseo imprimir deps de saber que es palindrome
          contP++;
        }
      }
    }
    j--;
  }
  free(palindromaReverso);
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
    if (strlen(palabraPalindroma) >= 3) {
      esPalindroma(palabraPalindroma);
    }
    len--;
  }
  free(palabraPalindroma);
}

int main(void) {
  int contD=0;
  palabra = malloc (256);
  listar("test-directorios", 0);
  for (int i=0;i<strlen(palabra);i++){
    if (palabra[i] != '!') {
      contD++;
    }
  }
  if (contD<= 20){
    creaPalabras();
  } else{
    printf("La cantidad de directorios son maximo 20");
  }
  if (contP== 0){
    printf("No existen\n");
  }
  free(palabra);
  return 0;
}
