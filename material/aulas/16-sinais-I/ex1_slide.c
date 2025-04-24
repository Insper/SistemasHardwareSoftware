//gcc ex1_slide.c -o ex1
#include <stdio.h>     

int main() {
	int *px = (int*) 0x01010101;
	*px = 0;
    printf("fim do programa.\n");
    return 0;
}


