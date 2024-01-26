#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

struct matrix
{
    int numrow;
    int numcol;
    int *elements;
};
typedef struct matrix Matrix;

/*
Print an image to the console. 
image: an array stores the flattened image stored in row major order.
Height: the height of the image.
Width: the width of the image.
*/
void image2char(int image[], int Height, int Width)
{
    //See lab 7, how images are stored in computers
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/lecs/lec8.pdf
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            if( image[i*Width + j] < 85){
                printf(" ");
            }
            else if(image[i*Width + j] <170){
                printf("I");
            }else{
                printf("M");
            }
        }
        printf("\n");
    }
}


/*
Read a matrix from file. Don't change it!
filename: the file that contains the matrix.
return: a matrix structure containing the matrix.
*/
Matrix read_matrix(char *filename)
{
    FILE *f = fopen(filename, "rb");
    // read int variables to the file.
    int numrow = getw(f);
    int numcol = getw(f);
    Matrix M = {numrow, numcol, calloc(numrow * numcol, sizeof(int))};

    for (int i = 0; i < M.numrow; i++)
    {
        for (int j = 0; j < M.numcol; j++)
        {
            M.elements[i*numcol + j] = getc(f);
        }
    }

    fclose(f);
    return M;
}

/*
Retrieve an element from a matrix.
M: the matrix.
i,j: the row and column of the element.
return: the element at row i and column j.
*/
int get_elem(Matrix M, int i, int j)
{
    //see lecture 9 for row major order
    return M.elements[i*M.numcol + j];
}

/*
Assign value to an element in a matrix.
M: the matrix.
i,j: the row and column of the element.
value: the value to be assigned.
*/
void set_elem(Matrix M, int i, int j, int value)
{
    //see lecture 9 for row major order
    M.elements[i*M.numcol + j] = value;
}

/*
Compute the pairwise squared distance of the i-th row of M1 and the j-th row of M2.
M1: the first matrix.
M2: the second matrix.
return: a matrix D where D_ij is the squared distance between the i-th row of M1 and the j-th row of M2.
*/
void pairwise_dist2(Matrix M1, Matrix M2, Matrix D)
{
    //Have a look at lab 9, matrix multiplication algorithm
    //Do they look similar? What are the similarities and differences?
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/labs/lab9.pdf
    // loop over each row of M1
    for (int i = 0; i< M1.numrow; i++)
    {
        // loop over each row of M2
        for (int j = 0; j < M2.numrow; j++)
        {
            // compute D_ij = sum_k (M1_ik - M2_jk)^2
            int sum = 0;
            for (int k = 0; k < M1.numcol; k++)
            {
                int diff = get_elem(M1, i, k) - get_elem(M2, j, k);
                sum += diff * diff;
            }
            set_elem(D, i, j, sum);
        }
    }
}

/*
Find the index of the minimum element in an array. 
a: the array.
len: the length of the array.
return: the index of the minimum element in the array.
example: [1,2,3,4,5] -> 0
         [5,4,3,2,1] -> 4
*/
int find_min_index(int a[], int len)
{
    // for more information, see the last tutorial in TB1
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/labs/tutorial6.pdf
    //set the initial minimum value to be the first element in the array.
    int min = a[0];
    int min_idx = 0;

    // compare the minimum value with the rest of the elements in the array.
    for (int i = 1; i < len; i ++){ 
        // if the current element is smaller than the current minimum value, 
        // update the minimum value and the index.
        if (a[i] < min){
            min = a[i];
            min_idx = i;
        }
    }
    return min_idx;
}

/*
Find the indices of 5 minimum elements in an array.
a: the array.
len: the length of the array.
return: an array of 5 integers containing the indices of the 5 minimum elements in a.
example: [1,2,33,4,5,23,6] -> [0,1,3,4,6]
*/
void minimum5(int a[], int len, int indices[])
{
    // this is a bit challenging. 
    // However, pay attention to the second task in the last tutorial. 
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/labs/tutorial6.pdf
    for (int i = 0; i < 5; i++)
    {
        indices[i] = find_min_index(a, len);
        // after finding the minimum index, set the value to be INT_MAX
        // so it won't be found again.
        a[indices[i]] = INT_MAX;
    }
}

void print(Matrix M){
    // matrix printing, see lab 8
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", get_elem(M, i, j));
        }
        printf("\n");
    }
}

void main()
{
    // 10% for submitting the correct code.
    Matrix X = read_matrix("./X.matrix");
    printf("N: %d, M: %d\n", X.numrow, (int) sqrt(X.numcol));   

    Matrix T = read_matrix("./T.matrix");
    printf("L: %d\n", T.numrow);

    Matrix Y = read_matrix("./Y.matrix");
    int s = 0;
    for (int i = 0; i < Y.numrow; i++)
    {
        if(Y.elements[i*Y.numcol + 0] == 1)
            s++;
    }
    printf("Number of 1 in the training set: %d\n", s);

    //TODO: construct the matrix D, where D_ij is the squared distance between the i-th row of T and the j-th row of X.
    // 40% of the total score.
    // 15% for the helper functions.
    // 25% for the pairwise_dist2 function.

    // See lecture 9 for heap memory allocation of structs
    // https://github.com/anewgithubname/MATH10017-2022/blob/main/lecs/lec9_.pdf
    // allocate HEAP memory for D
    Matrix D = {T.numrow, X.numrow, calloc(T.numrow * X.numrow, sizeof(int))};
    // compute the pairwise distances
    pairwise_dist2(T, X, D);

    // print out a subatrix of D, for checking. 
    print(D);

    // loop over each testing image
    for(int i=0; i<D.numrow; i++){
        printf("The %d-th testing image:\n", i);
        // visualize the image
        image2char(T.elements + i*T.numcol, 28, 28);

        // get the indices with the 5 smallest distances to the 
        // i-th testing image.
        int indices[5];
        // see How I indexed the i-th row of D. 
        minimum5(D.elements + i*D.numcol, D.numcol, indices);
        
        // collect the labels of the 5 nearest neighboring images.
        // how many 1s are there?
        int count = 0;
        for(int j=0; j<5; j++){
            if(get_elem(Y, indices[j], 0) == 1)
                count++;
        }

        printf("The %d-th testing image is classified as", i);
        if(count >= 3)
            printf(" 1.\n");
        else
            printf(" not 1.\n ");
        
        printf("\n");
        printf("----------------------------------------\n");
    }

    // free matrix D
    free(D.elements);
    free(X.elements);
    free(T.elements);
    free(Y.elements);
}