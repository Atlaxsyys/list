#pragma once

#include <math.h>

typedef int elem_t;

typedef struct List_elem_t
{
    List_elem_t *next;
    List_elem_t *prev;
    elem_t value;
} List_elem_t;

typedef struct List
{
    List_elem_t *head;
    List_elem_t *tail;
    int size;
} List;

const elem_t POIZON_VALUE = -666;
const int SIZE_DOT_FILENAME = 50;
const int SIZE_PNG_FILENAME = 50;
const int SIZE_COMMAND = 100;

List *list_constructor();
void list_destructor(List* lst);
void insert_before_head(List *lst, elem_t value);
void insert_after_tail(List *lst, elem_t value);
List_elem_t* get_head__list(List* lst);
List_elem_t* get_tail__list(List* lst);
List_elem_t* get_next_current_elem(List_elem_t* current_element);
List_elem_t* get_prev_current_elem(List_elem_t* current_element);
List_elem_t* find_to_number(List* lst, size_t number);
List_elem_t* find_to_value(List* lst, elem_t value);
void insert_before_element(List* lst, size_t number, elem_t value);
void insert_after_element(List* lst, size_t number, elem_t value);
void insert_first(List* lst, elem_t value);
void delete_element(List* lst, size_t number);
void list_clear(List* lst);
void graph_dump(List* lst);
