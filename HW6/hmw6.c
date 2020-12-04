#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    int size = 200, flag = 0, cnt1 = 0, res = 0, cnt2 = 0, exit = 0, line = 0, cmp = 0, i = 0, j = 0, i_copy = 0, found = 0;
    char * text, * search, * tmp1, * tmp2;
    char c;
    text = (char*)malloc(size*sizeof(char));
    search = (char*)malloc(size*sizeof(char));

    printf("Text:\n");
    while(flag < 2){
        res = scanf("%c", &c);
        if(res != 1 || c == EOF){
            printf("Invalid input.\n");
            free(text);
            free(search);
            return 0;
        }
        if(c == '\n'){
            flag++;
        }else{
            flag = 0;
            if(!isalpha(c)){
                c=' ';
            }
        }
        c = tolower(c);
        text[cnt1] = c;
        tmp1 = text;
        cnt1++;
        if(cnt1 == size-1){
            tmp1 = (char *)realloc(text, 2*size*sizeof(char));
            size*=2;
        }
        if(!tmp1){
            free(text);
            free(search);
            return 0;
        }
        text = tmp1;

    }

    flag = 0;
    printf("Searches:\n");
    while(flag == 0){
        cnt2 = exit = line = 0;
        while(exit == 0){
            res = scanf("%c", &c);
            if(c == '\n' || res==EOF){
                exit = 1;
                if(cnt2 == 0 && res != EOF){
                    printf("Invalid query\n");
                }
            } else {
                if(!isalpha(c)){
                    c=' ';
                }
            }
            c = tolower(c);
            search[cnt2] = c;
            tmp2 = search;
            cnt2++;
            if(cnt2 == size-1){
                tmp2 = (char *)realloc(search,2*size*sizeof(char));
                size*=2;
            }

            if(!tmp2){
                free(text);
                free(search);
                return 0;
            }
            search = tmp2;
        }
        i = found = 0;
        while(i < cnt1 && search[0] != '\n'){
            if(text[i]== '\n'){
                line++;
            }
            if (text[i] == search[0] && (i == 0? 1:(text[i-1]==' ' || text[i-1]=='\n'))){
                i_copy = i, j = 0, cmp = 0;
                while(cmp == 0){
                    if (text[i_copy] != search[j] && (text[i] != '\n' && search[j] != ' ')){
                        cmp = 1;
                    } else {
                        if(j >= cnt2-2 && (text[i_copy+1] == ' ' || text[i_copy+1] == '\n'|| i_copy == cnt1 )){
                            cmp = 1;
                            found++;
                            if(found == 1){
                                printf("Found: %d", line + 1);
                            } else {
                                printf(", %d", line + 1);
                            }
                        }

                    }
                    if(text[i_copy] == ' '|| text[i_copy] == '\n'){
                        while(text[i_copy] == ' '|| text[i_copy] == '\n'){
                            i_copy++;
                        }
                    } else {
                        i_copy++;
                    }
                    if(search[j] == ' '){
                        while(search[j] == ' '){
                            j++;
                        }
                    } else {
                        j++;
                    }


                }

            }
            i++;

        }

        if(found == 0 && search[0] != '\n'){
            printf("Not found\n");
        }else if(search[0]!='\n'){
            printf("\n");
        }

        if(res==EOF){
            flag = 1;
        }

    }

    free(text);
    free(search);
    return 0;
}
