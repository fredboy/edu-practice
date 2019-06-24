#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "lists.h"
#include "utils.h"

//dunno what is the normal way to do this...
//#define CLEAR system("clear")
#define CLEAR system("cls")


struct list_entry *ask_list_input(char name) {
    CLEAR;
    int size = -1;
    while (size < 0) {
        printf("Input the size of %c: ", name);
        size = scan_int();
    }
    struct list_entry *list_head = NULL;
    printf("Input elements of %c separated by a space or newline.\n", name);
    if (size > 0) do {
            printf("Your set should contain lower case latin letters only.\n");
            list_head = list_read(size);
    } while (!list_is_contains_only_latin_lower_case_letters(list_head));
    return list_sort(list_head);
}

void printABC(struct list_entry *A, struct list_entry *B, struct list_entry *C) {
    CLEAR;
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

void execute(int op) {
    struct list_entry *A = ask_list_input('A');
    struct list_entry *B = ask_list_input('B');
    struct list_entry *C = NULL;
    int sublist = 0;

    switch(op) {
        case 0:
            C = list_union(A, B);
            break;
        case 1:
            C = list_intersection(A, B);
            break;
        case 2:
            C = list_diff(A, B);
            break;
        case 3:
            C = list_simdiff(A, B);
            break;
        case 4:
            sublist = list_is_sublist_of(A, B);
            break;
        default:
            break;
    }

    printABC(A, B, C);
    if (op == 4) printf(sublist == 1 ? "A is a subset of B\n" : "A is not a subset of B\n");
    list_clear(A);
    list_clear(B);
    list_clear(C);
}

void show_menu_elements(int current_choose, char **menu, int menu_size) {
    for (int i = 0; i < menu_size; i++) {
        if (current_choose == i) {
            attron(COLOR_PAIR(1));
            printw(">> %s\n", menu[i]);
            attroff(COLOR_PAIR(1));
        } else {
            printw(" %s\n", menu[i]);
        }
    }
}

int menu(char *prompt, char **menu_text, int menu_size) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    use_default_colors();
    start_color();
    init_pair(1, -1, COLOR_BLUE);
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
                endwin();
                return choose;
            default:
                break;
        }
    }
}

char **get_menu() {
    char **menu = (char **) malloc(6 * sizeof(char *));
    for (int i = 0; i < 6; i++) menu[i] = (char *) malloc(256 * sizeof(char));
    menu[0] = "Union                       ";
    menu[1] = "Intersection                ";
    menu[2] = "Difference                  ";
    menu[3] = "Sim. Difference             ";
    menu[4] = "Is a subset                 ";
    menu[5] = "Quit                        ";
    return menu;
}

int main() {
    CLEAR;
    char **menu_text = get_menu();
    while (1) {
        int op = menu("Select an operation to perform:\n\n", menu_text, 6);
        if (op < 5) execute(op); else {
            free(menu_text);
            exit(0);
        }
        printf("Press whatever you want...\n");
        getch();
    }
}
