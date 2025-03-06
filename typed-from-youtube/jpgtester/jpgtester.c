
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 2)
  {
    printf("Usage: %s [filename]\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *fileName = argv[1];

  FILE *fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    perror("fopen");
    printf("Sorry, could not open file (%s)\n", fileName);
    return EXIT_FAILURE;
  }

  const int MAGIC_NUM_BYTES = 3;
  char magicNumber[MAGIC_NUM_BYTES] = {0};
  char expectedMagicNumber[MAGIC_NUM_BYTES] = {0xFF, 0xD8, 0xFF};

  int numRead = fread(magicNumber, 1, MAGIC_NUM_BYTES, fp);
  if (numRead != MAGIC_NUM_BYTES)
  {
    printf("Couldn't read the first 3 bytes!\n");
    return EXIT_FAILURE;
  }
  
  if (memcmp(magicNumber, expectedMagicNumber,
    MAGIC_NUM_BYTES) == 0)
  {
    printf("Yes!\n");
  } else {
    printf("No!\n");
  }
}
