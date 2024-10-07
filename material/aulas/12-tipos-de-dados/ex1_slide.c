// gcc -g ex1_slide.c -o ex1_slide
// valgrind --leak-check=yes ./ex1_slide

#include <stdio.h> // printf
#include <stdlib.h> // malloc

int main(){
    char *str = malloc(3);
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    str[3] = 'd';
    printf("%s",str);
    return 0;
}