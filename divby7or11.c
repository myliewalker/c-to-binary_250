#include <stdio.h>

int main(int num, char* args[]) {
    int total;
    sscanf(args[num-1], "%d", &total);
    int count = 0;
    int current = 7;
    int numbers[total];

    while (count < total) {
        if (current%7 == 0 || current%11 == 0) {
            numbers[count] = current;
            count++;
        }
        current++;
    }

    for (int i = 0; i < total; i++) {
        printf("%d\n", numbers[i]);
    }
    
    return 0;
}