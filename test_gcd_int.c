#include<stdio.h>
//Calculates GCD of two numbers
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b % a, a); 
} 
//Calculates GCD for multiple numbers
// int *arr - input numbers
int array_gcd(int arr[], int n) 
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
    array_gcd()
    int x = gcd(5,25);
    printf("%d",x);
    return 0;
}
