#include <stdlib.h>
#include <stdio.h>

#include <test_utils.h>

#define _4GB 4294967296
#define _2GB 2147483648
#define _500MB 524288000
#define _8MB 8388608

int main(int argc, char *argv[])
{
  gaspi_rank_t numranks, myrank;
  gaspi_rank_t rankSend;
  gaspi_size_t segSize;
  const  gaspi_offset_t localOff_r= 0;
  const gaspi_offset_t remOff_r = 0;
  const  gaspi_offset_t localOff_w = _2GB / 2 ;
  const gaspi_offset_t remOff_w = _2GB / 2;
  gaspi_number_t queueSize, qmax;
  const gaspi_size_t commSize = _500MB;
  int i;

  TSUITE_INIT(argc, argv);

  ASSERT (gaspi_proc_init(GASPI_BLOCK));

  ASSERT (gaspi_proc_num(&numranks));
  ASSERT (gaspi_proc_rank(&myrank));

  ASSERT (gaspi_segment_create(0, _2GB, GASPI_GROUP_ALL, GASPI_BLOCK, GASPI_MEM_INITIALIZED));

  ASSERT( gaspi_segment_size(0, myrank, &segSize));

  ASSERT (gaspi_barrier(GASPI_GROUP_ALL, GASPI_BLOCK));

  ASSERT (gaspi_queue_size_max(&qmax));

  for(i = 0; i < 100; i++ )
    {
      for(rankSend = 0; rankSend < numranks; rankSend++)
	{
	  if(rankSend == myrank)
	    continue;
	  
	  gaspi_printf("partner rank: %d - %lu bytes (%d)\n", rankSend, commSize, i);

	  ASSERT (gaspi_queue_size(1, &queueSize));
	  if (queueSize > qmax - 24)
	    ASSERT (gaspi_wait(1, GASPI_BLOCK));
	  
	  ASSERT (gaspi_read(0, localOff_r, rankSend, 0,  remOff_r,  commSize, 1, GASPI_BLOCK));
	}
    }
  for(i = 0; i < 100; i++ )
    {
      for(rankSend = 0; rankSend < numranks; rankSend++)
	{
	  if(rankSend == myrank)
	    continue;

	  ASSERT (gaspi_write(0, localOff_r, rankSend, 0,  remOff_r,  commSize, 1, GASPI_BLOCK));
	}
    }

  ASSERT (gaspi_wait(1, GASPI_BLOCK));
  
  ASSERT (gaspi_barrier(GASPI_GROUP_ALL, GASPI_BLOCK));
  
  ASSERT (gaspi_proc_term(GASPI_BLOCK));

  return EXIT_SUCCESS;
}
