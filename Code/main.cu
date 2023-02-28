
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>


#include "sparse_mult.cuh"


extern "C" {
    #include "load_stuff.h"
    #include "csx.h" // Credits to JohnStef :) 
}

#ifndef DEBUG_PRINT_ONLY_TIME
// #define DEBUG_PRINT_ONLY_TIME
#endif


#ifndef DEBUG_TIME_CPP
// #define DEBUG_TIME_CPP
#endif


// nvcc    -O3  main.cu    load_stuff.c  sparse_mult.cu  mmio.c csx.c -o CUDA_nick.exe

int main ( int argc, char* argv[] ){


    // Choose input 
    
    char file_relative_path[100] = "../Data" ; 

    
    if (argc > 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        // return 1;
    }

    char* file_to_load;

    int option_chosen = - 1 ; 

    if ( argc == 2  ){

        option_chosen = atoi(argv[1]);
        printf("The option_chosen is: %d\n", option_chosen);

        file_to_load = decide_file_to_load( option_chosen , file_relative_path, -1 ); 
    }
    else{
        file_to_load = select_file_to_load(file_relative_path ); 
    }
    

    #ifndef DEBUG_PRINT_ONLY_TIME
        printf("Start loading file: %s \n\n" , file_to_load ) ;
    #endif


    

    // Load data 
    
    int* p1 ;
    csx my_sparse =  csc_from_file(file_to_load, &p1);
    

    int* compressed_columes     = my_sparse->com ; 
    int* full_rows              = my_sparse->unc ;
    int nz          = my_sparse->e ;
    int matrix_dim  = my_sparse->v ; 

    
    // csx_print(my_sparse);

    #ifndef DEBUG_PRINT_ONLY_TIME
        printf("Loading Completed!\n"  ) ;
        printf("Matrix N = %d    |  nz = %d \n" , matrix_dim , nz ) ; 
    #endif

    
    
    
    // Send data to GPU 

        // Mesure time
        
        cudaEvent_t start, end;
        cudaEventCreate(&start);
        cudaEventCreate(&end);
        cudaEventRecord(start);
        

        #ifdef DEBUG_TIME_CPP
            auto cpp_start = std::chrono::high_resolution_clock::now();
        #endif


    int* d_nz;
    int* d_pointers;
    int* d_result_vector ; 
    int* d_p1 ;    
    
    cudaMalloc( (void**)&d_nz            ,  nz              * sizeof(int) ) ; 
    cudaMalloc( (void**)&d_pointers      , (matrix_dim+1)   * sizeof(int) ) ; 
    cudaMalloc( (void**)&d_result_vector , (matrix_dim)     * sizeof(int) ) ; 


    cudaMalloc( (void**)&d_p1            ,  matrix_dim * sizeof(int) ) ;     
    cudaMemcpy( (void*)d_p1         , p1                    ,  matrix_dim       * sizeof(int)   , cudaMemcpyHostToDevice );
    
    
    cudaMemcpy( (void*)d_nz         , full_rows             ,       nz          * sizeof(int)   , cudaMemcpyHostToDevice );
    cudaMemcpy( (void*)d_pointers   , compressed_columes    , (matrix_dim+1)    * sizeof(int)   , cudaMemcpyHostToDevice );

    
    // Make the calcualation in GPU for C3


    int threads_per_block = 1024 ; // This can not be greater than 1024 !!!
    int number_of_blocks = (matrix_dim/threads_per_block+1) ;

    #ifndef DEBUG_PRINT_ONLY_TIME
    //printf("Created %d blocks with %d threads each, total of %d threads\n" , number_of_blocks , threads_per_block , number_of_blocks * threads_per_block );
    #endif  

    sparse_mult<<<number_of_blocks,threads_per_block>>>(matrix_dim , nz ,d_pointers, d_nz  , d_result_vector ) ; 






    // Find sigma4 
    
    // Take d_result_vector  (it had C3) 
    int sigma4_from_GPU = sumArray_already_in_GPU(d_result_vector , matrix_dim ) ;
    // release d_result_vector  = C3



    // Take d_result_vector  (it had C3) 
    find_d3_hat<<<number_of_blocks,threads_per_block>>>( matrix_dim , d_p1  , d_result_vector );

    int sigma3_hat_from_GPU = sumArray_already_in_GPU(d_result_vector , matrix_dim ) ;  // Sum d3_hat to find sigma3 
    // release d_result_vector = d3_hat


    // Take d_result_vector  (it had d3_hat) 
    find_d2_hat<<<number_of_blocks,threads_per_block>>>( matrix_dim,  nz  ,  d_pointers, d_nz  , d_p1 ,  d_result_vector );
    
    int sigma2_hat_from_GPU = sumArray_already_in_GPU(d_result_vector , matrix_dim ) ;  // Sum d2_hat to find sigma2
    // release d_result_vector = d2_hat


        
    cudaDeviceSynchronize() ; // Probably not needed for the time

        // Time taken 

        cudaEventRecord(end);
        cudaEventSynchronize(start);
        cudaEventSynchronize(end);

        float time_in_ms = 0;
        cudaEventElapsedTime(&time_in_ms, start, end);

    
        #ifndef DEBUG_PRINT_ONLY_TIME
            // Normal print
            printf("Time %f ms  \n" , time_in_ms );
        #endif
        
        #ifdef DEBUG_PRINT_ONLY_TIME
            printf("Time %f ms    <---------- CUDA  for file: %s\n" , time_in_ms , file_to_load);
        #endif


        #ifdef DEBUG_TIME_CPP
            auto cpp_end = std::chrono::high_resolution_clock::now();
            double cpp_time = std::chrono::duration_cast<std::chrono::milliseconds>(cpp_end-cpp_start).count();
            printf("Time %f ms    <---------- CPP   for file: %s \n" , cpp_time , file_to_load);
        #endif


        




    // Print resutls σ1 σ2 σ3 σ4

    int sigma[5] ;
    sigma[0] =  matrix_dim ; 
    sigma[1] =  nz ; 
    sigma[2] =  sigma2_hat_from_GPU - 2 * sigma4_from_GPU  ; 
    sigma[3] =  sigma3_hat_from_GPU -     sigma4_from_GPU  ; 
    sigma[4] =  sigma4_from_GPU ; 

    #ifdef DEBUG_PRINT_ONLY_TIME
        check_results( sigma , option_chosen ) ; 
    #endif

    #ifndef DEBUG_PRINT_ONLY_TIME
        printf("\nResults\n" ) ;
        printf("sigma0: %d \n" , sigma[0] ) ; 
        printf("sigma1: %d \n" , sigma[1] ) ; 
        printf("sigma2: %d \n" , sigma[2] ) ; 
        printf("sigma3: %d \n" , sigma[3] ) ; 
        printf("sigma4: %d \n" , sigma[4] ) ; 
    #endif  
    

    // Clear memory both in CPU and GPU 
    cudaFree((void*)d_nz);
    cudaFree((void*)d_pointers);
    cudaFree((void*)d_result_vector);
    cudaFree((void*)d_p1);
    
    free(file_to_load);
    free(p1); 
    
    csx_free( my_sparse ) ; 


    return 0 ; 

}