/*
 * 多维数组示例
 * 演示二维数组、三维数组及其操作
 * C17/C18 标准
 */

#include <stdio.h>
#include <string.h>

// 打印二维数组
void print_2d_array(int rows, int cols, int arr[rows][cols], const char *label) {
    printf("%s:\n", label);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 演示二维数组的基本操作
void demo_2d_array_basics() {
    printf("=== 二维数组基础 ===\n");
    
    // 方式1: 完全初始化
    int matrix1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    print_2d_array(3, 4, matrix1, "完全初始化的矩阵");
    
    // 方式2: 部分初始化
    int matrix2[3][4] = {
        {1, 2},
        {5},
        {9, 10, 11}
    };
    print_2d_array(3, 4, matrix2, "部分初始化的矩阵（其余填0）");
    
    // 方式3: 全零初始化
    int matrix3[3][4] = {0};
    print_2d_array(3, 4, matrix3, "全零矩阵");
    
    // 方式4: 一维初始化方式
    int matrix4[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    print_2d_array(3, 4, matrix4, "一维方式初始化");
    
    // 访问和修改元素
    printf("访问元素: matrix1[1][2] = %d\n", matrix1[1][2]);
    matrix1[1][2] = 99;
    printf("修改后: matrix1[1][2] = %d\n\n", matrix1[1][2]);
}

// 矩阵加法
void matrix_add(int rows, int cols, int a[rows][cols], int b[rows][cols], int result[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

// 矩阵乘法
void matrix_multiply(int rows_a, int cols_a, int a[rows_a][cols_a],
                     int rows_b, int cols_b, int b[rows_b][cols_b],
                     int result[rows_a][cols_b]) {
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_b; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols_a; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// 矩阵转置
void matrix_transpose(int rows, int cols, int matrix[rows][cols], int result[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// 演示矩阵运算
void demo_matrix_operations() {
    printf("=== 矩阵运算演示 ===\n");
    
    // 矩阵加法
    int m1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int m2[2][3] = {{7, 8, 9}, {10, 11, 12}};
    int sum[2][3];
    
    print_2d_array(2, 3, m1, "矩阵A");
    print_2d_array(2, 3, m2, "矩阵B");
    matrix_add(2, 3, m1, m2, sum);
    print_2d_array(2, 3, sum, "A + B");
    
    // 矩阵乘法
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int b[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int product[2][2];
    
    print_2d_array(2, 3, a, "矩阵A (2x3)");
    print_2d_array(3, 2, b, "矩阵B (3x2)");
    matrix_multiply(2, 3, a, 3, 2, b, product);
    print_2d_array(2, 2, product, "A × B (2x2)");
    
    // 矩阵转置
    int original[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int transposed[3][2];
    
    print_2d_array(2, 3, original, "原矩阵");
    matrix_transpose(2, 3, original, transposed);
    print_2d_array(3, 2, transposed, "转置矩阵");
}

// 查找二维数组中的最大值和最小值
void find_max_min_2d(int rows, int cols, int arr[rows][cols], int *max, int *min, int *max_i, int *max_j, int *min_i, int *min_j) {
    *max = arr[0][0];
    *min = arr[0][0];
    *max_i = 0; *max_j = 0;
    *min_i = 0; *min_j = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > *max) {
                *max = arr[i][j];
                *max_i = i;
                *max_j = j;
            }
            if (arr[i][j] < *min) {
                *min = arr[i][j];
                *min_i = i;
                *min_j = j;
            }
        }
    }
}

// 演示二维数组的常见操作
void demo_2d_array_operations() {
    printf("=== 二维数组常见操作 ===\n");
    
    int matrix[3][4] = {
        {15, 23, 8, 42},
        {5, 67, 31, 19},
        {44, 12, 90, 3}
    };
    
    print_2d_array(3, 4, matrix, "测试矩阵");
    
    // 求和
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            sum += matrix[i][j];
        }
    }
    printf("所有元素之和: %d\n", sum);
    
    // 求平均值
    double avg = (double)sum / (3 * 4);
    printf("平均值: %.2f\n", avg);
    
    // 查找最大值和最小值
    int max, min, max_i, max_j, min_i, min_j;
    find_max_min_2d(3, 4, matrix, &max, &min, &max_i, &max_j, &min_i, &min_j);
    printf("最大值: %d 位置[%d][%d]\n", max, max_i, max_j);
    printf("最小值: %d 位置[%d][%d]\n\n", min, min_i, min_j);
    
    // 计算每行的和
    printf("每行的和:\n");
    for (int i = 0; i < 3; i++) {
        int row_sum = 0;
        for (int j = 0; j < 4; j++) {
            row_sum += matrix[i][j];
        }
        printf("  行 %d: %d\n", i, row_sum);
    }
    printf("\n");
    
    // 计算每列的和
    printf("每列的和:\n");
    for (int j = 0; j < 4; j++) {
        int col_sum = 0;
        for (int i = 0; i < 3; i++) {
            col_sum += matrix[i][j];
        }
        printf("  列 %d: %d\n", j, col_sum);
    }
    printf("\n");
}

// 演示三维数组
void demo_3d_array() {
    printf("=== 三维数组演示 ===\n");
    
    // 三维数组: 2个班级，每班3个学生，每人4门课成绩
    int scores[2][3][4] = {
        // 班级0
        {
            {85, 90, 78, 92},  // 学生0
            {88, 76, 95, 89},  // 学生1
            {91, 85, 88, 84}   // 学生2
        },
        // 班级1
        {
            {79, 88, 92, 87},  // 学生0
            {94, 82, 79, 91},  // 学生1
            {86, 90, 84, 88}   // 学生2
        }
    };
    
    printf("三维数组: [班级][学生][课程]\n\n");
    
    // 打印所有成绩
    for (int class_id = 0; class_id < 2; class_id++) {
        printf("班级 %d:\n", class_id);
        for (int student = 0; student < 3; student++) {
            printf("  学生 %d 的成绩: ", student);
            for (int course = 0; course < 4; course++) {
                printf("%d ", scores[class_id][student][course]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // 计算每个学生的平均分
    printf("每个学生的平均分:\n");
    for (int class_id = 0; class_id < 2; class_id++) {
        printf("班级 %d:\n", class_id);
        for (int student = 0; student < 3; student++) {
            int sum = 0;
            for (int course = 0; course < 4; course++) {
                sum += scores[class_id][student][course];
            }
            double avg = (double)sum / 4;
            printf("  学生 %d: %.2f\n", student, avg);
        }
    }
    printf("\n");
    
    // 计算每门课的平均分
    printf("每门课的平均分:\n");
    for (int course = 0; course < 4; course++) {
        int sum = 0;
        int count = 0;
        for (int class_id = 0; class_id < 2; class_id++) {
            for (int student = 0; student < 3; student++) {
                sum += scores[class_id][student][course];
                count++;
            }
        }
        double avg = (double)sum / count;
        printf("  课程 %d: %.2f\n", course, avg);
    }
}

// 演示字符串数组（二维字符数组）
void demo_string_array() {
    printf("\n=== 字符串数组演示 ===\n");
    
    // 方式1: 二维字符数组
    char names[5][20] = {
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve"
    };
    
    printf("学生名单:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
    printf("\n");
    
    // 修改字符串
    strcpy(names[2], "Carol");
    printf("修改后的名单:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
}

int main(void) {
    printf("C语言多维数组示例\n");
    printf("==========================================\n\n");
    
    demo_2d_array_basics();
    demo_matrix_operations();
    demo_2d_array_operations();
    demo_3d_array();
    demo_string_array();
    
    printf("\n==========================================\n");
    printf("示例运行完成！\n");
    
    return 0;
}
