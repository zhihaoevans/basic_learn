/*
 * 主题说明：C 用 struct 模拟面向对象 —— 把函数指针放进 struct 充当“方法”，
 *           派生结构体把“基类”放第一个成员实现继承，不同形状以同一接口调用（多态模拟）。
 * 运行命令：./c/build/bin/oop_struct_polymorphism
 * 预期输出（关键行）：
 *   圆 面积 = 12.57
 *   矩形 面积 = 12.00
 *   总面积 = 24.57 （不同形状同一接口：循环里统一调 shapes[i]->area(shapes[i])）
 */

#include <stdio.h>

typedef struct Shape Shape;

/* “基类”：数据 + 两个函数指针字段（模拟虚函数）。self 指针模拟隐式的 this。 */
struct Shape {
    const char *name;                          /* 类型名 */
    double (*area)(const Shape *self);         /* “方法”：计算面积 */
    void (*describe)(const Shape *self);       /* “方法”：自我描述 */
};

/* “派生类”：把 Shape 放在第一个成员——Shape* 与 Circle* 可以安全互转 */
typedef struct {
    Shape base;        /* 继承的“基类”部分 */
    double radius;     /* 子类自己的字段（封装在构造函数里初始化） */
} Circle;

typedef struct {
    Shape base;
    double width;
    double height;
} Rect;

/* ---- 各形状自己的“方法实现” ---- */

static double circle_area(const Shape *self) {
    const Circle *c = (const Circle *)self;    /* base 是首成员，指针可安全回转 */
    return 3.141592653589793 * c->radius * c->radius;
}

static double rect_area(const Shape *self) {
    const Rect *r = (const Rect *)self;
    return r->width * r->height;
}

/* 通用“方法”：只依赖 Shape 接口，任何形状都能用（多态的收益） */
static void shape_describe(const Shape *self) {
    printf("%s 面积 = %.2f\n", self->name, self->area(self));
}

/* ---- “构造函数”：集中初始化，模拟封装 ---- */

static Circle circle_new(double radius) {
    Circle c;
    c.base.name = "圆";
    c.base.area = circle_area;                 /* 绑定本类型的方法（模拟虚表） */
    c.base.describe = shape_describe;
    c.radius = radius;
    return c;
}

static Rect rect_new(double width, double height) {
    Rect r;
    r.base.name = "矩形";
    r.base.area = rect_area;
    r.base.describe = shape_describe;
    r.width = width;
    r.height = height;
    return r;
}

int main(void) {
    printf("C 面向对象模拟：struct + 函数指针\n");
    printf("==========================================\n\n");

    Circle circle = circle_new(2.0);           /* “构造”圆：半径 2 */
    Rect rect = rect_new(3.0, 4.0);            /* “构造”矩形：3 × 4 */

    /* 不同形状、不同 area 实现，放进同一个 Shape* 数组，以同一接口调用 */
    Shape *shapes[2] = { &circle.base, &rect.base };

    printf("=== 同一接口遍历（多态模拟） ===\n");
    double total = 0.0;
    for (size_t i = 0; i < sizeof(shapes) / sizeof(shapes[0]); i++) {
        shapes[i]->describe(shapes[i]);        /* 统一经接口调用，各走各的实现 */
        total += shapes[i]->area(shapes[i]);
    }
    printf("总面积 = %.2f （不同形状同一接口：循环里统一调 shapes[i]->area(shapes[i])）\n",
           total);

    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    return 0;
}
