#include <stdio.h>

class matrix{
  //TODO: Write a matrix class with three private fields: 
  //  num_rows: integer, stores the number of rows 
  //  num_cols: integer, stores the number of columns
  //  elements: integer pointer, pointing to a contiguous memory stores a row-major matrix.
  
  int num_rows;
  int num_cols;
  int *elements;
  
  // all functions below must be PUBLIC!
  
public: 
  
  //TODO: Write set_elem and get get_elem functions. Must check for invalid indices.
  // Use zero-based indexing!
  
  void set_elem(int i, int j, int value){
    if (i < 0 || i >= num_rows || j < 0 || j >= num_cols){
      printf("invalid indices!\n");
    }else{
      elements[i * num_cols + j] = value;
    }
  }
  
  int get_elem(int i, int j){
    if (i < 0 || i >= num_rows || j < 0 || j >= num_cols){
      printf("invalid indices!\n");
    }else{
      return elements[i * num_cols + j];
    }
  }
  
  //TODO: Write an add function. Must check for invalid dimensions.
  
  void add(matrix B){
    if (num_rows != B.num_rows || num_cols != B.num_cols){
      printf("invalid dimensions!\n");
    }else{
      for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
          set_elem(i, j, get_elem(i, j) + B.get_elem(i, j));
        }
      }
    }
  }
  
  //TODO: Write a constructor, which takes three arguments: nrow, ncol, and elem.
  // Must check nrow and ncol are positive integers. If they are not, print "invalid dimensions!" and do nothing.
  
  matrix(int nrow, int ncol, int *elem){
    if (nrow <= 0 || ncol <= 0){
      printf("invalid dimensions!\n");
    }else{
      num_rows = nrow;
      num_cols = ncol;
      elements = elem;
    }
  }
  
  // print out 
  void print(){
    for (int i = 0; i < num_rows; i++){
      for (int j = 0; j < num_cols; j++){
        printf("%d ", get_elem(i, j));
      }
      printf("\n");
    }
  }
  
};

int main(){
  //testing code for the matrix class.
  
  // prepare data in the stack memory. In this lab, DO NOT USE HEAP MEMORY.
  int num_rows = 2;
  int num_cols = 3;
  
  int elementsA[] = {1, 2, 3, 4, 5, 6};
  int elementsB[] = {7, 8, 9, 10, 11, 12};
  
  // TODO: After you finished writing your matrix class, uncomment the following code and test your matrix class.
  
  // create two matrices, with constructor.
  matrix A(num_rows, num_cols, elementsA);
  matrix B(num_rows, num_cols, elementsB);
  
  printf("printing A\n");
  A.print();
  
  printf("\nprinting B\n");
  B.print();
  
  printf("--------------------\n");
  
  // test your setter and getter functions.
  printf("setting A(0, 0) to 9\n");
  A.set_elem(0, 0, 9);
  printf("printing A\n");
  A.print();
  printf("\n");
  
  // using the setter function but with invalid indices.
  printf("setting B(2, -2) to 100\n");
  B.set_elem(2, -2, 100);
  printf("printing B\n");
  B.print();
  printf("\n");
  
  // write your own code and test your add function:
  printf("adding B to A\n");
  A.add(B);
  printf("printing A\n");
  A.print();
  printf("\n");
  
  // write your own code and test your add function but with incompatible dimensions:
  // Hint: you can create a new matrix C which is 3 by 2, and test your add function.
  
  int elementsC[] = {1, 2, 3, 4, 5, 6};
  matrix C(3, 2, elementsC);
  printf("adding C to A\n");
  A.add(C);
  printf("printing A\n");
  A.print(); // A should not change!
}