#include <stdio.h>

int testa_scanf() {
    int a,b;

    scanf("%d %d",&a,&b);

    return a+b;

}

int main(){

    int r;
    r = testa_scanf();
    printf("%d",r);
}