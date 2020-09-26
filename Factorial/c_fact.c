/*
* Program to calculate factorials in generic C.
*/
#include <stdio.h>
int main() {
    
    int n, i;
    unsigned long long fact = 1;
    
    printf("factorial program\n");
    printf("input number n= \n");
    scanf("%d", &n);
    
    for (i = 1; i <= n; ++i) {
            fact *= i;
    }
    
    printf("Factorial of %d = %llu\n", n, fact);
    return 0;
}
