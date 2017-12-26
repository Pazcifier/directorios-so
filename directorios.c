#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

void abrirDirectorios(const char *directorio, int indent) {
  DIR *dir;
  struct dirent *entry;
  char palindroma[10];

  if (!(dir = opendir(directorio)))
    return;

  while ((entry = readdir(dir)) != NULL) {
    printf("En directorio %s\n", entry -> d_name);
  }
}

int main() {
  abrirDirectorios("test-directorios", 0);
  return 0;
}
