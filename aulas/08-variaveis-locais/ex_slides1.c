long incremento(long *p, long val) {
    long x = *p;
    long y = x + val;
    *p = y;
    return x;
}
long call_incr() {
    long v1 = 351;
    long v2 = incremento(&v1, 100);
    return v1+v2;
}
int main(){
    return call_incr();
}
/* 
incremento:
        movq    (%rdi), %rax
        addq    %rax, %rsi
        movq    %rsi, (%rdi)
        ret
call_incr:
        subq    $16, %rsp
        movq    $351, 8(%rsp)
        movl    $100, %esi
        leaq    8(%rsp), %rdi
        call    incremento
        addq    8(%rsp), %rax
        addq    $16, %rsp
        ret
main:
        movl    $0, %eax
        call    call_incr
        ret */