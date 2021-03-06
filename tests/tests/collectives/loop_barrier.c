#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <test_utils.h>

#define ITERATIONS 1000

int main(int argc, char *argv[])
{
  gaspi_rank_t nprocs, myrank;

  TSUITE_INIT(argc, argv);

  ASSERT (gaspi_proc_init(GASPI_BLOCK));

  ASSERT(gaspi_proc_num(&nprocs));
  ASSERT(gaspi_proc_rank(&myrank));

  //loop barrier
  int i;
  for (i = 0; i < ITERATIONS; i++)
    ASSERT (gaspi_barrier(GASPI_GROUP_ALL, GASPI_BLOCK));

  //sync                                                                                                  
  ASSERT (gaspi_proc_term(GASPI_BLOCK));

  return EXIT_SUCCESS;
}
