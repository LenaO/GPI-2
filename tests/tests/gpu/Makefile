BIN =  hello_gpus.bin seg_alloc_gpu.bin seg_alloc_gpu_all.bin  seg_gpu_register.bin write_gpu.bin write_gpu_write.bin read_gpu.bin read_write_gpu.bin\
        read_write_gpu_gpu.bin notify_gpu.bin write_gpu_all.bin

CFLAGS+=-I../

build: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

%.bin: %.o ../test_utils.o
	$(CC) $(CFLAGS) $(LIB_PATH) -o $@ $^ $(LIBS)

clean:
	rm -rf *~ \#_* *.o *.bin

.PHONY: clean
