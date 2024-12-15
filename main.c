#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_RAND_Z 100
#define MIN_RAND_Z -100


int** full_rand_matrix(int** matrix, int rows, int cols);                        /* Функция заполнения массива случайными числами */
int** full_manual_matrix(int** matrix, int rows, int cols);                      /* Функция заполнения массива вручную */
int** sort_matrix(int** matrix, int* param_matrix, int rows, int cols);         /* Функция сортировки матрицы */
void print_matrix(int** matrix, int rows, int cols);                            /* Функция вывода массива в консоль */
int count_cols_no_nulls(int** matrix, int rows, int cols);                      /* Функция подсчёта количества ненулевых строк */


int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    char text;
    int flag = 1;
    int flag_sort_matrix = 0;
    int number_fill, number, count_cols;
    int rows, cols;
    int **original_matrix;
    int *param_sort_matrix;
    printf("***************************************************************************************\n");
    printf("*              Автор работы: Толстых Николай, группа бИД-241                          *\n");
    printf("*      Тема:   Дана целочисленная прямоугольная матрица.                              *\n");
    printf("*              Определить кол-во столбцов, не содержащих ни одного нулевого элемента  *\n");
    printf("*              Сортировку столбцов выполнить методом расчёски                         *\n");
    printf("*              Характеристикой столбца являются элементы, стоящие по диагонали        *\n");
    printf("***************************************************************************************\n");
 
    while (flag) {
        printf("Введите число строк > ");
        scanf("%d", &rows);
        printf("Введите число столбцов > ");
        getchar();
        scanf("%d", &cols);

        original_matrix = (int**)malloc(rows * sizeof(int*));
        if (original_matrix != NULL) {
            for (int i = 0; i < rows; i++) {
                original_matrix[i] = (int*)malloc(cols * sizeof(int));
            }
            flag = 0;
        }
        else {
            printf("Ошибка! Повторите попытку ввода!\n");
            getchar();
        }
        param_sort_matrix = (int*)malloc(cols * sizeof(int));
    }
    printf("\n***************************************************\n");
    printf("*      Выберите способ заполнения массива:        *\n");
    printf("*         1. Ручное заполнение                    *\n");
    printf("*         2. Заполнение случайными числами        *\n");
    printf("*         3. Завершить работу                     *\n");
    printf("***************************************************\n");
    printf("Введите номер команды > ");
    scanf("%d", &number_fill);

    switch (number_fill) {
    case 1:
            full_manual_matrix(original_matrix, rows, cols);
            break;
    case 2:
            full_rand_matrix(original_matrix, rows, cols);
            break;
    case 3:
            return 0;
    default:
            printf("\nКоманда введена некоректно!\n");
            return 0;
    }
    
    count_cols = count_cols_no_nulls(original_matrix, rows, cols);

    
    while (1) {
        printf("\n***************************************************\n");
        printf("*    Выберите команду:                            *\n");
        if (!flag_sort_matrix) {
            printf("*        1. Вывести исходную матрицу              *\n");
        } else {
            printf("*        1. Вывести сортированную матрицу         *\n");
        }
        printf("*        2. Вывести количество ненулевых слолбцов *\n");
        printf("*        3. Выполнить сортировку                  *\n");
        printf("*        4. Завершить работу                      *\n");
        printf("***************************************************\n");
        printf("Введите номер команды > ");
        scanf("%d", &number);
        printf("\n");

        switch (number) {
        case 1:
                print_matrix(original_matrix, rows, cols);
                break;
        case 2:
                printf("Количество столбцов без нулей - %d\n", count_cols);
                break;
        case 3:
                sort_matrix(original_matrix, param_sort_matrix, rows, cols);
                flag_sort_matrix = 1;
                break;
        case 4:
                return 0;
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
    }
    free(original_matrix);
    free(param_sort_matrix);
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = rand() % (MAX_RAND_Z - MIN_RAND_Z + 1) + MIN_RAND_Z;
        }
    }
    return matrix;
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

// Функция печати двухмерного массива в консоль
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

// Функция сортировки методом расчёски
int** sort_matrix(int** matrix, int* param_matrix, int rows, int cols) {
    float tab = (float)rows / (float)cols;
    int one_index, two_index, temp, temp_param;
    int height = cols - 1;
    float up_row, down_row;
    up_row = 0, down_row = rows - 1;

    for (int j = 0; j < cols; j++) {
        param_matrix[j] = matrix[(int)(up_row)][j] + matrix[(int)(down_row)][j];
        up_row += tab;
        down_row -= tab;
    }

    while (height != 0) {
        for (int j = 0; j < cols - height; j++) {
            one_index = j;
            two_index = j + height;
            if (param_matrix[one_index] > param_matrix[two_index]) {
                temp_param = param_matrix[one_index];
                param_matrix[one_index] = param_matrix[two_index];
                param_matrix[two_index] = temp_param;
                for (int i = 0; i < rows; i++) {
                    temp = matrix[i][one_index];
                    matrix[i][one_index] = matrix[i][two_index];
                    matrix[i][two_index] = temp;
                }
            }
        }
        height -= 1;
    }
    return matrix;
}

