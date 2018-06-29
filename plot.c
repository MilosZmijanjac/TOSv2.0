#include "monitor.h"
# define x_semirange 3 /* this is to define the region to be displayed*/
# define y_semirange 2
double f(double);
int roundoff (double y);
void plot()
{
    int a,b,x;
    double func;
    char graph[y_semirange*20+1][x_semirange*20+1];/*To store the graph in a 2D array*/
    
    
    for(a=0;a<=y_semirange*20;a++)/* Drawing the axis of the graph*/
        for(b=0;b<=x_semirange*20;b++)
        {
            graph[a][b]=' ';
            if(b==x_semirange*10)
                graph[a][b]='|';
            if(a==y_semirange*10)
                graph[a][b]='-';
        }
    
    
    for(b=0;b<=x_semirange*20;b++)
    {
        x=b-(x_semirange*10);
        
        func= (f(x));
        
        if(((y_semirange*10)-roundoff(func))>=0&&((y_semirange*10)-roundoff(func))<=y_semirange*20)
            
            graph[((y_semirange*10)-roundoff(func))][b]='o';
    }
    
    for(a=0;a<=y_semirange*20;a++)
    {
        for(b=0;b<=x_semirange*20;b++)
            
            putc(graph[a][b]);
        
        puts("\n");
    }
    
}
double f(double x) /*holds the function to be graphed. Can be easily overwritten*/
{
    
    return x+1;
}
/* Function for converting the double values to int so it can be stored in the array*/
int roundoff ( double y )
{
    int i;
    if (y >= 0)
        i = (int)(y + 0.5);
    else
        i = (int)(y - 0.5);
    return i;
}
