#ifndef STUDY_PRACTICE_UTILS_H
#define STUDY_PRACTICE_UTILS_H

#include <stdio.h>
#include <termios.h>
#include <zconf.h>
#include <termio.h>

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int is_latin_lower_case_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

int scan_digit() {
    char input = 0;
    scanf("%c", &input);
    if (is_digit(input)) return input - '0'; else return -1;
}

int scan_int() {
    char *input = (char *) malloc(256 * sizeof(char));
    scanf("%s", input);
    for (int i = 0; input[i] != '\0'; i++) if (!is_digit(input[i])) return -1;
    int result = (int) strtol(input, (char **)NULL, 10);
    free(input);
    return result;
}

int scan_char() {
    char *input = (char *) malloc(256 * sizeof(char));
    scanf("%s", input);
    char result = input[0];
    free(input);
    return result;
}

int mygetch(){
    int ch;
    struct termios oldt, newt;
    tcgetattr ( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

#endif //STUDY_PRACTICE_UTILS_H
