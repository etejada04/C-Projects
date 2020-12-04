#include <stdio.h>
#include <math.h>

int main() {
    double ax, ay, bx, by, cx, cy; //Coordinates A, B , C
    double oaX, oaY, obX, obY, ocX, ocY;//Coordinates of opposite A, B, C
    double distA, distB, distC, distAB, distBC, distAC;
    double distAoC, distAoB, distBoA;
    double epsilon = 1e-9;
    const char *shape1 = 0, *shape2 = 0, *shape3 = 0;
    char format[3] ={ '[', ',', ']'};

    printf("Point A:\n");
    if(scanf(" %c %lf %c %lf %c", &format[0], &ax, &format[1], &ay, &format[2]) != 5 || format[0] != '[' || format[1] != ',' || format[2] != ']'){
        printf("Invalid input.\n");
        return 0;
    }
    printf("Point B:\n");
    if(scanf(" %c %lf %c %lf %c", &format[0], &bx, &format[1], &by, &format[2]) != 5 || format[0] != '[' || format[1] != ',' || format[2] != ']'){
        printf("Invalid input.\n");
        return 0;
    }
    printf("Point C:\n");
    if(scanf(" %c %lf %c %lf %c", &format[0], &cx, &format[1], &cy, &format[2]) != 5 || format[0] != '[' || format[1] != ',' || format[2] != ']'){
        printf("Invalid input.\n");
        return 0;
    }

    if( fabs((cx-ax)*(by-ay) - (cy-ay)*(bx-ax)) <= epsilon*((cx-ax)*(cx-ax)+(cy-ay)*(cy-ay)) ){
        printf("Parallelograms do not exist.\n");
        return 0;
    }

    //Get coordinates for A opposite
    oaX = cx + (bx - ax);
    oaY = cy + (by - ay);
    //Get coordinates for B opposite
    obX = ax + (cx - bx);
    obY = ay + (cy - by);
    //Get coordinates for C opposite
    ocX = bx + (ax - cx);
    ocY = by + (ay - cy);
    //Get distance between vectors d = sqrt( (x1-x2)^2 + (y1-y2)^2 )
    distA = sqrt(pow(ax-oaX, 2) + pow(ay-oaY, 2));
    distB = sqrt(pow(bx-obX, 2) + pow(by-obY, 2));
    distC = sqrt(pow(cx-ocX, 2) + pow(cy-ocY, 2));
    distAB = sqrt(pow(ax-bx, 2) + pow(ay-by, 2));
    distAC = sqrt(pow(ax-cx, 2) + pow(ay-cy, 2));
    distBC = sqrt(pow(bx-cx, 2) + pow(by-cy, 2));
    //Get distance with respect to the opposites
    distAoB = sqrt(pow(ax-obX, 2) + pow(ay-obY, 2));
    distAoC = sqrt(pow(ax-ocX, 2) + pow(ay-ocY, 2));
    distBoA = sqrt(pow(bx-oaX, 2) + pow(by-oaY, 2));

    //Shape 1
    if(pow(distA - distBC,2) >= pow(epsilon,3)*distA*distBC){ //Check if diff diagonal
        if(pow(distAB - distBoA,2) < pow(epsilon,3)*distA*distBoA ) //Check if equal sides
            shape1 = "rhombus";
        else
            shape1 = "parallelogram";
    }
    if(pow(distA - distBC,2) < pow(epsilon,3)*distA*distBC){ //Check if equal diagonal
        if(pow(distAB - distBoA,2) < pow(epsilon,3)*distA*distBoA )
            shape1 = "square";
        else
            shape1 = "rectangle";
    }

    //Shape 2
    if(pow(distB - distAC,2) >= pow(epsilon,3)*distB*distAC){
        if(pow(distAB - distAoB,2) < pow(epsilon,3)*distAB*distAoB)
            shape2 = "rhombus";
        else
            shape2 = "parallelogram";
    }
    if(pow(distB - distAC,2) < pow(epsilon,3)*distB*distAC){
        if(pow(distAB - distAoB,2) < pow(epsilon,3)*distAB*distAoB)
            shape2 = "square";
        else
            shape2 = "rectangle";
    }


    //Shape 3
    if(pow(distC - distAB,2) >= pow(epsilon,3)*distC*distAB){
        if(pow(distAC - distAoC,2) < pow(epsilon,3)*distAC*distAoC)
            shape3 = "rhombus";
        else
            shape3 = "parallelogram";
    }
    if(pow(distC - distAB,2) < pow(epsilon,3)*distC*distAB){
        if(pow(distAC - distAoC,2) < pow(epsilon,3)*distAC*distAoC)
            shape3 = "square";
        else
            shape3 = "rectangle";
    }

    printf("A': [%.10g,%.10g], %s\n", oaX, oaY, shape1);
    printf("B': [%.10g,%.10g], %s\n", obX, obY, shape2);
    printf("C': [%.10g,%.10g], %s\n", ocX, ocY, shape3);

    return 0;
}

