#include <stdio.h>

int main() {
    int i, n=1000, sum=0;
    for(i=1; i<n; i++){
      sum = sum + i;
    }
    printf("Sum of first 1000 numbers is %d\n",sum);
    return 0;
}
