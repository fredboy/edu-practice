#ifndef STUDY_PRACTICE_LISTS_H
#define STUDY_PRACTICE_LISTS_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "utils.h"

#define FOREACH(list_head) \
    for (list_iterator iterator = {list_head, list_head ? list_head->value : 0,  0}; \
    iterator.entry != NULL; \
    iterator.entry = iterator.entry->next,  \
    iterator.value = iterator.entry ? iterator.entry->value : 0, \
    iterator.index++)

struct list_entry {
    char value;
    struct list_entry *next;
};

typedef struct {
    struct list_entry *entry;
    char value;
    int index;
} list_iterator;

struct list_entry *list_get_last(struct list_entry *list_head) {
    struct list_entry *iterator = list_head;
    while (iterator->next != NULL) iterator = iterator->next;
    return iterator;
}

int list_size(struct list_entry *list_head) {
    struct list_entry *iterator = list_head;
    int index = 0;
    while (iterator != NULL) {
        iterator = iterator->next;
        index++;
    }
    return index;
}

struct list_entry *list_append(struct list_entry *list_head, char value) {
    if (list_head == NULL) {
        list_head = (struct list_entry *) malloc(sizeof(struct list_entry));
        list_head->value = value;
        list_head->next = NULL;
        return list_head;
    } else {
        struct list_entry *last = list_get_last(list_head);
        last->next = (struct list_entry *) malloc(sizeof(struct list_entry));
        last = last->next;
        last->value = value;
        last->next = NULL;
        return list_head;
    }
}

char list_get(struct list_entry *list_head, int index) {
    FOREACH(list_head) {
        if (iterator.index == index) return iterator.value;
    }
    return 0;
}

void list_set(struct list_entry *list_head, int index, char value) {
    FOREACH(list_head) {
        if (iterator.index == index) iterator.entry->value = value;
    }
}

int list_contains_value(struct list_entry *list_head, char value) {
    FOREACH(list_head) if (iterator.value == value) return 1;
    return 0;
}

struct list_entry *list_random(int size) {
    struct list_entry *list_head = NULL;
    for (int i = 0; i < size; i++) {
        list_head = list_append(list_head, rand() % 26 + 'a');
    }
    return list_head;
}

struct list_entry *list_clear(struct list_entry *list_head) {
    struct list_entry *iterator = list_head;
    while (iterator != NULL) {
        struct list_entry *next = iterator->next;
        free(iterator);
        iterator = next;
    }
    return NULL;
}

void list_print(struct list_entry *list_head) {
    int size = list_size(list_head);
    FOREACH(list_head) printf(iterator.index == size - 1 ? "%c" : "%c, ", iterator.value);
}

struct list_entry *list_read(int size) {
    struct list_entry *list_head = NULL;
    for (int i = 0; i < size; i++) {
        char value = scan_char();
        list_head = list_append(list_head, value);
    }
    return list_head;
}

int list_compare_values(struct list_entry *a, struct list_entry *b) {
    if (a->value > b->value) return 1;
    else if (a->value < b->value) return -1;
    else return 0;
}

int list_is_ordered(struct list_entry *list_head) {
    int order = 0;
    if (list_size(list_head) <= 1) return 1;
    FOREACH(list_head) {
        if (iterator.index == 1) {
            order = list_compare_values(iterator.entry, list_head);
        } else if (iterator.index > 1) {
            if (list_compare_values(iterator.entry, list_head) != order) return 0;
        }
    }
    return 1;
}

struct list_entry *list_from_array(char array[], int size) {
    struct list_entry *list_head = NULL;
    for (int i = 0; i < size; i++) {
        list_head = list_append(list_head, array[i]);
    }
    return list_head;
}

int list_is_contains_only_latin_lower_case_letters(struct list_entry *list_head) {
    FOREACH(list_head) if (!is_latin_lower_case_letter(iterator.value)) return 0;
    return 1;
}

struct list_entry *list_union(struct list_entry *A, struct list_entry *B) {
    struct list_entry *C = NULL;
    while (A != NULL || B != NULL) {
        if (B == NULL || (A != NULL && A->value <= B->value)) {
            if (!list_contains_value(C, A->value)) C = list_append(C, A->value);
            A = A->next;
        } else if (A == NULL || (B->value <= A->value)) {
            if (!list_contains_value(C, B->value)) C = list_append(C, B->value);
            B = B->next;
        }
    }
    return C;
}

struct list_entry *list_intersection(struct list_entry *A, struct list_entry *B) {
    struct list_entry *C = NULL;
    FOREACH(A) {
        if (!list_contains_value(C, iterator.value) && list_contains_value(B, iterator.value))
            C = list_append(C, iterator.value);
    }
    return C;
}

struct list_entry *list_diff(struct list_entry *A, struct list_entry *B) {
    struct list_entry *C = NULL;
    FOREACH(A) {
        if (!list_contains_value(C, iterator.value) && !list_contains_value(B, iterator.value))
            C = list_append(C, iterator.value);
    }
    return C;
}

struct list_entry *list_simdiff(struct list_entry *A, struct list_entry *B) {
    return (list_union(list_diff(A, B), list_diff(B, A)));
}

int list_occurs_in_list(struct list_entry *A, struct list_entry *B) {
    FOREACH(A) {
        if (!list_contains_value(B, iterator.value)) return 0;
    }
    return 1;
}

struct list_entry **list_get_sublists(struct list_entry *list_head) {
    int size = list_size(list_head);
    int n = (int) pow(2, size);
    struct list_entry **list_array = (struct list_entry **) malloc(n * sizeof(struct list_entry *));
    for (int i = 0; i < n; i++) {
        FOREACH(list_head) if (i & (1 << iterator.index)) list_array[i] = list_append(list_array[i], iterator.value);
    }
    return list_array;
}

#endif //STUDY_PRACTICE_LISTS_H
