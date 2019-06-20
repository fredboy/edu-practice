#include <stdio.h>

#include "lists.h"
#include "utils.h"

struct list_entry *ask_list_input(char name) {
    system("clear");
    int size = -1;
    while (size < 0) {
        printf("Введите мощность множества %c: ", name);
        size = scan_int();
    }
    struct list_entry *list_head = NULL;
    printf("Введите элементы множества %c челез пробел.\n", name);
    if (size > 0) do {
            printf("Множество должно быть упорядоченным и состоять из маленьких латинских букв!\n");
            list_head = list_read(size);
    } while (!list_is_ordered(list_head) || !list_is_contains_only_latin_lower_case_letters(list_head));
    return list_head;
}

int choose_op() {
    system("clear");
    printf("Выберите операцию:\n"
           " 1) - объединение\n"
           " 2) - пересечение\n"
           " 3) - разность\n"
           " 4) - сим. разность\n"
           " 5) - входит или равно\n"
           " 6) - все подмножества\n\n"
           " 0 / Ctrl+C - выход\n");
    return mygetch() - '0';
}

void print_sublists(struct list_entry *list_head) {
    struct list_entry **list_array = list_get_sublists(list_head);
    int n = list_size(list_head);
    n = (int) pow(2, n);
    for (int i = 0; i < n; i++) {
        printf("%d. {", i + 1);
        list_print(list_array[i]);
        printf("}\n");
    }
}

void printABC(struct list_entry *A, struct list_entry *B, struct list_entry *C) {
    system("clear");
    printf("A = {");
    list_print(A);
    printf("}\n");
    printf("B = {");
    list_print(B);
    printf("}\n");
    printf("C = {");
    list_print(C);
    printf("}\n");
}

void op_1() {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    struct list_entry *C = list_union(A, B);
    printABC(A, B, C);
    list_clear(A);
    list_clear(B);
    list_clear(C);
}

void op_2() {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    struct list_entry *C = list_intersection(A, B);
    printABC(A, B, C);
    list_clear(A);
    list_clear(B);
    list_clear(C);
}

void op_3() {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    struct list_entry *C = list_diff(A, B);
    printABC(A, B, C);
    list_clear(A);
    list_clear(B);
    list_clear(C);
}

void op_4() {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    struct list_entry *C = list_simdiff(A, B);
    printABC(A, B, C);
    list_clear(A);
    list_clear(B);
    list_clear(C);
}

void op_5() {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    int occurs = list_occurs_in_list(A, B);
    printABC(A, B, NULL);
    printf(occurs == 1 ? "A входит или равно B\n" : "A не входит и не равно B\n");
    list_clear(A);
    list_clear(B);
}

void op_6() {
    struct list_entry *A = ask_list_input('A');
    print_sublists(A);
    list_clear(A);
}

int main() {
    while (1) {
        int op;
        do op = choose_op(); while(op < 0 || op > 6);
        switch (op) {
            case 1:
                op_1();
                break;
            case 2:
                op_2();
                break;
            case 3:
                op_3();
                break;
            case 4:
                op_4();
                break;
            case 5:
                op_5();
                break;
            case 6:
                op_6();
                break;
            case 0:
                exit(0);
            default:
                break;
        }
        printf("Нажмите что хотите...\n");
        mygetch();
        mygetch();
    }
}