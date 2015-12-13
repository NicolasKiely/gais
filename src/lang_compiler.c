/**
 * Compiles gais script to byte code
 * Usage: bin/compiler <input script> [output script]
 */

#include <stdlib.h>
#include <stdio.h>


void fcleanup(
    FILE **fin,
    FILE **fout
)
{
  if (*fin){
    fclose(*fin);
    *fin = NULL;
  }

  if (*fout){
    fclose(*fout);
    *fout = NULL;
  }
}

 
int main(
    int argc,
    char *argv[]
)
{
  char *fileName;
  FILE *fin, *fout;

  if (argc!=2 && argc!=3){
    fprintf(stderr, "Usage: %s <input script> [output file]\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Get file handles */
  fileName = argv[1];
  fin = fopen(fileName, "r");
  if (!fin){
    fprintf(stderr, "Error, cannot open file '%s'\n", fileName);
    return EXIT_FAILURE;
  }
  if (argc == 3){
    fileName = argv[2];
    fout = fopen(fileName, "w");
    if (!fout){
      fprintf(stderr, "Error, cannot open file '%s'\n", fileName);
      fcleanup(&fin, &fout);
      return EXIT_FAILURE;
    }
  } else {
    fout = stdout;
  }


  fcleanup(&fin, &fout);
  return EXIT_SUCCESS;
}
