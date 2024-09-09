int minhafunc(int a, int *b) {
    int res;
    res = a + *b;
    *b = res;
    return res;
}

int main() {
    int res;
    minhafunc(5,&res);
    return res;
}
