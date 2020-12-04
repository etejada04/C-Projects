#include <stdio.h>
#include <math.h>

int main() {
    double ax, ay, bx, by, cx, cy; //Coordinates A, B , C
    double oaX, oaY, obX, obY, ocX, ocY;//Coordinates of opposite A, B, C
    double distA, distB, distC, distAB, distBC, distAC;
    double distAoC, distAoB, distBoA;
    double epsilon = 0.000000001;
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
    //All points are in the same line: (y2 -y1)/(x2-x1) = (y3 -y1)/(x3-x1) -> Problem: division by 0
    if( fabs(((by-ay)/(bx-ax)) - ((cy-ay)/(cx-ax))) < epsilon ){
        printf("Parallelograms do not exist.\n");
        return 0;
    } else if ( fabs(ax-ay) == 0.0 && fabs(bx-by) == 0.0 && fabs(cx-cy) == 0.0){
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
    if(fabs(distA - distBC) > epsilon){ //Check if diff diagonal
        if(fabs(distAB - distBoA) < epsilon) //Check if equal sides
            shape1 = "rhombus";
        else
            shape1 = "parallelogram";
    }
    if(fabs(distA - distBC) < epsilon){ //Check if equal diagonal
        if(fabs(distAB - distBoA) < epsilon)
            shape1 = "square";
        else
            shape1 = "rectangle";
    }

    //Shape 2
    if(fabs(distB - distAC) > epsilon){
        if(fabs(distAB - distAoB) < epsilon)
            shape2 = "rhombus";
        else
            shape2 = "parallelogram";
    }
    if(fabs(distB - distAC) < epsilon){
        if(fabs(distAB - distAoB) < epsilon)
            shape2 = "square";
        else
            shape2 = "rectangle";
    }

    //Shape 3
    if(fabs(distC - distAB) > epsilon){
        if(fabs(distAC - distAoC) < epsilon)
            shape3 = "rhombus";
        else
            shape3 = "parallelogram";
    }
    if(fabs(distC-distAB) < epsilon){
        if(fabs(distAC - distAoC) < epsilon)
            shape3 = "square";
        else
            shape3 = "rectangle";
    }

    printf("A': [%.10g,%.10g], %s\n", oaX, oaY, shape1);
    printf("B': [%.10g,%.10g], %s\n", obX, obY, shape2);
    printf("C': [%.10g,%.10g], %s\n", ocX, ocY, shape3);

    return 0;
}

