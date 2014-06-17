
#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <assert.h>
#include <GASPI.h>

static gaspi_config_t tsuite_default_config = 
  {
    1,				//logout
    12121,
    0,				//netinfo
    0,				//netdev
    2048,				//mtu
    1,				//port check
    0,				//user selected network
    GASPI_IB,			//network typ
    1024,				//queue depth
    8,				//queue count
    GASPI_MAX_GROUPS,		//group_max;
    GASPI_MAX_MSEGS,		//segment_max;
    GASPI_MAX_TSIZE_C,		//transfer_size_max;
    GASPI_MAX_NOTIFICATION,	//notification_num;
    1024,				//passive_queue_size_max;
    GASPI_MAX_TSIZE_P,		//passive_transfer_size_max;
    278592,			//allreduce_buf_size;
    255,				//allreduce_elem_max;
    1				//build_infrastructure;  
  };

#define _4GB 4294967296
#define _2GB 2147483648

  

void tsuite_init(int argc, char *argv[]);
void success_or_exit ( const char* file, const int line, const int ec);
void must_fail ( const char* file, const int line, const int ec);
void must_timeout ( const char* file, const int line, const int ec);
void tsuite_init(int argc, char *argv[]);

#define TSUITE_INIT(argc, argv) tsuite_init(argc, argv);   
#define ASSERT(ec) success_or_exit (__FILE__, __LINE__, ec);
#define EXPECT_FAIL(ec) must_fail(__FILE__, __LINE__, ec);
#define EXPECT_TIMEOUT(ec) must_timeout(__FILE__, __LINE__, ec);  

gaspi_size_t get_system_mem();
void exit_safely();
  
#endif //_TEST_UTILS_H_
