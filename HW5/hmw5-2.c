#include <stdio.h>
#include <stdlib.h>

long long int gcd( long long int a, long long int b){
    while( b != 0){
        long long int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;

}

long long int lcm ( long long int a, long long int b){
    return a / gcd(a,b) * b;
}

int main() {
    int from = 0, to = 0, res = 0, n = 200, count = 0, r = 0;
    long long int * road = NULL, * tmp = NULL;
    char format;
    road = (long long int *) malloc(n*sizeof(long long int));
    printf("Lanes:\n");

    if( scanf(" %c ", &format) != 1 || format != '{'){
        printf("Invalid input.\n");
        return 0;
    }

    for(int i = 0; i < n; i++){
        r = scanf(" %lld %c", &road[i], &format);
        if( r != 2 || format != ',' || road[i] <= 0 ) {
            if(format == '}'){
                break;
            } else {
                printf("Invalid input.\n");
                free(road);
                return 0;
            }
        }

        road[count] = road[i];
        tmp = road;
        count++;

        if ( count == n-1){
            tmp = (long long int *) realloc(road, 2*n*sizeof(long long int));
            n*=2;
        }

        if(!tmp){
            free(road);
            return 0;
        }
        road = tmp;
    }

    if(road[0] <= 0 || road[count] <= 0){
        printf("Invalid input.\n");
        return 0;
    }

    printf("Routes:\n");
    while( (res = scanf("%d %d", &from, &to) )!= EOF){
        long long int original = 1;
        if( res != 2 || from < 0  || to > count+1 || from >= to){
            printf("Invalid input.\n");
            free(road);
            return 0;
        }

        for(int i = from; i < to; i++){
            original = lcm(road[i], original);
        }

        printf("Vehicles: %lld\n", original);

    }
    free(road);
    return 0;
}
