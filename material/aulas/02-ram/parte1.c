#include <stdio.h>

struct player {
    char icon_id;
    long level;
    char name[20];
    long score;
};

struct player one = {
    2,
    20,
    "nome nome nome",
    1012312312
};


int main(int argc, char *argv[]) {
    printf("Sizeof(struct player) = %lu\n", sizeof(struct player));
    printf("--------\nname: %s\nlevel: %ld\nicon: %d\nscore: %ld\n", one.name,
            one.level, one.icon_id, one.score);
    printf("---\nEndereços:\nname: %p\nlevel: %p\nicon: %p\nscore: %p\n", &one.name,
            &one.level, &one.icon_id, &one.score);
    printf("----\n&one: %p\n", &one);
    return 0;
}
