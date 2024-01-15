#include <stdio.h>
#include <stdlib.h>

// swap two elements in an array 
void swap(int array[], int i, int j){
    
    // YOUR CODE HERE

}

// find the index of the largest element in an array
int find_max_idx(int array[], int len){ 
     
     // YOUR CODE HERE
     return 1; // Just for the sake of returning something

}

// print an array
void print_array(int array[], int len){
    
    // YOUR CODE HERE
    
}

// sort an array
void sort(int array[], int len){

    // YOUR CODE HERE

}

// recursive version
void sort_v2(int array[], int len){
   
   // YOUR CODE HERE
}

// selection sort: loop version
void sort_sel_loop(int array[], int len){
 
 // YOUR CODE HERE

}

// selection sort: recursive version
void sort_sel_rec(int array[], int len){

  // YOUR CODE HERE

}

void main()
{
    int array[] = {5,3,2,4};
    int len = 4;
    
    printf("testing find_max_idx-----------------------\n");
    // testing find_min_idx
    int min_idx = find_max_idx(array, len);
    printf("max_idx: %d\n", min_idx);

    printf("testing swap-----------------------\n");
    //testing swap
    swap(array, 0, 1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("testing sort-----------------------\n");
    //test sort
    int a [] = {5, 3, 2, 1, 2, 4};
    len = 6;
    // YOUR CODE HERE
    print_array(a, len);

    int b [] = {5, 3, 2, 1, 2, 4};
    printf("testing sort (recursive)-----------------------\n");
    // YOUR CODE HERE
    print_array(b, len);

    int c [] = {5, 3, 2, 1, 2, 4};
    printf("testing selection sort (loop)-----------------------\n");
    // YOUR CODE HERE
    print_array(c, len);

    int d [] = {5, 3, 2, 1, 2, 4};
    printf("testing selection sort (loop)-----------------------\n");
    // YOUR CODE HERE
    print_array(d, len);
}