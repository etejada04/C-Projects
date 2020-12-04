#include <stdio.h>
#include <string.h>

int dimesion[2000][2000];
int d[2000][2000];

int getDimensions(int * height, int * width)
{
    if ( scanf("%d %d", height, width) != 2 || *height < 1 || *width < 1 || *height > 2000 || *width > 2000)
    {
        return 0;
    }

    return 1;
}

int main() {
    int width = 0, height = 0, investment = 0, res = 0, res2=0;
    char str[7] = {0};

    printf("Map size:\n");
    res2=getDimensions(&width, &height);

    if(res2 == 0){
        printf("Invalid input.\n");
        return 0;
    }

    printf("Price map:\n");
    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            res = scanf(" %d", &dimesion[i][j]);
            if (res != 1){
                printf("Invalid input.\n");
                return 0;
            }
        }
    }

    for (int m = 1; m <= height; ++m) {
        for (int j = 1; j <= width; ++j) {
            d[m][j] = d[m - 1][j] + d[m][j - 1] + dimesion[m][j] - d[m - 1][j - 1];
        }
    }

    printf("Queries:\n");
    while ((scanf("%6s %d", str, &investment)) != EOF) {
        int cnt = 0, sum = 0, area = 0, max = -1;

        if ((strcmp("list", str) && strcmp("count", str)) || investment==0 || investment < 0) {
            printf("Invalid input.\n");
            return 0;
        }

        for (int i = 1; i <= height; ++i) {
            for (int j = 1; j <= width; ++j) {
                for (int k = i; k <= height; ++k) {
                    for (int l = j; l <= width; ++l) {
                        sum = d[k][l] - d[k][j - 1] - d[i - 1][l] + d[i - 1][j - 1];
                        if (sum <= investment) {
                            area = (k - i + 1) * (l - j + 1);
                            if (area > max) {
                                max = area;
                                cnt = 1;
                            } else if (area == max) {
                                cnt++;
                            }
                        }

                    }
                }
            }
        }
                if (cnt == 0) {
                    printf("Not found.\n");
                    continue;
                }
        printf("Max. area: %d (x %d)\n", max, cnt);
        if (strcmp("list", str) == 0) {
            for (int i = 1; i <= height; ++i) {
                for (int j = 1; j <= width; ++j) {
                    for (int k = i; k <= height; ++k) {
                        for (int l = j; l <= width; ++l) {
                            sum = d[k][l] - d[k][j - 1] - d[i - 1][l] + d[i - 1][j - 1];
                            if (sum <= investment) {
                                area = (k - i + 1) * (l - j + 1);
                                if (area == max) {
                                    printf("%d: %d x %d @ (%d,%d)\n", sum, l - j + 1, k - i + 1, j - 1, i - 1);
                                }
                            }

                        }
                    }
                }
            }


        }

    }

    return 0;
}
