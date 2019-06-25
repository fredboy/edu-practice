#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>

#include "lists.h"
#include "utils.h"

//dunno what is the normal way to do this...
#define CLEAR system("clear")
//#define CLEAR system("cls")


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

void print_set(struct list_entry *list_head, char name) {
    printf("%c = {", name);
    list_print(list_head);
    printf("}\n");
}

void mv_print_set(int y, int x, struct list_entry *list_head, char name) {
    mvprintw(y, x, "%c = {%s}", name, list_to_string(list_head));
}

void execute(int op, struct list_entry *A, struct list_entry *B) {
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
	CLEAR;
    print_set(A, 'A');
    print_set(B, 'B');
    if (op != 4) print_set(C, 'C');
    else printf(sublist == 1 ? "A is a subset of B\n" : "A is not a subset of B\n");
    list_clear(C);
}

void draw_frame(int y1, int x1, int y2, int x2, int br_h) {
    mvhline(y1, 0, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvhline(y1 + br_h, x1, 0, x2-x1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
    mvaddch(y1 + br_h, x1, ACS_LTEE);
    mvaddch(y1 + br_h, x2, ACS_RTEE);
}

void show_menu_elements(int current_choose, char **menu, int menu_size) {
    printw("\n");
    for (int i = 0; i < menu_size; i++) {
        if (strcmp(menu[i], ";br") == 0) {
            printw("\n");
        } else if (current_choose == i) {
            attron(COLOR_PAIR(1));
            printw(" >> %s\n", menu[i]);
            attroff(COLOR_PAIR(1));
        } else {
            printw("  %s\n", menu[i]);
        }
    }
    draw_frame(0, 0, 10, 20, 3);
}

int menu(char **menu_text, int menu_size, struct list_entry *A, struct list_entry *B) {
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
        show_menu_elements(choose, menu_text, menu_size);
        mvprintw(0, 8, "Menu");
        mv_print_set(1, 22, A, 'A');
        mv_print_set(2, 22, B, 'B');
        refresh();
        int character = getch();
        switch (character) {
            case KEY_UP:
                choose--;
                if (choose < 0) choose = menu_size - 1;
                if (menu_text[choose][0] == ';') choose--;
                break;
            case KEY_DOWN:
                choose++;
                if (choose >= menu_size) choose = 0;
                if (menu_text[choose][0] == ';') choose++;
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
    char **menu = (char **) malloc(9 * sizeof(char *));
    menu[0] = "Input A          ";
    menu[1] = "Input B          ";
    menu[2] = ";br";
    menu[3] = "Union            ";
    menu[4] = "Intersection     ";
    menu[5] = "Difference       ";
    menu[6] = "Sim. Difference  ";
    menu[7] = "Is a subset      ";
    menu[8] = "Quit             ";
    return menu;
}

int main() {
    CLEAR;
    char **menu_text = get_menu();
    struct list_entry *A = NULL, *B = NULL;
    while (1) {
        int op = menu(menu_text, 9, A, B);
        switch (op) {
            case 0:
                A = ask_list_input('A');
                break;
            case 1:
                B = ask_list_input('B');
                break;
            case 8:
                free(menu_text);
                list_clear(A);
                list_clear(B);
                CLEAR;
                exit(0);
            default:
                execute(op - 3, A, B);
                break;
        }
        printf("Press whatever you want...\n");
        getch();
    }
}
