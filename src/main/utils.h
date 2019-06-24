#ifndef STUDY_PRACTICE_UTILS_H
#define STUDY_PRACTICE_UTILS_H

#include <stdio.h>

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int is_latin_lower_case_letter(char c) {
    return (c >= 'a' && c <= 'z');
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

#endif //STUDY_PRACTICE_UTILS_H
