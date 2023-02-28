
# Makefile
# By Liouliakis Nikolaos 


CC_CUDA    	= nvcc 
CC 			= gcc
CFLAGS 		= -O3


MAIN_CUDA = main.cu
FILES_TO_COMPILE = load_stuff.c  sparse_mult.cu  mmio.c csx.c
EXE_NAME_CUDA 	= CUDA_nick.exe 


program: 
	$(CC_CUDA) 	$(CFLAGS)  $(MAIN_CUDA) 	$(FILES_TO_COMPILE) -o $(EXE_NAME_CUDA) 	


.PHONY: run clean test  


run:
	./$(EXE_NAME_CUDA) 
#


clean:
	 rm -f $(EXE_NAME_CUDA)
#	del $(EXE_NAME_CUDA)

test:	
	echo hello world


