#include <stdio.h>
#include <memory.h>

int rec_list(int mod, int n, int p_cnt, int c_cnt, int i_cnt, char arr[], int k){
    int sum = 0;
    if (p_cnt == mod){
        return 0;
    }
    if(!n){
        if(i_cnt == 1){
            return 0;
        } else {
            return 1;
        }
    }
    if(i_cnt != 1){
        //Park
        arr[k] = 'P';
        sum = rec_list(mod, n-1, 0, c_cnt+1, 0, arr, k+1);
        //Industrial
        arr[k] = 'I';
        sum += rec_list(mod, n-1, p_cnt+1, c_cnt+1, i_cnt+1, arr, k+1);
    }

    //Residential
    arr[k] = 'R';
    //sum += rec_list(mod, n-1, p_cnt+1, 0, 0, arr, k+1);
    sum += rec_list(mod, n-1, p_cnt+1, c_cnt+1, 0, arr, k+1);
    //Commercial
    if(c_cnt >= mod && i_cnt != 1){
        arr[k] = 'C';
        sum += rec_list(mod, n-1, p_cnt+1, 0, 0, arr, k+1);
    }

    printf("[%s]\n", arr);

    return sum;
}

int rec_count(int mod, int n, int p_cnt, int c_cnt, int i_cnt){
    int sum = 0;
    if (p_cnt == mod){
        printf("0");
        return 0;
    }
    if(!n){
        if(i_cnt == 1){
            printf("0");
            return 0;
        } else {
            printf("1");
            return 1;
        }
    }
    if( i_cnt != 1){
        //Park
        printf("P");
        sum = rec_count(mod, n-1, 0, c_cnt+1, 0);
        //Industrial
        printf("I");
        sum += rec_count(mod, n-1, p_cnt+1, c_cnt+1, i_cnt+1);
    }
    //Residential
    printf("R");
    sum += rec_count(mod, n-1, p_cnt+1, 0, 0);
    //Commercial
    if(c_cnt >= mod && i_cnt != 1){
        printf("C");
        sum += rec_count(mod, n-1, p_cnt+1, 0, 0);
    }

    return sum;
}

int main() {
    int mod = 0, n = 0, res = 0, k = 0, r = 0;
    char arr[100] = {0};
    char str[7] = {0};

    printf("Modulus:\n");
    if( scanf("%d", &mod)!= 1 || mod < 1 || mod > 10){
        printf("Invalid input.\n");
        return 0;
    }
    printf("Searches:\n");
    while ((r = scanf("%6s %d", str, &n)) != EOF){
        if ((strcmp("list", str) && strcmp("count", str))|| n < 1 || r != 2) {
            printf("Invalid input.\n");
            return 0;
        }
        else if(strcmp("count", str) == 0){
            res = rec_count(mod, n, 0, mod, 0);
            printf("=> %d\n", res);
        }
        else if(strcmp("list", str) == 0){
            res = rec_list(mod, n, 0, mod, 0 , arr, k );
            printf("=> %d\n", res);
        }
    }
    return 0;
}
