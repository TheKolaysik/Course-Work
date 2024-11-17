//�����: ������� �������
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>




int** create_matrix(int rows, int cols);                                        /* ������� ������������� ������������� �������  */
int** full_rand_matrix(int** matrix, int rows, int cols);                        /* ������� ���������� ������� ���������� ������� */
int** full_manual_matrix(int** matrix, int rows, int cols);                      /* ������� ���������� ������� ������� */
int** sort_matrix(int** matrix, int rows, int cols);                             /* ������� ���������� ������� */
int** copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols);  /* ������� ����������� �������� �� ������� � ������ */
void print_matrix(int** matrix, int rows, int cols);                            /* ������� ������ ������� � ������� */
int count_cols_no_nulls(int** matrix, int rows, int cols);                      /* ������� �������� ���������� ��������� ����� */


int main() {
    setlocale(LC_ALL, "RUS");
    char text;
    int flag = 1;
    int number_fill, number, count_cols;
    int rows, cols;
    int **original_matrix, **new_matrix;
    printf("����� ������: ������� �������, ������ ���-241\n");
    printf("����:\t ���� ������������� ������������� �������.\n");
    printf("\t ���������� ���-�� ��������, �� ���������� �� ������ �������� ��������.\n");
    printf("\t �������������� ������ ����� � ������������� ������ ���������.\n");
    printf("\t ����������� ������ �������� �������, ����������� �� � ������������ � ������ �������������.\n\n");

    printf("������� ����� ����� > ");
    scanf("%d", &rows);
    printf("������� ����� �������� > ");
    scanf("%d", &cols);

    original_matrix = create_matrix(rows, cols);
    new_matrix = create_matrix(rows, cols);
    printf("\n�������� ������ ���������� �������:\n");
    printf("1. ������ ����������\n");
    printf("2. ���������� ���������� �������\n");
    printf("������� ����� ������� > ");
    scanf("%d", &number_fill);

    switch (number_fill) {
    case 1:
            full_manual_matrix(original_matrix, rows, cols);
            break;
    case 2:
            full_rand_matrix(original_matrix, rows, cols);
            break;
    default:
            printf("\n������� ������� ����������!\n");
            break;
    }
    
    count_cols = count_cols_no_nulls(original_matrix, rows, cols);

    copy_matrix(original_matrix, new_matrix, rows, cols);
    sort_matrix(new_matrix, rows, cols);
    
    while (1) {
        printf("\n�������� �������:\n");
        printf("1. ������� �������� �������\n");
        printf("2. ������� ��������������� �������\n");
        printf("3. ������� ���������� ��������� ��������\n");
        printf("������� ����� ������� > ");
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
                printf("���������� �������� ��� ����� - %d\n", count_cols);
                break;
        default:
                printf("����� ������� ����� ����������!\n");
                break;
        }
        printf("���������� ���������� ���������? (�� - y, ��� - n)\n");
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

// ������� ���������� ������� 
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

// ������� ������������� ����������� �������
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)malloc(cols * sizeof(int));;
        }
    }
    return matrix;
}

// ������� ������� ���������� �������
int** full_manual_matrix(int** matrix, int rows, int cols) {
    printf("������� �������� ����� �������\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", *(matrix + i) + j);
        }
    }
    return matrix;
}

// ������� ���������� ������� ����������
int** full_rand_matrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = rand();
        }
    }
    return matrix;
}

// ������� ����������� ��������� ����� �������� � ������
int** copy_matrix(int** original_matrix, int** new_matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(new_matrix + i) + j) = *(*(original_matrix + i) + j);
        }
    }
    return new_matrix;
}

// ������� ����������� ���������� ��������, �� ���������� �����
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

// ������� ������ ����������� ������� � �������
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

