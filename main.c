//Автор: Толстых Николай
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>




int** create_matrix(int rows, int cols);                                        /* Функция инициализации динамического массива  */
int** full_rand_matrix(int** matrix, int rows, int cols);                        /* Функция заполнения массива случайными числами */
int** full_manual_matrix(int** matrix, int rows, int cols);                      /* Функция заполнения массива вручную */
int** sort_matrix(int** matrix, int rows, int cols);                             /* Функция сортировки массива */
int** copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols);  /* Функция копирования значений из массива в массив */
void print_matrix(int** matrix, int rows, int cols);                            /* Функция вывода массива в консоль */
int count_cols_no_nulls(int** matrix, int rows, int cols);                      /* Функция подсчёта количества ненулевых строк */


int main() {
    setlocale(LC_ALL, "RUS");
    char text;
    int flag = 1;
    int number_fill, number, count_cols;
    int rows, cols;
    int **original_matrix, **new_matrix;
    printf("Автор работы: Толстых Николай, группа бИД-241\n");
    printf("Тема:\t Дана целочисленная прямоугольная матрица.\n");
    printf("\t Определить кол-во столбцов, не содержащих ни одного нулевого элемента.\n");
    printf("\t Характеристика строки сумма её положительных чётных элементов.\n");
    printf("\t Переставляя строки заданной матрицы, расположить их в соответствии с ростом характеристик.\n\n");

    printf("Введите число строк > ");
    scanf("%d", &rows);
    printf("Введите число столбцов > ");
    scanf("%d", &cols);

    original_matrix = create_matrix(rows, cols);
    new_matrix = create_matrix(rows, cols);
    printf("\nВыберите способ заполнения массива:\n");
    printf("1. Ручное заполнение\n");
    printf("2. Заполнение случайными числами\n");
    printf("Введите номер команды > ");
    scanf("%d", &number_fill);

    switch (number_fill) {
    case 1:
            full_manual_matrix(original_matrix, rows, cols);
            break;
    case 2:
            full_rand_matrix(original_matrix, rows, cols);
            break;
    default:
            printf("\nКоманда введена некоректно!\n");
            break;
    }
    
    count_cols = count_cols_no_nulls(original_matrix, rows, cols);

    copy_matrix(original_matrix, new_matrix, rows, cols);
    sort_matrix(new_matrix, rows, cols);
    
    while (1) {
        printf("\nВыберите команду:\n");
        printf("1. Вывести исходную матрицу\n");
        printf("2. Вывести преобразованную матрицу\n");
        printf("3. Вывести количество ненулевых слолбцов\n");
        printf("Введите номер команды > ");
        scanf("%d", &number);
        printf("\n");

        switch (number) {
        case 1:
                print_matrix(original_matrix, rows, cols);
                break;
        case 2:
                print_matrix(new_matrix, rows, cols);
                break;
        case 3:
                printf("Количество столбцов без нулей - %d\n", count_cols);
                break;
        default:
                printf("Номер команды введён некоректно!\n");
                break;
        }
        printf("Продолжить выполнение программы? (Да - y, нет - n)\n");
        getchar();
        if ((text = getchar()) == 'n')
            break;
    }
    for (int i = 0; i < rows; i++) {
        free(original_matrix[i]);
        free(new_matrix[i]);
    }
    free(original_matrix);
    free(new_matrix);
}

// Функция сортировки матрицы 
int** sort_matrix(int** matrix, int rows, int cols) {
    int one_specific, two_specific;
    int one, two;
    int elem_matrix;


    for (int n = 0; n < rows - 1; n++) {
        for (int i = 0; i < rows - 1; i++) {
            one_specific = 0;
            two_specific = 0;
            for (int j_o = 0; j_o < cols; j_o++) {
                elem_matrix = *(*(matrix + i) + j_o);
                if (elem_matrix > 0 && elem_matrix % 2 == 0) {
                    one_specific += elem_matrix;
                }
            }
            for (int j_t = 0; j_t < cols; j_t++) {
                elem_matrix = *(*(matrix + i + 1) + j_t);
                if (elem_matrix > 0 && elem_matrix % 2 == 0) {
                    two_specific += elem_matrix;
                }
            }
            if (one_specific > two_specific) {
                for (int j = 0; j < cols; j++) {
                    one = *(*(matrix + i) + j);
                    two = *(*(matrix + i + 1) + j);
                    *(*(matrix + i) + j) = two;
                    *(*(matrix + i + 1) + j) = one;

                }
            }
        }
    }
    return matrix;
}

// Функция инициализации двухмерного массива
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)malloc(cols * sizeof(int));;
        }
    }
    return matrix;
}

// Функция ручного заполнения массива
int** full_manual_matrix(int** matrix, int rows, int cols) {
    printf("Введите значения ячеек матрицы\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", *(matrix + i) + j);
        }
    }
    return matrix;
}

// Функция заполнения массива значениями
int** full_rand_matrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = rand();
        }
    }
    return matrix;
}

// Функция копирования элементов одной матриццы в другую
int** copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(new_matrix + i) + j) = *(*(original_matrix + i) + j);
        }
    }
    return new_matrix;
}

// Функция определения количества столбцов, не содержащих нулей
int count_cols_no_nulls(int** matrix, int rows, int cols) {
    int count_cols = 0;
    for (int j = 0; j < cols; j++) {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            if (*(*(matrix + i) + j) != 0) {
                count += 1;
            }
        }
        if (count == rows) {
            count_cols += 1;
        }
    }
    return count_cols;
 }

// Функция печали двухмерного массива в консоль
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

