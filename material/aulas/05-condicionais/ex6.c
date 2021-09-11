int ex6(long a, long b) {
    long c;
    if (a > b) {
        c = a;
    } else {
        c = b;
    }
    if (a > 0) {
        c = -c;
    }
    return c;
}
