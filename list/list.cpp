#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "list.h"
#include <colour.h>

List* list_constructor()
{
    List* lst = (List*) calloc(1, sizeof(List));

    lst->head = nullptr;
    lst->tail = nullptr;
    lst->size = 0;

    list_assert(lst);

    return lst;
}

void list_destructor(List* lst)
{
    list_assert(lst);

    list_clear(lst);
    free(lst);

    lst = nullptr;
}

int insert_before_head(List* lst, List_elem_t** head_node, elem_t value)   //               +-------+    next   +-------+        +-------+         
{                                                                          //               |       |   ----->  |       |        |       |                      
    list_assert(lst);                                                      //       <----   | value |   <-----  |       |   .... |       |             
                                                                           // prev = null   +-------+    prev   +-------+        +-------+                      
    if ((*head_node) == nullptr)                                           //               ^curr_node            ^head            ^tail
    {
        insert_first(lst, value);

        return 0;
    }
    
    List_elem_t* new_node = create_node();

    new_node->value = value;
    new_node->prev = nullptr;

    new_node->next = (*head_node);
    (*head_node)->prev = new_node;
    (*head_node) = new_node;

    lst->size++;
    list_assert(lst);

    return 0;
}

int insert_after_tail(List* lst, List_elem_t** tail_node, elem_t value)     //    +-------+       +-------+   next    +-------+  next = null                                                     
{                                                                           //    |       |       |       |  ----->   |       | ----->                                      
    list_assert(lst);                                                       //    |       |  .... |       |  <-----   | value |                                               
                                                                            //    +-------+       +-------+   prev    +-------+                                                      
    if ((*tail_node) == nullptr)                                               //     ^head            ^tail             ^curr_node
    {
        insert_first(lst, value);

        return 0;
    }

    List_elem_t* new_node = create_node();

    new_node->next = nullptr;
    new_node->value = value;
    new_node->prev = (*tail_node);

    (*tail_node)->next = new_node;
    (*tail_node) = new_node;

    lst->size++;

    return 0;
}

List_elem_t* get_head_list(List* lst)
{
    list_assert(lst);

    return lst->head;
}

List_elem_t* get_tail_list(List* lst)
{
    list_assert(lst);

    return lst->tail;
}

List_elem_t* get_next_current_elem(List_elem_t* current_node)
{
    assert(current_node);

    return current_node->next;
}

List_elem_t* get_prev_current_elem(List_elem_t* current_node)
{
    assert(current_node);

    return current_node->prev;
}

List_elem_t* search_by_number(List* lst, size_t number)
{
    list_assert(lst);

    List_elem_t* current_node = get_head_list(lst);

    for (size_t i = 0; i < number; i++)
    {
        current_node = get_next_current_elem(current_node);
    }

    return current_node;
}

List_elem_t* search_by_value(List* lst, elem_t value)
{
    list_assert(lst);

    List_elem_t* current_node = get_head_list(lst);

    for(int i = 0; i < lst->size; i++)
    {
        if (current_node->value == value)
        {
            return current_node;
        }

        current_node = get_next_current_elem(current_node);
    }

    return nullptr;
}

void insert_before_node(List* lst, size_t number, elem_t value)
{
    list_assert(lst);

    List_elem_t* current_node = search_by_number(lst, number);

    List_elem_t* new_node = create_node();

    new_node->prev = current_node->prev;
    new_node->next = current_node;
    new_node->value = value;

    get_prev_current_elem(current_node)->next = new_node;
    current_node->prev = new_node;

    lst->size++;
}

void insert_after_node(List* lst, size_t number, elem_t value)
{
    list_assert(lst);

    List_elem_t* current_node = search_by_number(lst, number);

    List_elem_t* new_node = create_node();

    new_node->next = current_node->next;
    new_node->prev = current_node;
    new_node->value = value;
    get_next_current_elem(current_node)->prev = new_node;
    current_node->next = new_node;

    lst->size++;
}

void insert_first(List* lst, elem_t value)
{
    assert(lst);

    List_elem_t* new_node = create_node();

    new_node->value = value;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    lst->head = new_node;
    lst->tail = new_node;
    lst->size = 1;
}

List_elem_t* create_node()
{
    List_elem_t* new_node = (List_elem_t*) calloc(1, sizeof(List_elem_t));

    return new_node ? new_node : nullptr;
}

void delete_node(List* lst, size_t number)
{
    list_assert(lst);

    List_elem_t* current_node = search_by_number(lst, number);

    if (lst->size == 1)
    {
        lst->head = nullptr;
        lst->tail = nullptr;
    }

    else if (current_node == lst->head)
    {
        lst->head = get_next_current_elem(current_node);
        get_next_current_elem(current_node)->prev = nullptr;
    }

    else if (current_node == lst->tail)
    {
        lst->tail = get_prev_current_elem(current_node);
        get_prev_current_elem(current_node)->next = nullptr;
    }

    else
    {
        get_prev_current_elem(current_node)->next = get_next_current_elem(current_node);
        get_next_current_elem(current_node)->prev = get_prev_current_elem(current_node);
    }

    current_node->value = POIZON_VALUE;
    current_node->next = nullptr;
    current_node->prev = nullptr;

    free(current_node);
    lst->size--;
}

void list_clear(List* lst)
{
    list_assert(lst);

    List_elem_t* current_node = get_head_list(lst);
    List_elem_t* next_node = nullptr;

    for (int i = 0; i < lst->size; i++)
    {
        next_node = get_next_current_elem(current_node);

        current_node->next = nullptr;
        current_node->prev = nullptr;
        current_node->value = POIZON_VALUE;

        free(current_node);

        current_node = next_node;
    }

    lst->size = 0;
    lst->head = nullptr;
    lst->tail = nullptr;
}

int graph_dump(List* lst)
{
    list_assert(lst);

    static int file_counter = 0;

    char* dot_filename = (char*) calloc(SIZE_DOT_FILENAME, sizeof(char));
    char* png_filename = (char*) calloc(SIZE_PNG_FILENAME, sizeof(char));
    char* command      = (char*) calloc(SIZE_COMMAND, sizeof(char));

    sprintf(dot_filename, "../tests/graph_%d.dot", file_counter);
    sprintf(png_filename, "../tests/graph_%d.png", file_counter);

    FILE* file = fopen(dot_filename, "w");

    if (!file)
    {
        perror("Error open file: ");

        return 0;
    }

    fprintf(file, "digraph G {\n");
    fprintf(file, "    rankdir = LR;\n");
    fprintf(file, "    bgcolor=\"#C0C0C0\";\n\n");

    List_elem_t* current_node = lst->head;
    int index = 0;

    while (current_node)
    {
        fprintf(file, "    node%03d [shape=Mrecord; style=filled; fillcolor=\"blue:white\"; label=\"{index: %d} | { value: %d } | {next: %d} | {prev: %d} \"];\n",
                index, index, current_node->value,
                (current_node->next ? index + 1 : -1),
                (current_node->prev ? index - 1 : -1));

        current_node = current_node->next;
        index++;
    }

    fprintf(file, "\n");

    current_node = lst->head;
    index = 0;

    while (current_node && current_node->next)
    {
        fprintf(file, "    node%03d -> node%03d [style=bold; weight=1000; color=red; ];\n",
                                index, index + 1);

        current_node = current_node->next;
        index++;
    }

    if (lst->tail)
    {
        fprintf(file, "    tail [shape=ellipse; style=filled; color=lightcoral; label=\"TAIL\"];\n");
        fprintf(file, "    tail -> node%03d [style=dashed; color=red; ];\n", index);
    }

    current_node = lst->tail;

    while (current_node && current_node->prev)
    {
        if (index > 0)
        {
            fprintf(file, "    node%03d -> node%03d [weight=0; color= green; constraint=false; ];\n",
                                    index, index - 1);
        }

        current_node = current_node->prev;
        index--;
    }

    if (lst->head)
    {
        fprintf(file, "    head [shape=ellipse; style=filled; color=lightblue; label=\"HEAD\"];\n");
        fprintf(file, "    head -> node000 [style=dashed; color=blue; ];\n");
    }
    
    fprintf(file, "}\n");
    fclose(file);

    sprintf(command, "dot -Tpng %s -o %s", dot_filename, png_filename);
    system(command);

    file_counter++;
    
    free(dot_filename);
    free(png_filename);
    free(command);

    return 0;
}

int list_verify(List* lst)
{
    int list_errors = 0;
    
    if (lst == nullptr)
    {
        list_errors |= LIST_IS_NULL;

        return list_errors;
    }

    if (lst->size < 0)
    {
        list_errors |= LIST_SIZE_BELOW_ZERO;
    }

    // if (lst->head == nullptr)
    // {
    //     list_errors |= LIST_HEAD_IS_NULL;
    // }

    // if (lst->tail == nullptr)
    // {
    //     list_errors |= LIST_TAIL_IS_NULL;
    // }

    return list_errors;
}

void convert_to_binary(int num)
{
    if (num == 0)
    {
        fprintf(stderr, "0");
        return;
    }
    
    int binary[32] = {};
    int i = 0;
    
    while (num > 0)
    {
        binary[i] = num % 2;
        num /= 2;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
    {
        fprintf(stderr, "%d", binary[j]);
    }
}

const char* convert_to_str(int err)
{
    switch(err)
    {
        case LIST_IS_NULL:         { return "LIST_IS_NULL";         break;}
        case LIST_SIZE_BELOW_ZERO: { return "LIST_SIZE_BELOW_ZERO"; break;}
        // case LIST_HEAD_IS_NULL:    { return "LIST_HEAD_IS_NULL";    break;}
        // case LIST_TAIL_IS_NULL:    { return "LIST_TAIL_IS_NULL";    break;}
        default:                   { return "UNKNOWN ERROR"; }
    }
}

void list_errors_output(int list_errors)
{
    fprintf(stderr, RED "Error: " CLEAR);

    convert_to_binary(list_errors);

    const char* str_error = convert_to_str(list_errors);

    fprintf(stderr, RED " %s" CLEAR, str_error);
}

void list_assert(List* lst)
{
    int list_errors = list_verify(lst);

    if (list_errors != 0)
    {
        list_errors_output(list_errors);
        fprintf(stderr, PURPLE_TEXT("\nLINE: %d FUNCTION: %s FILE: %s\n"), __LINE__, __FUNCTION__, __FILE__);

        abort();
    }
}







