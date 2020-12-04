#include <stdio.h>
#define MAXDIM 10000000

long int gcd(long int a, long int b){
    while( b != 0){
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;

}

long int lcm (long int a, long int b){
    return a / gcd(a,b) * b;
}

int main() {
    long int flag = 0, i=0, tile_int[i], joint_int[i], width_int = 0, length_int = 0;
    double width, length, tile[10] = {0.0}, joint[10] = {0.0};
    double fwidth = 0.0, flength = 0.0;

    printf("Minimum dimensions:\n");
    if(scanf("%lf %lf", &width, &length) != 2 || width >= MAXDIM || length >= MAXDIM || width <= 0.0 || length <= 0.0){
        printf("Invalid input.\n");
        return 0;
    }

    printf("Tiles:\n");

   while( (flag = scanf("%lf %lf", &tile[i], &joint[i])) == 2){
       if( /*flag != 2 || */tile[i] <= 0.0 || tile[i] >= MAXDIM || joint[i] < 0.0 || joint[i] >= MAXDIM){
           //printf("Invalid input.\n");
           break;
       }
       i++;
    }
    for (long int k = 0; k < i ; ++k) {
        tile_int[k] = tile[k] * 10;
        joint_int[k] = joint[k] * 10;
        //Put outside
        width_int = width * 10;
        length_int = length * 10;

    }

    if(i == 0){
        printf("Invalid input.\n");
        return 0;
    }

    long int LCM = 0, LCM2 = 0, k = 0, div1 = 0, div2 = 0;
    LCM = lcm(tile_int[k] + joint_int[k], tile_int[k+1] + joint_int[k]);
    LCM2 = lcm(LCM, tile_int[k+2] + joint_int[k+2]);


    div1 = width_int / LCM;
    div2 = length_int / LCM;

    if(LCM < width_int || LCM < length_int){
        if(i==1){
            fwidth = tile_int[k];
            flength = joint_int[k];
        } else if(i==2){
            fwidth = ( (div1+1) * LCM) / 10;
            flength = ( (div2+1) * LCM) / 10;
        } else if (i==3){
            fwidth = LCM2/10;
            flength = LCM2/10;
        }

    }

    if(flag == EOF /*&& fwidth >= width && flength >= length*/)
        printf("Dimensions: %.1f x %.1f\n", fwidth, flength);
    else
        printf("Invalid input.\n");
    return 0;


}

