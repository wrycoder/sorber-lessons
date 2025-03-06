
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
  int pagesize = sysconf(_SC_PAGE_SIZE);
  if (pagesize == -1)
  {
    perror("sysconf");
  }

  int buffersize = 2 * pagesize;
  char *p1 = malloc(sizeof(char) * 50);

  printf("p1: %p\n", p1);

  char *p2, *p3;

  if (posix_memalign((void **)&p2, pagesize, buffersize)) 
  {
    perror("posix_memalign");
  }

  p3 = mmap(NULL, buffersize, PROT_READ | PROT_WRITE,
    MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (p3 == MAP_FAILED)
  {
    perror("mmap");
  }

  printf("p2: %p\n", p2);
  printf("p3: %p\n", p3);

  printf("writing... \n");
  memset(p2, 5, buffersize);
  memset(p3, 5, buffersize);
  printf("writing done!\n");

  if (mprotect(p2+pagesize, pagesize, PROT_READ) == -1)
  {
    perror("mprotect");
  }

  for (int i=0; i < buffersize; i++)
  {
    printf("%d (%p): writing ... \n", i, p2 + i);
    p2[i] = 3;
  }

  /* *
   *  The loop will hit read-only memory at *(p2 + pagesize),
   *  so we should never reach this point.
   */
  printf("DONE!");
  return EXIT_SUCCESS;
}
