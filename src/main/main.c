#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

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
            printf("Множество должно состоять из маленьких латинских букв!\n");
            list_head = list_read(size);
    } while (!list_is_contains_only_latin_lower_case_letters(list_head));
    return list_sort(list_head);
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

void op_7() {
    struct list_entry *A = ask_list_input('A');
    list_print(list_sort(A));
    printf("\n");
    list_clear(A);
}

void show_menu_elements(int current_choose, char **menu, int menu_size) {
    for (int i = 0; i < menu_size; i++) {
        if (current_choose == i) {
            attron(A_REVERSE);
            printw(">> %s\n", menu[i]);
            attroff(A_REVERSE);
        } else {
            printw(" %s\n", menu[i]);
        }
    }
}

int menu(char *prompt, char **menu_text, int menu_size) {
    int choose = 0;
    curs_set(0);
    while (true) {
        clear();
        printw("%s", prompt);
        show_menu_elements(choose, menu_text, menu_size);
        int character = getch();
        switch (character) {
            case KEY_UP:
                if (choose > 0) {
                    (choose)--;
                }
                break;
            case KEY_DOWN:
                if (choose < menu_size - 1) {
                    (choose)++;
                }
                break;
            case '\n':
                curs_set(1);
                return choose;
            default:
                break;
        }
    }
}

char **get_menu() {
    char **menu = (char **) malloc(6 * sizeof(char *));
    for (int i = 0; i < 6; i++) menu[i] = (char *) malloc(256 * sizeof(char));
    menu[0] = "Объединение      ";
    menu[1] = "Пересечение      ";
    menu[2] = "Разность         ";
    menu[3] = "Сим. Разность    ";
    menu[4] = "Входит или равно ";
    menu[5] = "Выход            ";
    return menu;
}

int main() {
    setlocale(LC_ALL, "");
    char **menu_text = get_menu();
    while (1) {
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        int op = menu("Выберите операцию:\n", menu_text, 6);
        endwin();
        switch (op) {
            case 0:
                op_1();
                break;
            case 1:
                op_2();
                break;
            case 2:
                op_3();
                break;
            case 3:
                op_4();
                break;
            case 4:
                op_5();
                break;
            case 5:
                exit(0);
            default:
                break;
        }
        printf("Нажмите что хотите...\n");
        getch();
    }
}
