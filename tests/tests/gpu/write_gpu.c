#include <stdio.h>
#include <stdlib.h>

#include <test_utils.h>
#include<GASPI_GPU.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define GPIQueue1 1

#define _4GB 4294967296

#define _128MB 134217728

int main(int argc, char *argv[])
{
  TSUITE_INIT(argc, argv);
  gaspi_gpu_t gpus[8]; 
  gaspi_gpu_num nGPUs;


  ASSERT (gaspi_proc_init(GASPI_BLOCK));
  ASSERT (gaspi_init_GPUs());
  ASSERT (gaspi_number_of_GPUs(&nGPUs));
  ASSERT (gaspi_GPU_ids(gpus));


  const unsigned long N = (1 << 8);
  gaspi_rank_t P, myrank;

  ASSERT (gaspi_proc_num(&P));
  ASSERT (gaspi_proc_rank(&myrank));

  gaspi_printf("P = %d N = %lu\n", P, N);

  gaspi_printf("Seg size: %lu MB\n",  MAX (_128MB, 2 * ((N/P) * N * 2 * sizeof (double)))/1024/1024);

  ASSERT (gaspi_segment_create(0,
			       MAX(_128MB, 2 * ((N/P) * N * 2 * sizeof (double))),
			       GASPI_GROUP_ALL, GASPI_BLOCK, GASPI_MEM_INITIALIZED|GASPI_MEM_GPU));
  

  unsigned char * pGlbMem;

  gaspi_pointer_t _vptr;
  ASSERT (gaspi_segment_ptr(0, &_vptr));

  pGlbMem = ( unsigned char *) _vptr;

  gaspi_number_t qmax ;
  ASSERT (gaspi_queue_size_max(&qmax));

  gaspi_printf("Queue max: %lu\n", qmax);

  ASSERT (gaspi_barrier(GASPI_GROUP_ALL, GASPI_BLOCK));

  int i;
  gaspi_number_t queueSize;
  int rankSend = (myrank + 1) % P;
  gaspi_printf("rank to: %d\n", rankSend);

  for (i = 0; i < 2 * N; i ++)
  {
    ASSERT (gaspi_queue_size(1, &queueSize));
    

    if (queueSize > qmax - 24)
    {
      gaspi_printf (" i = %d qsize %u\n", i , queueSize);
      ASSERT (gaspi_wait(1, GASPI_BLOCK));
    }


    if (gaspi_write(0, //seg
          1024, //local
          rankSend, //rank
          0, //seg rem
          1024, //remote
          32768, //size
          1, //queue
          GASPI_BLOCK) != GASPI_SUCCESS)

    {
      gaspi_queue_size(1, &queueSize);
      gaspi_printf (" failed with i = %d queue %u\n", i, queueSize);
      exit(-1);

    }
  }

  ASSERT (gaspi_wait(1, GASPI_BLOCK));

  ASSERT (gaspi_barrier(GASPI_GROUP_ALL, GASPI_BLOCK));

  ASSERT (gaspi_proc_term(GASPI_BLOCK));


  return EXIT_SUCCESS;
}
