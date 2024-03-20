#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// the class below is copied from the previous assignment (with some modifications)
class matrix
{
    int num_rows;
    int num_cols;
    int *elements;

    public:
    int get_ncols(){
      return num_cols;  
    }

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
            return 'N';
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

    // Copy constructor
    matrix(const matrix & A_){
      printf("allocating memory for the matrix (copy constructor)...\n");
      num_rows = A_.num_rows;
      num_cols = A_.num_cols;
      elements = (int *)malloc(num_rows * num_cols * sizeof(int));
      for(int i = 0; i < num_rows; i++){
              for(int j = 0; j < num_cols; j++){
               elements[i * num_cols + j] = A_.get_elem(i, j);   
            }
     }
    }

    ~matrix() {
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

class Algorithm {

    private:

    matrix A_;
    double *beta;
    double *alpha;
    double *beta_old;
    double *alpha_old;
    int converged;

    void normalizeScores(double *scores) {
        double norm = 0.0;
        for (int i = 0; i < A_.get_ncols(); i++) {
            norm += scores[i] * scores[i];
        }
        norm = sqrt(norm);

        for (int i = 0; i < A_.get_ncols(); i++) {
            scores[i] = scores[i] / norm;
        }
    }

    bool convergence_check(double * score1, double * score2, double tol) {
        int num_papers = A_.get_ncols();

        for (int i = 0; i < num_papers; ++i) {
            if (abs(score1[i] - score2[i]) > tol) {
                return false;
            }
        }

        return true;
    }

 public:
    Algorithm(matrix &A) : A_(A) {

     converged = 0;
     printf("allocating memory for the scores vectors...\n");
     beta = (double *)malloc(A.get_ncols() * sizeof(double)); 
     alpha = (double *)malloc(A.get_ncols() * sizeof(double)); 
     beta_old = (double *)malloc(A.get_ncols() * sizeof(double)); 
     alpha_old = (double *)malloc(A.get_ncols() * sizeof(double)); 
     for(int i = 0; i < A.get_ncols(); i++){
        beta[i] = alpha[i] = 1.0; 
     }
    
    }

    void run(int max_iter = 100, double tol = 1e-6) {

        int num_papers = A_.get_ncols();
        converged = 0;

        // Run the algorithm
        for (int iter = 0; iter < max_iter; ++iter) {

            for (int i = 0; i < num_papers; ++i) {
             alpha_old[i] = alpha[i];
             beta_old[i] = beta[i];
            } 

            // Update alpha scores
            double acc;
            for (int i = 0; i < num_papers; ++i) {
                acc = 0.0;
                for (int j = 0; j < num_papers; ++j) {
                    if (A_.get_elem(j, i) > 0.0) {
                        acc += beta[j];
                    }
                }
             alpha[i] = acc;
            }

            // Update beta scores
            for (int i = 0; i < num_papers; ++i) {
                acc = 0.0;
                for (int j = 0; j < num_papers; ++j) {
                    if (A_.get_elem(i, j) > 0.0) {
                        acc += alpha[j];
                    }
                }
                beta[i] = acc;
            }

            // Normalize scores
            normalizeScores(beta);
            normalizeScores(alpha);

            // Check for convergence
            if (convergence_check(alpha, alpha_old, tol) && convergence_check(beta, beta_old, tol) ) {
                converged = 1;
                break;
            }

          
        }

    }

    void print_alpha() {
        for (int i = 0; i < A_.get_ncols(); i++) {
         printf("%f " , alpha[i]);
        }
    }

    void print_beta() {
        for (int i = 0; i < A_.get_ncols(); i++) {
         printf("%f " , beta[i]);
        }
    }

    void print_conv(){
      printf("%d ", converged);
    }

   ~Algorithm() {
        printf("freeing memory for the scores vectors...\n");
        free(beta);
        free(alpha);
        free(beta_old);
        free(alpha_old);
    }

}; 

int main() {
    
    double a[] = {0, 1, 1, 0, 0, 0, 0, 
                  0, 0, 1, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0,
                  0, 0, 1, 0, 1, 1, 0,
                  1, 1, 1, 0, 0, 1, 0,
                  1, 0, 1, 0, 0, 0, 0,
                  1, 1, 1, 1, 1, 1, 0};
    
    matrix A(7, 7);

    for (int i = 0; i < 49; i++){
      A.set_elem(i / 7, i % 7, a[i]);
    }
   
   printf("\n");
   printf("A: \n\n");
   A.print();
   printf("\n");

   Algorithm algo(A);
   algo.run(); 
   printf("\n");

   printf("Did we converge? ");
   algo.print_conv();
   printf("\n\n");

   printf("Impact scores: \n");
   algo.print_alpha();
   printf("\n\n");

   printf("Knowledge scores: \n");        
   algo.print_beta();
   printf("\n\n");

   return 0;
}
