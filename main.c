//Автор: Толстых Николай
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define TEXT_LEN 100 // Максимальная длина вводимой строки


int** create_matrix(int rows, int cols);                                        /* Функция инициализации динамического массива  */
void full_rand_matrix(int** matrix, int rows, int cols);                        /* Функция заполнения массива случайными числами */
void full_manual_matrix(int** matrix, int rows, int cols);                      /* Функция заполнения массива вручную */
void sort_matrix(int** matrix, int rows, int cols);                             /* Функция сортировки массива */
void copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols);  /* Функция копирования значений из массива в массив */
void print_matrix(int** matrix, int rows, int cols);                            /* Функция вывода массива в консоль */
int count_cols_no_nulls(int** matrix, int rows, int cols);                      /* Функция подсчёта количества ненулевых строк */
int open_with_file(int** matrix, int rows, int cols);                           /* Функция чтения массива из файла */
int write_in_file(int** matrix, int** new_matrix, int rows, int cols, int count_cols); /* Функция записи в файл */


int main() {
    setlocale(LC_ALL, "RUS");
    char text;
    int flag = 1;
    int number_fill, number, count_cols;
    int rows, cols;
    int **original_matrix, **new_matrix;
    printf("Введите число строк > ");
    scanf("%d", &rows);
    printf("Введите число столбцов > ");
    scanf("%d", &cols);

    original_matrix = create_matrix(rows, cols);
    new_matrix = create_matrix(rows, cols);
    while (flag) {
        printf("\nВыберите способ заполнения массива:\n");
        printf("1. Ручное заполнение\n");
        printf("2. Заполнение случайными числами\n");
        printf("3. Чтение из файла\n");
        printf("Введите номер команды > ");
        scanf("%d", &number_fill);

        switch (number_fill) {
        case 1:
                full_manual_matrix(original_matrix, rows, cols);
                flag = 0;
                break;
        case 2:
                full_rand_matrix(original_matrix, rows, cols);
                flag = 0;
                break;
        case 3:
                open_with_file(original_matrix, rows, cols);
                flag = 0;
                break;
        default:
                printf("\nНомер команды введён некоректно!\n");
                break;
        }
    }
    
    count_cols = count_cols_no_nulls(original_matrix, rows, cols);

    copy_matrix(original_matrix, new_matrix, rows, cols);
    sort_matrix(new_matrix, rows, cols);
    
    while (1) {
        printf("\nВыберите команду:\n");
        printf("1. Вывести исходную матрицу\n");
        printf("2. Вывести отсортированную матрицу\n");
        printf("3. Вывести количество ненулевых слолбцов\n");
        printf("4. Записать данные массива в файл\n");
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
                printf("Количество ненулевых столбцов - %d\n", count_cols);
                break;
        case 4:
                write_in_file(original_matrix, new_matrix, rows, cols, count_cols);
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
    free(original_matrix);
    free(new_matrix);
}

// Функция сортировки матрицы 
void sort_matrix(int** matrix, int rows, int cols) {
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
}

// Функция инициализации двухмерного массива
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    matrix[0] = (int*)malloc(rows * cols * sizeof(int));
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }
    return matrix;
}

// Функция ручного заполнения массива
void full_manual_matrix(int** matrix, int rows, int cols) {
    printf("Введите значения ячеек матрицы\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", *(matrix + i) + j);
        }
    }
}

// Функция заполнения массива значениями
void full_rand_matrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = rand();
        }
    }
}

// Функция копирования элементов одной матриццы в другую
void copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(new_matrix + i) + j) = *(*(original_matrix + i) + j);
        }
    }
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

// Функция записи массива в файл
int write_in_file(int** original_matrix, int** new_matrix, int rows, int cols, int count_cols) {
    char file_name[TEXT_LEN];
    FILE *output;
    printf("Введите имя файла для записи > ");
    scanf("%s", &file_name);
    if ((output = fopen(file_name, "wt")) == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return 0;
    }
    fprintf(output, "Исходная матрица\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(output, "%d ", *(*(original_matrix + i) + j));
        }
        fprintf(output, "\n");
    }
    fprintf(output, "\nОтсортированная матрица\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(output, "%d ", *(*(new_matrix + i) + j));
        }
        fprintf(output, "\n");
    }
    fprintf(output, "Количество ненулевых столбцов - %d\n", count_cols);
    printf("Данные успешно записаны!\n");
    fclose(output);
}

// Функция чтения массива из файла
int open_with_file(int** matrix, int rows, int cols) {
    FILE* input;
    char file_name[TEXT_LEN];
    int temp;
    printf("Введите название файла > ");
    scanf("%s", &file_name);
    input = fopen(file_name, "rt");
    if (input == NULL) {
        printf("Ошибка чтения файла!\n");
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!feof(input)) {
                fscanf(input, "%d", *(matrix + i) + j);
            } else {
                printf("Ошибка! Чтение не может быть выполнено!\n");
                break;
            }
        }
    }

    printf("Чтение выполнено успешно!\n");
    fclose(input);
    return 1;
}

