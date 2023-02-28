/*
 *
 * Created by:   github.com/johnstef99
 * Last updated: 2022-11-23
 *
 */

#ifndef CSX_H
#define CSX_H

#include <stdio.h>
#include <stdlib.h>

#include "mmio.h"

/* Compressed Sparse Row/Column */
struct CSX {
  /* num of vertices */
  int v;
  /* num of edges */
  int e;
  /* compressed row/col */
  int *com;
  /* uncompressed col/row */
  int *unc;
};

typedef struct CSX *csx;

csx csx_new(int vertices, int edges);       // extra
csx csx_new_calloc(int vertices, int edges) ; // rename

csx csx_transpose(csx matrix);

void csx_print(csx matrix); // Some changes

csx csc_from_file(char *path  , int** p1 ); // Extra return p1

void csx_free(csx matrix); // Changes

void check_csx( csx matrix ); // Extra

#endif