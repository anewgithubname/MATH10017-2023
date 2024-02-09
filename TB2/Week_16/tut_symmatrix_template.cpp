#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <utility>


class matrix
{
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

    int get_elem(int i, int j) const
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

    ~matrix()
    {
        printf("freeing the matrix...\n");
        free(elements);
    }

    // print all elements in the matrix
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

class symmmatrix: public matrix{

public:

    // TODO: Write a constructor that takes one argument for both dimensions of the matrix.
  
    /*
    void set_elem(int i, int j, int value)
    {
    // TODO: Rewrite set_elem function so that it preserves the symmetry of the matrix.
    // This version uses matrix::
    }

    void set_elem_v2(int i, int j, int value)
    {
    // TODO: Rewrite set_elem function so that it preserves the symmetry of the matrix.
    // This version uses the "protected" keyword
    } */

};

int main()
{
    // TODO adapt this for symmetric matrices
    // construct B: a 3x3 matrix.
    matrix A(3, 3);

    for (int i = 0; i < 3; i++){
        for (int j = i; j < 3; j++){
            A.set_elem(i, j, rand() % 10);
        }
    }
    A.print();

}
