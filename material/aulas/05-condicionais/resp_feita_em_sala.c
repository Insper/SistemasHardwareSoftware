// Registradores
// %edi: int a
//
// Return:
// %eax: int
int ex1(int a) {
    return a > 10;
}

// Registradores
// %rdi: unsigned long a
// %rsi: unsigned long b
//
// Return:
// %eax: int
int ex2(unsigned long a, unsigned long b) {
    return a <= b;
}

// Registradores
// %rdi: long a
// %rsi: long b
// Return:
// %
int ex3(long a, long b) {
    int exp1 = a > b; // foi armazenada no %al
    int exp2 = b > 0; // foi armazenada no %dl
    int res = exp1 && exp2;
    return res;
}

int ex3(long a, long b) {
    return (a > b) && (b > 0); //parenteses opcionais
}