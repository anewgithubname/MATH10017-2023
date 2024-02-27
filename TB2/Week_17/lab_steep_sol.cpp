#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Problem
{
    double epsilon;
    double x0; // initial point
    
    virtual double f(double x)
    {
        return sin(x / 2) + cos(x / 4);
    }

    virtual double df(double x)
    {
        return cos(x / 2) / 2 - sin(x / 4) / 4;
    }

    // solve the subproblem
    // argmin_x\in [xt-epsilon, xt+epsilon] f(x)
    double subproblem(double xt)
    {
        double x = xt - epsilon;
        double fmax = -100;
        double xmax = x;
        while (x <= xt + epsilon)
        {
            if (f(x) > fmax)
            {
                fmax = f(x);
                xmax = x;
            }
            x += epsilon / 100; // you can choose fixed spacing.
        }
        return xmax;
    }

public:
    Problem(double eps, double initial_guess)
    {
        epsilon = eps;
        x0 = initial_guess;
    }

    void set_epsilon(double eps){
      epsilon = eps;
    }

    void set_x0(double initial_guess){
      x0 = initial_guess;
    }


    // solve the problem using hill-climbing
    void solve()
    {
        double x0 = -4; // initial point

        double xt = x0;
        double xt_1 = 100; // xt-1

        while (fabs(xt - xt_1) >= 1e-5)
        { // fabs absolute value function
            xt_1 = xt;
            xt = subproblem(xt);
            printf("f(%.4f) = %.4f\n", xt, f(xt));
        }

        printf("Maximum is at %f with value %f\n", xt, f(xt));
    }

    //  solve the problem using the gradient ascent algorithm
    void GAsolve()
    {
        double xt = x0;
        double xt_1 = 100; // xt-1

        while (fabs(xt - xt_1) >= 1e-5)
        { // fabs absolute value function
            xt_1 = xt;
            xt = xt + epsilon * df(xt);
            printf("f(%.4f) = %.4f\n", xt, f(xt));
        }

        printf("Maximum is at %f with value %f\n", xt, f(xt));
    }
};


class NewProblem: public Problem // this is a new problem 
{
    double f(double x) // now, we have a new function to be maximized 
    {
        return -x*x;
    }
    double df(double x) // now, we have a new function to be maximized 
    {
        return -2*x;
    }
    public: 
    NewProblem(double eps, double initial_guess): Problem(eps, initial_guess) {}
};


int main()
{   
    // Solve problem with hill-climbing
    Problem p(0.5, -4);
    printf("hill climbing... \n");
    p.solve();

    // Solve with gradient ascent
    printf("\ngradient ascent... \n");
    // p.set_epsilon(1);
    p.GAsolve();

    // Solutions are identical here

    // Try on another problem: we need the "virtual" keyword in from of Problem::f for this to work!!
    printf("\nsolving a new problem... \n");
    
    NewProblem p2(0.2, -4);

    printf("hill climbing... \n");
    p2.solve();

    printf("\ngradient ascent... \n");
    p2.GAsolve();
}



