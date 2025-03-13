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

const elem_t POIZON_VALUE   = -666;
const int SIZE_DOT_FILENAME = 50;
const int SIZE_PNG_FILENAME = 50;
const int SIZE_COMMAND      = 100;

enum errors
{
    LIST_SIZE_BELOW_ZERO = 1 << 0,
    LIST_IS_NULL         = 1 << 1,
    LIST_HEAD_IS_NULL    = 1 << 2,
    LIST_TAIL_IS_NULL    = 1 << 3
};

List *list_constructor();
void list_destructor(List* lst);
int insert_before_head(List *lst, List_elem_t** head_node, elem_t value);
int insert_after_tail(List *lst, List_elem_t** tail_node, elem_t value);
List_elem_t* get_head_list(List* lst);
List_elem_t* get_tail_list(List* lst);
List_elem_t* get_next_current_elem(List_elem_t* current_node);
List_elem_t* get_prev_current_elem(List_elem_t* current_node);
List_elem_t* search_by_number(List* lst, size_t number);
List_elem_t* search_by_value(List* lst, elem_t value);
void insert_before_node(List* lst, size_t number, elem_t value);
void insert_after_node(List* lst, size_t number, elem_t value);
void insert_first(List* lst, elem_t value);
List_elem_t* create_node();
void delete_node(List* lst, size_t number);
void list_clear(List* lst);
int graph_dump(List* lst);
int list_verify(List* lst);
void convert_to_binary(int num);
const char* convert_to_str(int err);
void list_errors_output(int list_errors);
void list_assert(List* lst);
