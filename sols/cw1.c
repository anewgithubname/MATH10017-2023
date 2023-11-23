#include <stdio.h>
#include <math.h>

const double PI = 3.141592653; // declare PI and initialize it with 3.1415926...

/*
plot sin(ax+b)
input: a, b
output: nothing, just prints the graph
*/
void plot(double a, double b)
{
    // printf("Please expand your commandline window if the graph is not displayed properly.\n\n");
    printf("Function graph for sin(%.2fx+%.2f):\n\n", a, b);
    for (double y = 1; y >= -1; y = y - .2) // loop over each y value
    {
        for (double x = 0; x <= PI * 2; x = x + .1) // loop over each x value
        {
            if (fabs(y) < 1e-5)//print x axis labels
            {
                if (fmod(x, PI / 2) < 1e-1) // print an x mark for multiples of pi/2
                {
                    printf("X");
                }
                else
                {
                    printf("-");
                }
            }
            else if (fabs(x) < 1e-5)//print y axis label
            {
                printf("|");
            }
            else
            {
                if (fabs(y - sin(a * x + b)) < .1) // print function sin(ax+b)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void main()
{
    // test my function
    plot(2, PI / 2);
}