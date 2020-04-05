#include<stdio.h>
#include<math.h>

typedef long long int ll; 
  
// Utility function to find 
// GCD of 'a' and 'b' 
double gcd_double(double a, double b) 
{ 
    if (a < b) 
        return gcd_double(b, a); 
  
    // base case 
    if (fabs(b) < 0.001) 
        return a; 
  
    else
        return (gcd_double(b, a - floor(a / b) * b)); 
} 
  
// Returns LCM of array elements 
double findlcm(double arr[], int n) 
{ 
    // Initialize result 
    double ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / 
                (gcd_double(arr[i], ans))); 
  
    return ans; 
} 
  
// Driver Code 
int main() 
{ 
    double arr[] = { 1.0,1.8,1,2 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    printf("%lf", findlcm(arr, n)); 
    return 0; 
} 