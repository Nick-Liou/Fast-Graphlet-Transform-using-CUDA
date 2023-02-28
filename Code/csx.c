/*
 *
 * Created by:   github.com/johnstef99
 * Last updated: 2022-11-23
 *
 */

#include "csx.h"
#include <stdlib.h>

csx csx_new(int vertices, int edges) {
  csx csc = malloc(sizeof(struct CSX));
  csc->v = vertices;
  csc->e = edges;
  csc->com = malloc((vertices + 1) * sizeof(int));
  csc->unc = malloc(edges * sizeof(int));

  if (!csc || !csc->com || !csc->unc) {
    fprintf(stderr, "Counldn't create CSC for %d vertices and %d edges\n",
            vertices, edges);
    exit(1);
  }
  return csc;
}

csx csx_new_calloc(int vertices, int edges) {
  csx csc = malloc(sizeof(struct CSX));
  csc->v = vertices;
  csc->e = edges;
  csc->com = calloc((vertices + 1), sizeof(int));
  csc->unc = calloc(edges, sizeof(int));

  if (!csc || !csc->com || !csc->unc) {
    fprintf(stderr, "Counldn't create CSC for %d vertices and %d edges\n",
            vertices, edges);
    exit(1);
  }
  return csc;
}

void csx_free(csx matrix) {
  free(matrix->com);
  free(matrix->unc);
  free(matrix);
}

csx csx_transpose(csx original) {
  csx tran = csx_new_calloc(original->v, original->e);

  // count how many vertices each vertice points to or is pointed from
  int *counter = calloc(original->v, sizeof(int));
  for (int i = 0; i < original->e; i++) {
    counter[original->unc[i]]++;
  }

  // make the compressed row/col
  for (int i = 1; i < original->v + 1; i++) {
    tran->com[i] = tran->com[i - 1] + counter[i - 1];
  }

  // make the non-compressed col/row
  for (int i = 0; i < original->v; i++) {
    for (int j = original->com[i]; j < original->com[i + 1]; j++) {
      int points_to = original->unc[j];
      int dest = tran->com[points_to];

      tran->unc[dest] = i;
      tran->com[points_to]++;
    }
  }

  // correct the modified compressed row/col
  for (int col = 0, last = 0; col <= tran->v; col++) {
    int temp = tran->com[col];
    tran->com[col] = last;
    last = temp;
  }

  free(counter);
  return tran;
}

void csx_print(csx matrix) {
    int max_print = 50  ; 
    int lim =  (matrix->v < max_print ) ?  matrix->v : max_print ;
    int lim_B =  (matrix->e < max_print ) ?  matrix->e : max_print ;
    for (int i = 0; i < lim_B; i++) {
        printf("%3d ", i);
    }
    puts("");
    for (int i = 0; i < lim_B; i++) {
        printf("----");
    }
    puts("");
    for (int i = 0; i < lim + 1; i++) {
        if (i < matrix->v + 1)
        printf("%3d ", matrix->com[i]);
    }
    puts("");
    for (int i = 0; i < lim_B; i++) {
        printf("%3d ", matrix->unc[i]);
    }
    puts("");
   

}


void check_csx( csx matrix ){

    int count = 0 ; 
    for ( int i = 0 ; i < matrix->v ; i++ ){
        // Check the sublist
        
        for ( int j = matrix->com[i]  ; j < matrix->com[i+1]-1 ; j++ ){
            if ( matrix->unc[j] > matrix->unc[j+1]  ){
                printf("Not greater!! at i = %d and j = %d \n" , i , j ) ; 
                if ( count++ == 10 ){
                    break; 
                }
            }
        }
    }

    if ( count == 0 ){
        printf("\nAll correct and sorted !! \n");
    }


}

/*
 * Function:  csc_from_file
 * ------------------------
 * Reads a .mtx file and stores it in CSC format
 *
 * path: the path of the file to read the matrix from
 *
 * returns: The matrix in a CSC format
 */
csx csc_from_file(char *path , int** p1) {
	int ret_code;
	MM_typecode matcode;
	FILE *f;
	int M, N, nz;

  
    
	if ((f = fopen(path, "r")) == NULL) {
		fprintf(stderr, "Couldn't open file %s\n", path);
		// fprintf(stdout, "Couldn't open file %s\n", path);
		
		exit(1);
	}

	if (mm_read_banner(f, &matcode) != 0) {
		printf("Could not process Matrix Market banner.\n");
		exit(1);
	}

	if (!mm_is_matrix(matcode) || !mm_is_pattern(matcode) ||  !mm_is_symmetric(matcode)) {
		fprintf(stderr, "MTX format not supported, only matrix pattern symmetric files are supported!\n");
		exit(1);
	}

	if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) != 0){
		exit(1);
	}

  
    
	// Read mtx file to COO
	int *coo_row = malloc(nz * 2 * sizeof(int));
	int *coo_col = malloc(nz * 2 * sizeof(int));

	int a, b, j;
	int k = 0;
	for (int i = 0; i < nz; i++) {
		fscanf(f, "%d %d%*[ ]%*f\n", &a, &b);
		coo_row[k] = a - 1;
		coo_col[k] = b - 1;
		if (coo_row[k] == coo_col[k]) {
			fprintf(stderr, "Found self-loop!\n");
		}
		coo_row[k + 1] = coo_col[k];
		coo_col[k + 1] = coo_row[k];
		k += 2;
	}

	// Covert COO to CSC
	csx csc = csx_new(M, nz * 2);

  
    
  // count number of non-zero elements in each column
  int *col_count = calloc(M, sizeof(int));
  for (int i = 0; i < nz * 2; i++) {
    col_count[coo_col[i]]++;
  }

  /* cumulative sum of column count */
  int index = 0;
  for (int i = 0; i < M; i++) {
    csc->com[i] = index;
    index += col_count[i];
  }
  csc->com[M] = nz * 2;

  /* re-initialize column count */
  for (int i = 0; i < M; i++) {
    col_count[i] = 0;
  }

  // fill row indices and values in CSC format
  for (int i = 0; i < nz * 2; i++) {
    j = coo_col[i];
    k = csc->com[j] + col_count[j];
    csc->unc[k] = coo_row[i];
    col_count[j]++;
  }

  // free(col_count); // Use it since it is already calculated 
  *p1 = col_count ; 
  free(coo_row);
  free(coo_col);

  fclose(f);

  /* mm_write_banner(stdout, matcode); */
  /* mm_write_mtx_crd_size(stdout, M, N, nz); */
  /* puts("--------------"); */

  return csc;
}