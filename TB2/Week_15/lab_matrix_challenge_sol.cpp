#include <stdio.h>
#include <stdlib.h>
#include <climits>

class matrix
{
    // TODO: Write a matrix class with three private fields:
    //   num_rows: integer, stores the number of rows
    //   num_cols: integer, stores the number of columns
    //   elements: integer pointer, pointing to a contiguous memory stores a row-major matrix.

    int num_rows;
    int num_cols;
    int *elements;

    // all functions below must be PUBLIC!

public:

    int get_num_rows() { return num_rows; }
    int get_num_cols() { return num_cols; }

    // TODO: Write set_elem and get get_elem functions. Must check for invalid indices.
    //  Use zreo-based indexing!

    void set_elem(int i, int j, int value)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
        }
        else
        {
            elements[i * num_cols + j] = value;
        }
    }

    // TODO: Write a print function.

    int get_elem(int i, int j)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
            return INT_MAX;
        }
        else
        {
            return elements[i * num_cols + j];
        }
    }

    // TODO: Write an add function. Must check for invalid dimensions.
    void add(matrix B)
    {
        if (num_rows != B.num_rows || num_cols != B.num_cols)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            for (int i = 0; i < num_rows; i++)
            {
                for (int j = 0; j < num_cols; j++)
                {
                    set_elem(i, j, get_elem(i, j) + B.get_elem(i, j));
                }
            }
        }
    }

    // TODO: Write a constructor, which takes three arguments: nrow, ncol, and elem.
    //  Must check nrow and ncol are positive integers. If they are not, print "invalid dimensions!" and do nothing.
    matrix(int nrow, int ncol)
    {
        if (nrow <= 0 || ncol <= 0)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            num_rows = nrow;
            num_cols = ncol;
            printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(int));
        }
    }

    matrix(const matrix &M){
     // do deep copy
     // not only copy variables, 
     // but also copy the memory they point to.
     num_rows = M.num_rows;
     num_cols = M.num_cols; 
     printf("allocating memory for the matrix...\n");
     elements = (int *)malloc(num_rows * num_cols * sizeof(int));
     for(int i = 0; i < num_rows * num_cols; i++){
        elements[i] = M.elements[i];
     }
    }

    ~matrix()
    {
        printf("freeing the matrix...\n");
        free(elements);
    }

    // print out
    void print()
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                printf("%d ", get_elem(i, j));
            }
            printf("\n");
        }
    }

};

matrix mult_matrices(matrix A, matrix B)
{
  int nr = A.get_num_rows();
  int nc = A.get_num_cols();

  matrix C(nr, nc);

    for (int i = 0; i < nr; i++)
            {
                for (int j = 0; j < nc; j++)
                {
                    C.set_elem(i, j, A.get_elem(i, j) * B.get_elem(i, j));
                }
            }        
  return C;
}



int main()
{
    // testing code for the matrix class.
   
    int nr = 3; 
    int nc = 3;
  
    matrix A(nr, nc);
    matrix B(nr, nc);

    for(int ir = 0; ir < nr; ir++){
     for(int ic = 0; ic < nc; ic++){
      A.set_elem(ir, ic, ir);
      B.set_elem(ir, ic, ic);
     }   
    }

    printf("\n A: \n\n");
    A.print();

    printf("\n B: \n\n");
    B.print();

    matrix C = mult_matrices(A, B);
   
    printf("\n C: \n\n");
    C.print();

    A.add(B);

    printf("\n A: \n\n");
    A.print();
}
