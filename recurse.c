#include <stdio.h>

int f(int n);

int main(int num, char* args[]) {
    int n;
    sscanf(args[num-1], "%d", &n);
    int fib = f(n);
    printf("%d\n", fib);
    return 0;
}

int f(int n) {
    if (n == 0) return 5;
    return 4*n + 2*f(n-1) + 3;
}