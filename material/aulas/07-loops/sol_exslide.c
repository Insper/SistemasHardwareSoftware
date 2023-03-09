/* Argumentos
edi int a
esi int b

Local
eax int i
edx int res*/
int funcao(int a, int b) {
    int i = a;
    int res = 0;
    while (i <= b) {
        res += a;
        i += 1;
    }
    return res;
}
/*
int funcao(int edi, int esi) {
    int eax = edi;
    int edx = 0;
    goto compara;
    faz_algo:
        edx += edi;
        eax += 1;
    
    compara:
    if (eax - esi <= 0) {
        goto faz_algo;
    }
    eax = edx;
    return eax;
}*/