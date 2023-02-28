
// Source code for the CUDA kernel 

extern "C"{
    #include "sparse_mult.cuh"
}

#include <stdio.h>


#ifndef DEBUG
// #define DEBUG
#endif


#ifndef DEBUG_GUDA_SOME
// #define DEBUG_GUDA_SOME
#endif





extern __global__ void whoami(void){

    int block_id = 
                    blockIdx.x + 
                    blockIdx.y * gridDim.x + 
                    blockIdx.z * gridDim.x * gridDim.y ;

    int block_offset = 
                    block_id * blockDim.x * blockDim.y * blockDim.z ;
    
    
    int thread_offset = 
                    threadIdx.x + 
                    threadIdx.y * blockDim.x + 
                    threadIdx.z * blockDim.x * blockDim.y ;

    int id = block_offset + thread_offset ; 

    printf("%04d | Block(%d %d %d) = %3d | Thread(%d %d %d) = %3d \n" , 
        id , 
        blockIdx.x  , blockIdx.y  , blockIdx.z  , block_offset , 
        threadIdx.x , threadIdx.y , threadIdx.z , thread_offset ) ;
    
}


extern __global__ void sparse_mult( int N , int nz  ,  int* pointers , int* nz_elements , int* results ){ 

    // Find thread id 
    int id = blockIdx.x * blockDim.x + threadIdx.x ; 

    
    
    // #ifdef DEBUG_GUDA_SOME
    // printf("Hi i am the thread number %4d   am i greater than N %d!!! \n", id ,  id >= N ) ;
    
    // #endif


    if ( id >= N  ){
        #ifdef DEBUG_GUDA_SOME
        printf("Hi i am the thread number %4d and i will not do anything !!! \n", id  ) ;
        #endif
        return ; 
    }


    // Print thread id 
    #ifdef DEBUG
        printf("%4d | Block(%d %d %d) | Thread(%d %d %d) | Start and stop at: pointers[%3d]= %3d  , pointers[%3d]= %3d \n" , 
            id  , 
            blockIdx.x  , blockIdx.y  , blockIdx.z   , 
            threadIdx.x , threadIdx.y , threadIdx.z  , 
            id , pointers[id] , id+1, pointers[id+1]) ;
    #endif


    results[id] = 0 ; 
    for( int other_point_pointer = pointers[id] ; other_point_pointer < pointers[id+1] ; other_point_pointer++){
        // printf("%04d | Block(%d %d %d) | Thread(%d %d %d) | pointers[%2d] = %2d \n" , 
        // id  , 
        // blockIdx.x  , blockIdx.y  , blockIdx.z   , 
        // threadIdx.x , threadIdx.y , threadIdx.z  , 
        // other_point_pointer , nz_elements[other_point_pointer]) ;
        
        int other_point_id = nz_elements[other_point_pointer] ; 

        if( other_point_id < id ){
            continue ; 
        }

        if (  nz_elements[pointers[id]] > nz_elements[pointers[other_point_id+1]-1]   || nz_elements[pointers[id+1]-1] < nz_elements[pointers[other_point_id]]  ){
            // This means there is not overlap between the two lists
            #ifdef DEBUG
            printf("The lists %3d and %3d  do not have any overlap\n" , id , other_point_id );
            #endif
            continue ; 
        }
        // We need to find how many common points there are between "id" and "other_point_id"


        // 'pointers' to element
        int mine_start = pointers[id] ;
        int mine_end = pointers[id+1] ;
        int other_start = pointers[other_point_id] ;
        int other_end = pointers[other_point_id+1] ;

        
        #ifdef DEBUG
        int count = 0 ; 
        #endif

        while( mine_start < mine_end && other_start < other_end ){

            
            #ifdef DEBUG
            // printf("Common check between lists: %3d and %3d , now checking elements %3d with %3d -------\n" , id , other_point_id ,  nz_elements[mine_start] , nz_elements[other_start]  );
            #endif

            if ( nz_elements[mine_start] < nz_elements[other_start] ){
                mine_start++;
            }
            else if ( nz_elements[mine_start] > nz_elements[other_start]  ){
                other_start++;
            }
            else{
                
                results[id]++;
                other_start++;
                mine_start++;

                #ifdef DEBUG
                count++; 
                #endif
            }

        }

        #ifdef DEBUG 
        printf("Common elements found between %3d and %3d are %3d many \n" , id , other_point_id , count);
        #endif


    }


    #ifdef DEBUG
    printf("%04d | Block(%d %d %d) | Thread(%d %d %d) | End | results[%3d] = %3d  \n" , 
        id  , 
        blockIdx.x  , blockIdx.y  , blockIdx.z   , 
        threadIdx.x , threadIdx.y , threadIdx.z  , 
        id , results[id]) ;
    #endif
    
}


extern __global__ void find_d2_hat( int N , int nz  ,  int* pointers , int* nz_elements ,int* p1 ,  int* results ){ 

    // Find thread id 
    int id = blockIdx.x * blockDim.x + threadIdx.x ; 


    if ( id >= N  ){
        #ifdef DEBUG_GUDA_SOME
            printf("Hi i am the thread number %4d and i will not do anything !!! \n", id  ) ;
        #endif
        return ; 
    }


    // Print thread id 
    #ifdef DEBUG
        printf("%4d | Block(%d %d %d) | Thread(%d %d %d) | Start and stop at: pointers[%3d]= %3d  , pointers[%3d]= %3d \n" , 
            id  , 
            blockIdx.x  , blockIdx.y  , blockIdx.z   , 
            threadIdx.x , threadIdx.y , threadIdx.z  , 
            id , pointers[id] , id+1, pointers[id+1]) ;
    #endif

    // Perform  A*p1-p1 
    results[id] = - p1[id] ; 
    for( int other_point_pointer = pointers[id] ; other_point_pointer < pointers[id+1] ; other_point_pointer++){
        // printf("%04d | Block(%d %d %d) | Thread(%d %d %d) | pointers[%2d] = %2d \n" , 
        // id  , 
        // blockIdx.x  , blockIdx.y  , blockIdx.z   , 
        // threadIdx.x , threadIdx.y , threadIdx.z  , 
        // other_point_pointer , nz_elements[other_point_pointer]) ;
        
        int other_point_id = nz_elements[other_point_pointer] ; 

        results[id] += p1[other_point_id] ; 

    }


    #ifdef DEBUG
        printf("%04d | Block(%d %d %d) | Thread(%d %d %d) | End | results[%3d] = %3d  \n" , 
            id  , 
            blockIdx.x  , blockIdx.y  , blockIdx.z   , 
            threadIdx.x , threadIdx.y , threadIdx.z  , 
            id , results[id]) ;
    #endif
    
}


__global__ void find_d3_hat( int N , int* p1  , int* d3_hat ){ 

    // Find thread id 
    int id = blockIdx.x * blockDim.x + threadIdx.x ; 

    if ( id >= N  ){
        #ifdef DEBUG_GUDA_SOME
        printf("Hi i am the thread number %4d and i will not do anything inside find_d3_hat  !!! \n", id  ) ;
        #endif
        return ; 
    }

    d3_hat[id] =  p1[id] * (p1[id]-1) / 2  ; 

    #ifdef DEBUG
    printf("%04d | Block(%d %d %d) | Thread(%d %d %d) | End | d3_hat[%3d] = %3d  \n" , 
        id  , 
        blockIdx.x  , blockIdx.y  , blockIdx.z   , 
        threadIdx.x , threadIdx.y , threadIdx.z  , 
        id , d3_hat[id]) ;
    #endif
    
}



// static const int wholeArraySize = 100000000;
static const int blockSize = 1024;
static const int gridSize = 24; //this number is hardware-dependent; usually #SM*2 is a good number.

__global__ void sumCommMultiBlock(const int *gArr, int arraySize, int *gOut) {
    int thIdx = threadIdx.x;
    int gthIdx = thIdx + blockIdx.x*blockSize;
    const int gridSize = blockSize*gridDim.x;
    int sum = 0;
    for (int i = gthIdx; i < arraySize; i += gridSize)
        sum += gArr[i];
    __shared__ int shArr[blockSize];
    shArr[thIdx] = sum;
    __syncthreads();
    for (int size = blockSize/2; size>0; size/=2) { //uniform
        if (thIdx<size)
            shArr[thIdx] += shArr[thIdx+size];
        __syncthreads();
    }
    if (thIdx == 0)
        gOut[blockIdx.x] = shArr[0];
}



__host__ int sumArray(int* arr , int wholeArraySize ) {
    int* dev_arr;
    cudaMalloc((void**)&dev_arr, wholeArraySize * sizeof(int));
    cudaMemcpy(dev_arr, arr, wholeArraySize * sizeof(int), cudaMemcpyHostToDevice);

    int out;
    int* dev_out;
    cudaMalloc((void**)&dev_out, sizeof(int)*gridSize);
    
    sumCommMultiBlock<<<gridSize, blockSize>>>(dev_arr, wholeArraySize, dev_out);
    //dev_out now holds the partial result
    sumCommMultiBlock<<<1, blockSize>>>(dev_out, gridSize, dev_out);
    //dev_out[0] now holds the final result
    cudaDeviceSynchronize();
    
    cudaMemcpy(&out, dev_out, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(dev_arr);
    cudaFree(dev_out);
    return out;
}


__host__ int sumArray_already_in_GPU(int* dev_arr , int wholeArraySize ) {
    // int* dev_arr;
    // cudaMalloc((void**)&dev_arr, wholeArraySize * sizeof(int));
    // cudaMemcpy(dev_arr, arr, wholeArraySize * sizeof(int), cudaMemcpyHostToDevice);

    int out;
    int* dev_out;
    cudaMalloc((void**)&dev_out, sizeof(int)*gridSize);
    
    sumCommMultiBlock<<<gridSize, blockSize>>>(dev_arr, wholeArraySize, dev_out);
    //dev_out now holds the partial result
    sumCommMultiBlock<<<1, blockSize>>>(dev_out, gridSize, dev_out);
    //dev_out[0] now holds the final result
    cudaDeviceSynchronize();
    
    cudaMemcpy(&out, dev_out, sizeof(int), cudaMemcpyDeviceToHost);
    // cudaFree(dev_arr);
    cudaFree(dev_out);
    return out;
}
