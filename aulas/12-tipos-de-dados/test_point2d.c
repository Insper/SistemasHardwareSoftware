#include "mintest/macros.h"
#include "point2d.h"

int test_new_destroy_get() {
    Point2D *p = point2D_new(0, 0);

    test_assert(point2D_get_x(p) == 0, "Erro na inicialização da componente x!");
    test_assert(point2D_get_y(p) == 0, "Erro na inicialização da componente y!");

    point2D_destroy(p);

    Point2D *p2 = point2D_new(10, 20);

    test_assert(point2D_get_x(p2) == 10, "Erro na inicialização da componente x!");
    test_assert(point2D_get_y(p2) == 20, "Erro na inicialização da componente y!");

    point2D_destroy(p2);

    return 0;
}

int test_add() {
    Point2D *a, *b, *c;
    a = point2D_new(10.5, 20);
    b = point2D_new(30, 40.3);
    c = point2D_add(a, b);

    test_assert(point2D_get_x(c) == 40.5, "Erro na soma: componente x!");
    test_assert(point2D_get_y(c) == 60.3, "Erro na soma: componente x!");

    point2D_destroy(a);
    point2D_destroy(b);
    point2D_destroy(c);

    return 0;
}

int test_scale() {
    Point2D *a, *b, *c;
    a = point2D_new(10.5, 20);
    b = point2D_scale(a, 2.5);

    test_assert(point2D_get_x(b) == 26.25, "Erro na escala: componente x!");
    test_assert(point2D_get_y(b) == 50, "Erro na escala: componente y!");

    c = point2D_scale(a, 0);

    test_assert(point2D_get_x(c) == 0, "Erro na escala: componente x!");
    test_assert(point2D_get_y(c) == 0, "Erro na escala: componente y!");

    point2D_destroy(a);
    point2D_destroy(b);
    point2D_destroy(c);

    return 0;
}

int test_theta() {
    Point2D *a, *b;
    a = point2D_new(20, 30);
    b = point2D_new(40, 50);

    test_assert(point2D_theta(a, b) == 1, "Erro na inclinação da reta!");

    point2D_destroy(a);
    point2D_destroy(b);

    a = point2D_new(20, 30);
    b = point2D_new(40, 40);

    test_assert(point2D_theta(a, b) == 0.5, "Erro na inclinação da reta!");

    point2D_destroy(a);
    point2D_destroy(b);

    return 0;
}

test_list = { TEST(test_new_destroy_get), TEST(test_add), TEST(test_scale), TEST(test_theta) };

#include "mintest/runner.h"
