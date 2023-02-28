
#ifndef load_matrix_h
#define load_matrix_h



// typedef unsigned int uint;

char* select_file_to_load(  char* default_path );

char* generate_filename(char* relative_path, char* file_name); 

void scanf_check( int number_of_output_arguments_expected , int actual_output_arguments ); 

void load_file(const char *file_name, int *total_nodes, int *total_number_of_edges, int **full_rows, int **compressed_columns);

void print_sample(  int total_nodes, int total_number_of_edges, int *full_rows, int *compressed_columns , int max_print);

char* decide_file_to_load( int option_chosen , char* default_path , int max_options );


void check_results( int* sigma , int option_chosen ) ; 


#endif