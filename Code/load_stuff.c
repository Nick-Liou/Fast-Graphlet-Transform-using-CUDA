

#include <stdbool.h>
#include <stdlib.h>

#include <string.h>


#include "load_stuff.h"

#include "mmio.h"



#ifndef DEBUG_LOADING
#define DEBUG_LOADING
#endif

void int_swap(int* a , int* b){
    
    int temp = *a ; 
    *a = *b ; 
    *b = temp ;

}

void scanf_check( int number_of_output_arguments_expected , int actual_output_arguments ) {

    if( number_of_output_arguments_expected != actual_output_arguments){
        printf("Error scanning values, Expected %d but read %d \n" ,number_of_output_arguments_expected, actual_output_arguments );
        exit(1);
    }
}


void check_results( int* sigma , int option_chosen ){
    if( option_chosen == -1 ){
        printf("Options was chosen frome the menu check can not work\n");
        return;
    }

    int error = 0 ; 
    if ( option_chosen == 0  ){
        int id = -1 ; 
        
        if ( sigma[0] != 448695 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 448695\n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[1] != 6629222 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 6629222\n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[2] != 57146832 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 57146832\n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[3] != 28573416 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 28573416\n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[4] != 18735552 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 18735552\n", ++id , sigma[id] );
            error++;
        }

        if ( error != 0 ){
            printf("There was an error in auto \n"); 
        }

    }

    if ( option_chosen == 1  ){
        int id = -1 ; 
        
        if ( sigma[0] != 7733822 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 7733822     \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[1] != 16313034 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 16313034    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[2] != 20314242 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 20314242    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[3] != 10157121 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 10157121    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[4] != 32724 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 32724       \n", ++id , sigma[id] );
            error++;
        }

        if ( error != 0 ){
            printf("There was an error in great-britain_osm \n"); 
        }

    }

    if ( option_chosen == 2  ){
        int id = -1 ; 
        
        if ( sigma[0] != 4194304 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 4194304     \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[1] != 25165738 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 25165738    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[2] != 82698832 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 82698832    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[3] != 41349416 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 41349416    \n", ++id , sigma[id] );
            error++;
        }
        if ( sigma[4] != 25310016 ){
            printf("The value of sigma[%d] was wrong is was : %d  when is sould have been : 25310016    \n", ++id , sigma[id] );
            error++;
        }

        if ( error != 0 ){
            printf("There was an error in delaunay_n22 \n"); 
        }

    }



    if ( error != 0 ) {
        exit(1) ; 
    }
    else{
        // printf("all fine \n");
    }


}

int print_options ( const char* default_path ) {

    int i = 0  ; 
    printf( "Default path is \"%s\"  \n\n" , default_path ) ; 
    printf( "%d)auto.mtx               ( 43  MB ) \n" , i++) ; 
    printf( "%d)great-britain_osm.mtx  ( 125 MB ) \n" , i++) ; 
    printf( "%d)delaunay_n22.mtx       ( 190 MB ) \n" , i++) ; 
    printf( "%d)s6.mtx                 ( 1   KB ) \n" , i++) ; 
    printf( "%d)s12.mtx                ( 1   KB ) \n" , i++) ; 
    printf( "%d)mycielskian4.mtx       ( 3   KB ) \n" , i++) ; 
    printf( "%d)karate.mtx             ( 2   KB ) \n" , i++) ; 
    // printf( "%d)com-Youtube.mtx        ( 37  MB ) \n" , i++) ;  // 
    printf( "%d)Relative path to file             \n" , i++) ; 
    printf( "%d)Exit \n" , i++) ; 
    
    return i ; 
}


char* decide_file_to_load( int option_chosen , char* default_path , int max_options ) {

    int i = 0 ; 

    if ( option_chosen == i++ ){
        char file_name[50] = "auto.mtx" ;             
        return generate_filename(default_path , file_name);        
    }
    if ( option_chosen == i++){
        char file_name[50] = "great-britain_osm.mtx" ;
        return generate_filename(default_path , file_name);
    }
    if ( option_chosen == i++){
        char file_name[50] = "delaunay_n22.mtx" ;     
        return generate_filename(default_path , file_name);
    }
    if ( option_chosen == i++){
        char file_name[50] = "s6.mtx" ;               
        return generate_filename(default_path , file_name);
    }
    if ( option_chosen == i++){
        char file_name[50] = "s12.mtx" ;              
        return generate_filename(default_path , file_name);
    }
    if ( option_chosen == i++){
        char file_name[50] = "mycielskian4.mtx" ;     
        return generate_filename(default_path , file_name);
    }
    if ( option_chosen == i++){
        char file_name[50] = "karate.mtx" ;           
        return generate_filename(default_path , file_name);
    }
    // if ( option_chosen == i++){
    //     char file_name[50] = "com-Youtube.mtx" ;           
    //     return generate_filename(default_path , file_name);
    // }
    if ( option_chosen == i++){    
        // Read relative path from the user
        char* file_relative_path = (char*)malloc(1024*sizeof(char));

        printf("Enter the relative path to the file: ");
        scanf_check( 1, scanf("%1023s", file_relative_path));
        return file_relative_path;
    }
    if ( option_chosen == i++){    
        // Exit
        printf("You chose to exit\n");
        exit(0);        
    }

    return select_file_to_load ( default_path ) ; 

}


char* generate_filename(char* relative_path, char* file_name){
    // Allocate memory for the new filename
    char* new_filename = (char*) malloc(strlen(relative_path) + strlen(file_name) + 1 ); 
    
    if ( new_filename == NULL ) { 
        printf("Malloc Error returned NULL in generate_filename function.\n"); 
        exit(1) ; 
    }

    // Concatenate the path with the file name
    sprintf(new_filename, "%s/%s", relative_path , file_name);
    
    return new_filename;
}

char* select_file_to_load(  char* default_path ){


    int max_options = print_options( default_path ) ; 
            
    int option_chosen = -1 ;

    while ( option_chosen < 0 || option_chosen >= max_options ){
        if ( option_chosen != -1 ){
            printf("Input a valid option!");
        }
        printf("\n");
        printf("Select option: ");  
        scanf_check(1,  scanf("%d", &option_chosen));
    }

    return decide_file_to_load( option_chosen , default_path , max_options ) ; 

    // // Exit 
    // if ( option_chosen == max_options - 1 ){
    //     printf("You chose to exit\n");
    //     exit(0); 
    // }

    // switch (expression){
    //     case constant1:
    //     // statements
    //     break;

    //     case constant2:
    //     // statements
    //     break;
        


    //     default:
    //     // default statements
    // }

    


    // char* file_to_load = generate_filename(file_relative_path, file_name) ; 

    // return file_to_load ; 




    // if( number == -2 ){
        
    //     char* file_relative_path = (char*)malloc(1024*sizeof(char));

    //     printf("Enter the relative path to the file: ");
    //     fflush(stdout);
    //     scanf_check( 1, scanf("%1023s", file_relative_path));
      
        // if (print_dataset_parameters_and_free(file_relative_path, false)){
        //     // This means the file was opened and the parameters of the file were printed 
        //     return file_relative_path ;
        // }
        // else{
        //     printf("The file could not open, perhaps it does not exist, try again.\n");
        //     printf("File that tried to open was: %s\n",file_relative_path);
        //     free(file_relative_path);
        //     return select_file_to_load();
        // }



    // // }
    // // else if ( number != -1 ){
    // //     // Print the modified string
    // //     char* file_name =  generate_filename(base_name , number) ;
    // //     //printf("%s\n", file_name);
    // //     if (print_dataset_parameters_and_free(file_name , false)){
    // //         return file_name; 
    // //     }
    // //     else{
    // //         printf("The file could not open, perhaps it does not exist, try again.\n");
    // //         printf("File that tried to open was: %s\n",file_name);
    // //         return select_file_to_load();
    // //     }
        
    // // }
    

}


// char* select_file_to_load(){


    
    
    
//     // "../knn_datasets_zero_based/knn_dataset0.txt" 
//     char base_name[100] = "../knn_datasets_zero_based/knn_dataset" ;
//     int number = 0;

//     printf("\n");
//     printf("Select dataset ID  / give '-1' to show availiable datasets / give '-2' to specify relative path to a file: ");      
//     fflush(stdout);
//     scanf_check(1,  scanf("%d", &number));

//     if( number == -2 ){
        
//         char* file_relative_path = (char*)malloc(1024*sizeof(char));

//         printf("Enter the relative path to the file: ");
//         fflush(stdout);
//         scanf_check( 1, scanf("%1023s", file_relative_path));
      
//         if (print_dataset_parameters_and_free(file_relative_path, false)){
//             // This means the file was opened and the parameters of the file were printed 
//             return file_relative_path ;
//         }
//         else{
//             printf("The file could not open, perhaps it does not exist, try again.\n");
//             printf("File that tried to open was: %s\n",file_relative_path);
//             free(file_relative_path);
//             return select_file_to_load();
//         }



//     }
//     else if ( number != -1 ){
//         // Print the modified string
//         char* file_name =  generate_filename(base_name , number) ;
//         //printf("%s\n", file_name);
//         if (print_dataset_parameters_and_free(file_name , false)){
//             return file_name; 
//         }
//         else{
//             printf("The file could not open, perhaps it does not exist, try again.\n");
//             printf("File that tried to open was: %s\n",file_name);
//             return select_file_to_load();
//         }
        
//     }
//     else{
//         // Search and print the files with a specified format 
//         number = 0 ; 
//         printf("\n");
//         while( print_dataset_parameters_and_free (generate_filename(base_name , number++) , true  ) ); //{ }
//         // This while has an empty body!
//         return select_file_to_load();
//     }

// }






// Load a sparse matrix with 2 columns in the file (if there are 3 it breaks :))
// Since the matrix is symmetric CSR and CSC are the same thing
// We assume that the second column is sorted in the input file 
void load_file(const char *file_name, int *total_nodes, int *total_number_of_edges, int **full_rows, int **compressed_columns) {




    printf("Inside load file \n");

    
    int ret_code;
    MM_typecode matcode;
    FILE *f;

    int M, N, nz;
    

    if ((f = fopen(file_name, "r")) == NULL) {
        printf("Could not open file it returned a NULL pointer.\n");
        exit(1);
    }

    if (mm_read_banner(f, &matcode) != 0) {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    } 

    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && mm_is_sparse(matcode)) {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }

    /* find out size of sparse matrix  */

    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) != 0){

        printf("There was an error reading the file .\n");
        exit(1);
    }


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Start of malloc ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    *total_number_of_edges = nz;
    *total_nodes = M ;

    /* reseve memory for matrices */

    printf("Before malloc \n");


    int* normal_rows     = (int *) malloc( 2 * nz * sizeof(int));
    int* normal_columns  = (int *) malloc( 2 * nz * sizeof(int));
    


    bool succefully_malloc = true;

    if ( normal_rows == NULL ){
        succefully_malloc = false;     
        printf("\nFailed to malloc rows");
    }
    if ( normal_columns == NULL ){
        succefully_malloc = false;     
        printf("\nFailed to malloc columns");    
    }

    if ( !succefully_malloc ) {      
        printf("\nSo the program is exiting \n");  
        exit(1) ;
    }
    

    
    
    #ifdef DEBUG_LOADING
    printf("After malloc N = %d M = %d nz = %d \n" ,N ,M , nz );  
    #endif

    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */


    //printf("Start reading file ... \n");
    int diagonal_elements = 0 ; 
    for (int i = 0; i < nz; i++) {
                
                
        // printf("Before fscanf  \n");  
        fscanf(f, "%d %d \n", &normal_columns[2*i], &normal_rows[2*i] );

        if (  normal_columns[2*i] == normal_rows[2*i] ){
            diagonal_elements++ ; 
        }

        // Sub 1 from each of them to make them zero based
        normal_columns[2*i+1]   = --normal_rows[2*i] ; 
        normal_rows[2*i+1]      = --normal_columns[2*i] ;
        
        // printf("i = %2d | a =  %2d  | b = %2d \n" , 2*i , normal_columns[2*i] , normal_rows[2*i]); 
        // printf("i = %2d | a =  %2d  | b = %2d \n" , 2*i+1 , normal_columns[2*i+1] , normal_rows[2*i+1]); 

    }   
    
    if ( diagonal_elements != 0 ){
        printf("After load diagonal_elements = %d \n" ,diagonal_elements ); 
    }

    
    #ifdef DEBUG_LOADING
    printf("After reading from file \n") ;
    #endif

      
    *compressed_columns = (int*) malloc( (M + 1) * sizeof(int) ) ; 
    *full_rows          = (int*) malloc(  2 * nz * sizeof(int) ) ; 
    int *nz_per_row     = (int*) calloc( M+1 , sizeof(int) );

    #ifdef DEBUG_LOADING
    printf("Value at ptr = %p \n", nz_per_row);
    #endif

    if ( compressed_columns == NULL ){
        succefully_malloc = false;     
        printf("\nFailed to malloc compressed_columns");
    }
    if ( full_rows == NULL ){
        succefully_malloc = false;     
        printf("\nFailed to malloc full_rows");    
    }
    if ( nz_per_row == NULL ){
        succefully_malloc = false;
        printf("\nFailed to malloc nz_per_row");    
    }

    if ( !succefully_malloc ) {      
        printf("\nSo the program is exiting \n");  
        exit(1) ;
    }
    
    
    
    #ifdef DEBUG_LOADING
    printf("After malloc \n") ;
    #endif

    // Count how many times each node appears
    for ( int i = 0 ; i < 2 * nz ; i++ ){
        nz_per_row[ normal_columns[i]  ]++;
    }

    
    #ifdef DEBUG_LOADING
    printf("After counting \n") ;
    #endif


    // Find cumsum to fill compressed_columns
    int cumsum = 0 ; 
    for ( int i = 0 ; i <= M ; i++ ){
        (*compressed_columns)[i] = cumsum ; 
        cumsum += nz_per_row[i] ;

        // Reset it to use it again later 
        nz_per_row[i] = 0 ;  
    }

    
    #ifdef DEBUG_LOADING
    printf("After cumsum \n") ;
    #endif

    // Fill the full_rows
    for ( int i = 0 ; i < 2 * nz ; i++ ){
        int element = normal_columns[i] ;         
        int index_in_full = (*compressed_columns)[element] + nz_per_row[element]++ ; 
        (*full_rows)[index_in_full] = normal_rows[i];
    }

    
    #ifdef DEBUG_LOADING
    printf("After fill full rows \n") ;
    #endif

    // for (int i = 0; i < 2 * nz; i++) {
    //     printf("i = %2d | a =  %2d  | b = %2d \n" , 2*i , normal_columns[i] , normal_rows[i]); 
    // }


    // return ; 
    
    #ifdef DEBUG_LOADING
    printf("Prepare to free \n") ;
    printf("Value at ptr = %p \n", nz_per_row);
    printf("nz_per_row[0] = %d  \n" , nz_per_row[0]) ;
    #endif


    free( nz_per_row ) ; 
    
    #ifdef DEBUG_LOADING
    printf("After free 1\n") ;
    #endif
    free( normal_rows    ) ; 
    
    #ifdef DEBUG_LOADING
    printf("After free 2\n") ;
    #endif
    free( normal_columns ) ; 
    
    #ifdef DEBUG_LOADING
    printf("After free 3\n") ;
    #endif

    
    if (f != stdin) {
        fclose(f);
    }


    /************************/
    /* now write out matrix */
    /************************/

    // mm_write_banner(stdout, matcode);
    
    //printf("Dimentions of \n");
    //mm_write_mtx_crd_size(stdout, M, N, nz);




}



void print_sample(  int total_nodes, int total_number_of_edges, int *full_rows, int *compressed_columns , int max_print){

    int lim_A =  (total_nodes < max_print ) ?  total_nodes: max_print ;
    int lim_B =  (total_number_of_edges < max_print ) ?  total_number_of_edges : max_print ;

    for (int i = 0; i < lim_B; i++) {
        printf("%3d ", i);
    }
    puts("");
    for (int i = 0; i < lim_B; i++) {
        printf("----");
    }
    puts("");
    for (int i = 0; i < lim_A + 1; i++) {        
        printf("%3d ", compressed_columns[i]);
    }
    puts("");
    for (int i = 0; i < lim_B; i++) {
        printf("%3d ", full_rows[i]);
    }
    puts("");
   

}




