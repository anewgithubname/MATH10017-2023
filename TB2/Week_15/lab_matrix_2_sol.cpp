#include <stdio.h>
#include <stdlib.h>
#include <climits>

class matrix
{
    int num_rows;
    int num_cols;
    int *elements;

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

void read_image(int image[])
{
    FILE *in = fopen("surprise.dat", "rb");
    int count = 0;
    unsigned char b = fgetc(in);
    while (!feof(in))
    {
        image[count] = b;
        b = fgetc(in);
        count++;
    }
    fclose(in);
}

class image: public matrix
{

public:
    image(int height, int width, int *data): matrix(height, width)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                set_elem(i, j, data[i * width + j]);
            }
        }
    }

    void show(){
    //See lab 7, how images are stored in computers
    //https://github.com/anewgithubname/MATH10017-2023/blob/main/lecs/lec8.pdf
    for(int i = 0; i < get_num_rows(); i++){
        for(int j = 0; j < get_num_cols(); j++){
            if( get_elem(i,j) < 85){
                printf(" ");
            }
            else if(get_elem(i,j) <170){
                printf("I");
            }else{
                printf("M");
            }
        }
        printf("\n");
    }
    }

};

int main()
{
    // testing code for the matrix class.
    
    int HEIGHT = 45; 
    int WIDTH = 44;
    int *data = (int *)malloc(HEIGHT * WIDTH * sizeof(int));

    read_image(data);
    image img(HEIGHT, WIDTH, data);
    img.show();

    free(data);
}
