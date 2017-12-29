#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

struct letra {
  int nroDirectorio;
  int finDirectorio;
  char letraDirectorio[255];
};

void listar(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry; //Entrada del directorio a iterar
    struct letra letras[20];
    int contDirectorio = 0;

    if (!(dir = opendir(name))) // Si no existe el directorio, se sale
        return;

    while ((entry = readdir(dir)) != NULL) { // ciclo para leer el directorio hasta que no haya osubdirectorios o archivos
        if (entry->d_type == DT_DIR) { // Si el tipo del archivo es un directorio entonces entra
            char path[1024]; // especificamos un array de char con el nombre del directorio
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue; // comparamos que el nombre sea igual
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            strncpy(letras[contDirectorio].letraDirectorio, entry->d_name, 254);
            letras[contDirectorio].nroDirectorio = contDirectorio++;
            listar(path, indent + 2);
        }
    }
    closedir(dir);

    letras[contDirectorio].finDirectorio = 1;

    for (int i = 0; i < contDirectorio; i++) {
      printf("%s\n", letras[i].letraDirectorio);
    }
}

int main(void) {

  listar("test-directorios", 0);

  return 0;
}
