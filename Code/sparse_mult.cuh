#ifndef sparse_mult_cuh
#define sparse_mult_cuh

// Header file for the kernel CUDA code 


// This is to make it compile 
#ifdef __cplusplus
extern "C"{
#endif


// This finds C3/2 (kinda)
__global__ void sparse_mult(int N , int nz ,  int* A , int* B , int* C) ; 

__global__ void whoami(void);

__global__ void find_d3_hat( int N , int* p1  , int* d3_hat );

extern __global__ void find_d2_hat( int N , int nz  ,  int* pointers , int* nz_elements ,int* p1 ,  int* results );

// Those two fucntion are used to sum the elements of an array in parallel in the GPU
// from the site https://sodocumentation.net/cuda/topic/6566/parallel-reduction--e-g--how-to-sum-an-array-
__global__ void sumCommMultiBlock(const int *gArr, int arraySize, int *gOut);

// The sums work for int 
__host__ int sumArray(int* arr , int wholeArraySize ) ;

__host__ int sumArray_already_in_GPU(int* dev_arr , int wholeArraySize ); // Variation



// This is to make it compile 
#ifdef __cplusplus
}
#endif





#endif