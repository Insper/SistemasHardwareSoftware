// para compilar use:
// gcc -Og -c sol_exslide.c -o sol_exslide.o

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
}
    
Dump of assembler code for function funcao:
   0x0000000000001149 <+0>:     endbr64 
   0x000000000000114d <+4>:     mov    %edi,%eax
   0x000000000000114f <+6>:     mov    $0x0,%edx
   0x0000000000001154 <+11>:    jmp    0x115b <funcao+18>
   0x0000000000001156 <+13>:    add    %edi,%edx
   0x0000000000001158 <+15>:    add    $0x1,%eax
   0x000000000000115b <+18>:    cmp    %esi,%eax
   0x000000000000115d <+20>:    jle    0x1156 <funcao+13>
   0x000000000000115f <+22>:    mov    %edx,%eax
   0x0000000000001161 <+24>:    ret    
End of assembler dump.
*/