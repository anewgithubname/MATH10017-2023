#include <stdio.h>
#include <string.h> // for string compare function 'strcmp'

// SORTING STRINGS
/*
** swap: swap the i and j elements of an array of strings
*/
void swap(char* array[], int i, int j){
    char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

/*
** find_max_idx: find the index of the "largest" string in array
*/
int find_max_idx(char* array[], int len){
    int idx = 0;
    char* max = array[0];
    int tmp;
    for (int i = 1; i < len; i++)
    {
        tmp = strcmp(array[i], max);
        if(tmp > 0){
            max = array[i];
            idx = i; 
        }
    }
    
    return idx; 
}

void print_array(char* array[], int len){
    for(int i = 0; i < len; i++){
        printf("%s; ", array[i]);
    }
    printf("\n");
}

/*
** sort: sort array of strings in ascending order
*/
void sort(char* array[], int len){
      for (int i = 1; i <= len-1; i++){
        
        int max_idx = find_max_idx(array, len - i + 1); 

        swap(array, max_idx, len - i);
    }
}

/*
** sort_v2: sort array of strings in ascending order using a *recursive* algorithm
*/
void sort_v2(char* array[], int len){
    int max_idx = find_max_idx(array, len); 
    swap(array, max_idx, len - 1);

    if(len>1){ 
        sort_v2(array, len-1);
    }
}


// STRING COMPARISON
/*
** my_strcmp: return <0 if s<t, 0 if s==t, >0 if s>t
*/
int my_strcmp(char* s, char* t){
 int i = 0;
 int diff = 0;
 while(diff == 0){
  diff = s[i] - t[i];
  if( s[i] == '\0' ){
    break;
  }
  i++;
 }
 return(diff);
}

int main(){
    // MAKE SOME STRINGS
    char* s1 = "string 1";
    char* s2 = "hello, world!";
    char* s3 = "about";
    char* s4 = "zebra";
    int len = 4;

    // TEST SORT
    printf("TESTING sort\n\n");
    char* arr1[] = {s1, s2, s3, s4};
    sort(arr1, 4);
    // YOUR CODE HERE
    print_array(arr1, 4);
    printf("\n\n");
    

    printf("TESTING sort2\n\n");
    char* arr2[] = {s1, s2, s3, s4};
    sort_v2(arr2, 4);
    print_array(arr2, 4);
    printf("\n\n");

    printf("TESTING my_strcmp\n\n");
    int diff;
    char* arr3[] = {"cat", "horse", "pillow", "hello", "goodbye"};
    char* arr4[] = {"horse", "pillow", "pillow", "cat", "good"};
    for(int i = 0; i < 5; i++){
     printf("%s - ", arr3[i]);
     printf("%s = ", arr4[i]);
     diff = my_strcmp(arr3[i], arr4[i]);
     printf("%d ", diff);
     printf("\n\n");
    }

}
