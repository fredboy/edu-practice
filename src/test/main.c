#define CTEST_MAIN

#include <ctest.h>
#include <lists.h>

CTEST(LISTS, LIST_APPEND) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    list_head = list_append(list_head, 'b');
    ASSERT_EQUAL('a', list_head->value);
    ASSERT_EQUAL('b', list_head->next->value);
}

CTEST(LISTS, LIST_SIZE_0) {
    struct list_entry *list_head = NULL;
    ASSERT_EQUAL(0, list_size(list_head));
}

CTEST(LISTS, LIST_SIZE_1) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    ASSERT_EQUAL(1, list_size(list_head));
}

CTEST(LISTS, LIST_SIZE_2) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    list_head = list_append(list_head, 'b');
    ASSERT_EQUAL(2, list_size(list_head));
}

CTEST(LISTS, LIST_CLEAR) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    list_head = list_clear(list_head);
    ASSERT_EQUAL(0, list_size(list_head));
}

CTEST(LISTS, LIST_RANDOM) {
    struct list_entry *list_head = list_random(5);
    ASSERT_EQUAL(5, list_size(list_head));
}

CTEST(LISTS, LIST_FOREACH) {
    struct list_entry *list_head = list_random(5);
    int sz = 0;
    FOREACH(list_head) sz = iterator.index;
    ASSERT_EQUAL(list_size(list_head) - 1, sz);
}

CTEST(LISTS, LIST_GET_LAST_1) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    ASSERT_EQUAL('a', list_get_last(list_head)->value);
    list_head = list_clear(list_head);
}

CTEST(LISTS, LIST_GET_LAST_2) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    list_head = list_append(list_head, 'b');
    ASSERT_EQUAL('b', list_get_last(list_head)->value);
}

CTEST(LISTS, LIST_GET) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'a');
    list_head = list_append(list_head, 'b');
    list_head = list_append(list_head, 'c');
    list_head = list_append(list_head, 'd');
    ASSERT_EQUAL('b', list_get(list_head, 1));
    ASSERT_EQUAL('d', list_get(list_head, 3));
    ASSERT_EQUAL('a', list_get(list_head, 0));
    ASSERT_EQUAL('c', list_get(list_head, 2));
}

CTEST(LISTS, LIST_SET) {
    struct list_entry *list_head = list_random(10);
    list_set(list_head, 6, 't');
    ASSERT_EQUAL('t', list_get(list_head, 6));
}

CTEST(LISTS, LIST_CONTAINS_VALUE_TRUE) {
    struct list_entry *list_head = list_random(10);
    list_set(list_head, 6, 't');
    ASSERT_EQUAL(1, list_contains_value(list_head, 't'));
}

CTEST(LISTS, LIST_CONTAINS_VALUE_FALSE) {
    struct list_entry *list_head = NULL;
    list_head = list_append(list_head, 'p');
    ASSERT_EQUAL(0, list_contains_value(list_head, 't'));
}

CTEST(LISTS, LIST_FROM_ARRAY) {
    char array[] = {'a', 'b', 'c', 'd', 'e'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(5, list_size(list_head));
    FOREACH(list_head) ASSERT_EQUAL(array[iterator.index], iterator.value);
}

CTEST(LISTS, LIST_IS_ORDERED_NULL) {
    ASSERT_EQUAL(1, list_is_ordered(NULL));
}

CTEST(LISTS, LIST_IS_ORDERED_0) {
    char array[] = {'h', 'e', 'd', 'c', 'v'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(0, list_is_ordered(list_head));
}

CTEST(LISTS, LIST_IS_ORDERED_1) {
    char array[] = {'a', 'd', 'h', 'i', 'p'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(1, list_is_ordered(list_head));
}

CTEST(LISTS, LIST_IS_ORDERED_NEG1) {
    char array[] = {'p', 'i', 'h', 'd', 'a'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(1, list_is_ordered(list_head));
}

CTEST(LISTS, LIST_IS_ORDERED_TRUE) {
    char array[] = {'a', 'd', 'h', 'i', 'p'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(1, list_is_sorted(list_head));
}

CTEST(LISTS, LIST_IS_SORTED_FALSE) {
    char array[] = {'h', 'e', 'd', 'c', 'v'};
    struct list_entry *list_head = list_from_array(array, 5);
    ASSERT_EQUAL(0, list_is_sorted(list_head));
}

CTEST(LISTS, LIST_SORT) {
    struct list_entry *list_head = list_random(10);
    list_head = list_sort(list_head);
    ASSERT_EQUAL(1, list_is_sorted(list_head));
}

CTEST(LISTS, LIST_TO_STRING) {
    struct list_entry *list_head = list_random(10);
    char * list = list_to_string(list_head);
    FOREACH(list_head) ASSERT_EQUAL(iterator.value, list[iterator.index * 3]);
}

CTEST(LISTS, LIST_UNION) {
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'i', 'j', 'k', 'l'};
    struct list_entry *A = NULL;
    A = list_append(A, 'a');
    A = list_append(A, 'b');
    A = list_append(A, 'c');
    A = list_append(A, 'd');
    A = list_append(A, 'e');
    struct list_entry *B = NULL;
    B = list_append(B, 'f');
    B = list_append(B, 'i');
    B = list_append(B, 'j');
    B = list_append(B, 'k');
    B = list_append(B, 'l');
    struct list_entry *C = list_union(A, B);
    ASSERT_EQUAL(10, list_size(C));
    FOREACH(C) {
        ASSERT_EQUAL(chars[iterator.index], iterator.value);
    }
}

CTEST(LISTS, LIST_INTERSECTION) {
    char chars[] = {'a', 'c', 'e'};
    struct list_entry *A = NULL;
    A = list_append(A, 'a');
    A = list_append(A, 'c');
    A = list_append(A, 'e');
    struct list_entry *B = NULL;
    B = list_append(B, 'a');
    B = list_append(B, 'b');
    B = list_append(B, 'c');
    B = list_append(B, 'd');
    B = list_append(B, 'e');
    B = list_append(B, 'f');
    struct list_entry *C = list_intersection(A, B);
    ASSERT_EQUAL(3, list_size(C));
    FOREACH(C) {
        ASSERT_EQUAL(chars[iterator.index], iterator.value);
    }
}

CTEST(LISTS, LIST_DIFF) {
    char chars[] = {'a', 'b'};
    struct list_entry *A = NULL;
    A = list_append(A, 'a');
    A = list_append(A, 'b');
    A = list_append(A, 'c');
    A = list_append(A, 'd');
    struct list_entry *B = NULL;
    B = list_append(B, 'c');
    B = list_append(B, 'd');
    B = list_append(B, 'e');
    B = list_append(B, 'f');
    struct list_entry *C = list_diff(A, B);
    ASSERT_EQUAL(2, list_size(C));
    FOREACH(C) {
        ASSERT_EQUAL(chars[iterator.index], iterator.value);
    }
}

CTEST(LISTS, LIST_SIMDIFF) {
    char chars[] = {'a', 'b', 'e', 'f'};
    struct list_entry *A = NULL;
    A = list_append(A, 'a');
    A = list_append(A, 'b');
    A = list_append(A, 'c');
    A = list_append(A, 'd');
    struct list_entry *B = NULL;
    B = list_append(B, 'c');
    B = list_append(B, 'd');
    B = list_append(B, 'e');
    B = list_append(B, 'f');
    struct list_entry *C = list_simdiff(A, B);
    ASSERT_EQUAL(4, list_size(C));
    FOREACH(C) {
        ASSERT_EQUAL(chars[iterator.index], iterator.value);
    }
}

CTEST(LISTS, LIST_IS_SUBLIST_OF_TRUE) {
    struct list_entry *A = NULL;
    A = list_append(A, 'b');
    A = list_append(A, 'c');
    A = list_append(A, 'd');
    struct list_entry *B = NULL;
    B = list_append(B, 'a');
    B = list_append(B, 'b');
    B = list_append(B, 'c');
    B = list_append(B, 'd');
    B = list_append(B, 'e');
    B = list_append(B, 'f');
    B = list_append(B, 'g');
    ASSERT_EQUAL(1, list_is_sublist_of(A, B));
}

CTEST(LISTS, LIST_IS_SUBLIST_OF_FALSE) {
    struct list_entry *A = NULL;
    A = list_append(A, 'a');
    A = list_append(A, 'b');
    A = list_append(A, 'c');
    A = list_append(A, 'd');
    A = list_append(A, 'h');
    struct list_entry *B = NULL;
    B = list_append(B, 'a');
    B = list_append(B, 'b');
    B = list_append(B, 'c');
    B = list_append(B, 'd');
    B = list_append(B, 'e');
    B = list_append(B, 'f');
    B = list_append(B, 'g');
    ASSERT_EQUAL(0, list_is_sublist_of(A, B));
}

int main(int argc, const char **argv) {
    srand(time(NULL));
    return ctest_main(argc, argv);
}