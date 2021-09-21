void func2(int *a) {
    *a += 1;
}

int func1() {
    int a = 10;
    int b = 11;
    func2(&a);
    b++;
    func2(&b);
}
