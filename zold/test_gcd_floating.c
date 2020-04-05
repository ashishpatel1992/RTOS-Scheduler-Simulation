#include<stdio.h>
#include<math.h>

// Calculates GCD of two numbers
// Ref: https://www.geeksforgeeks.org/program-find-gcd-floating-point-numbers/
double gcd(double a, double b) 
{ 
    if (a < b) 
        return gcd(b, a); 
  
    // base case 
    if (fabs(b) < 0.001) 
        return a; 
  
    else
        return (gcd(b, a - floor(a / b) * b)); 
} 
//Calculates GCD for multiple numbers
// int *arr - input numbers
float array_gcd(double arr[], int n) 
{ 
    int result = arr[0]; 
    for (int i = 1; i < n; i++) 
    { 
        result = gcd(arr[i], result); 
  
        if(result == 1) 
        { 
           return 1; 
        } 
    } 
    return result; 
} 
int main(int argc, char const *argv[])
{
    // array_gcd()
    float x = gcd(5.22222,25);
    printf("%f",x);
    return 0;
}
