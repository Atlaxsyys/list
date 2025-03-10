#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "list.h"

List *list_constructor()
{
    List *lst = (List*)calloc(1, sizeof(List));

    if(lst == nullptr)
    {
        fprintf(stderr, "lst is null pointer");
    }

    lst->head = nullptr;
    lst->tail = nullptr;
    lst->size = 0;

    return lst;
}

void list_destructor(List* lst)
{
    assert(lst);

    list_clear(lst);

    free(lst);
    lst = nullptr;
}

void insert_before_head(List *lst, elem_t value)                           //               +-------+    next   +-------+        +-------+         
{                                                                          //               |       |   ----->  |       |        |       |                      
    assert(lst);                                                           //       <----   | value |   <-----  |       |   .... |       |             
                                                                           // prev = null   +-------+    prev   +-------+        +-------+                      
    List_elem_t* new_node = (List_elem_t*)calloc(1, sizeof(List_elem_t)); //               ^curr_node            ^head            ^tail

    new_node->value = value;
    new_node->prev = nullptr;

    if (lst->head == nullptr)
    {
        lst->head = new_node;
        lst->tail = new_node;
        new_node->next = nullptr;
        new_node->prev = nullptr;
    }
 
    else
    {
        new_node->next = lst->head;
        lst->head->prev = new_node;
        lst->head = new_node;
    }

    lst->size++;
}

void insert_after_tail(List *lst, elem_t value)                             //    +-------+       +-------+   next    +-------+  next = null                                                     
{                                                                           //    |       |       |       |  ----->   |       | ----->                                      
    assert(lst);                                                            //    |       |  .... |       |  <-----   | value |                                               
                                                                            //    +-------+       +-------+   prev    +-------+                                                      
    List_elem_t* new_node = (List_elem_t*)calloc(1, sizeof(List_elem_t));  //     ^head            ^tail             ^curr_node

    new_node->value = value;
    new_node->next = nullptr;

    if(lst->tail == nullptr)
    {
        lst->head = new_node;
        lst->tail = new_node;
        new_node->prev = nullptr;
    }

    else
    {
        new_node->prev = lst->tail;
        lst->tail->next = new_node;
        lst->tail = new_node;
    }

    lst->size++;
}

List_elem_t* get_head__list(List* lst)
{
    assert(lst);

    return lst->head;
}

List_elem_t* get_tail__list(List* lst)
{
    assert(lst);

    return lst->tail;
}

List_elem_t* get_next_current_elem(List_elem_t* current_element)
{
    assert(current_element);

    return current_element->next;
}

List_elem_t* get_prev_current_elem(List_elem_t* current_element)
{
    assert(current_element);

    return current_element->prev;
}

List_elem_t* find_to_number(List* lst, size_t number)
{
    assert(lst);

    List_elem_t* current_element = get_head__list(lst);

    for(size_t i = 0; i < number; i++)
    {
        current_element = get_next_current_elem(current_element);
    }

    return current_element;
}

List_elem_t* find_to_value(List* lst, elem_t value)
{
    assert(lst);

    List_elem_t* current_element = get_head__list(lst);

    while(current_element != nullptr)
    {
        if(current_element->value == value)
        {
            return current_element;
        }

        current_element = get_next_current_elem(current_element);
    }

    return nullptr;
}

void insert_before_element(List* lst, size_t number, elem_t value)
{
    assert(lst);

    List_elem_t* current_element = find_to_number(lst, number);

    List_elem_t* new_element = (List_elem_t*) calloc(1, sizeof(List_elem_t));

    new_element->prev = current_element->prev;
    new_element->next = current_element;
    new_element->value = value;

    get_prev_current_elem(current_element)->next = new_element;
    current_element->prev = new_element;

    lst->size++;
}

void insert_after_element(List* lst, size_t number, elem_t value)
{
    assert(lst);

    List_elem_t* current_element = find_to_number(lst, number);

    List_elem_t* new_element = (List_elem_t*) calloc(1, sizeof(List_elem_t));

    new_element->next = current_element->next;
    new_element->prev = current_element;
    new_element->value = value;

    get_next_current_elem(current_element)->prev = new_element;
    current_element->next = new_element;

    lst->size++;
}

void insert_first(List* lst, elem_t value)
{
    assert(lst);

    List_elem_t* new_element = (List_elem_t*) calloc(1, sizeof(List_elem_t));

    new_element->value = value;
    new_element->next = nullptr;
    new_element->prev = nullptr;

    lst->head = new_element;
    lst->tail = new_element;
    lst->size = 1;
}

void delete_element(List* lst, size_t number)
{
    assert(lst);

    List_elem_t* current_element = find_to_number(lst, number);

    if (lst->size == 1)
    {
        lst->head = nullptr;
        lst->tail = nullptr;
    }

    else if(current_element == lst->head)
    {
        lst->head = get_next_current_elem(current_element);
        get_next_current_elem(current_element)->prev = nullptr;

    }

    else if(current_element == lst->tail)
    {
        lst->tail = get_prev_current_elem(current_element);
        get_prev_current_elem(current_element)->next = nullptr;
    }

    else
    {
        get_prev_current_elem(current_element)->next = get_next_current_elem(current_element);
        get_next_current_elem(current_element)->prev = get_prev_current_elem(current_element);
    }

    current_element->value = POIZON_VALUE;
    current_element->next = nullptr;
    current_element->prev = nullptr;

    free(current_element);
    lst->size--;
}

void list_clear(List* lst)
{
    assert(lst);

    List_elem_t* current_element = get_head__list(lst);
    List_elem_t* next_element = nullptr;

    for (int i = 0; i < lst->size; i++)
    {
        next_element = get_next_current_elem(current_element);

        current_element->next = nullptr;
        current_element->prev = nullptr;
        current_element->value = POIZON_VALUE;

        free(current_element);

        current_element = next_element;
    }

    lst->size = 0;
    lst->head = nullptr;
    lst->tail = nullptr;
}


void graph_dump(List* lst)
{
    static int file_counter = 0;
    char* dot_filename = (char*) calloc(SIZE_DOT_FILENAME, sizeof(char));
    char* png_filename = (char*) calloc(SIZE_PNG_FILENAME, sizeof(char));
    char* command = (char*) calloc(SIZE_COMMAND, sizeof(char));

    sprintf(dot_filename, "../tests/graph_%d.dot", file_counter);
    sprintf(png_filename, "../tests/graph_%d.png", file_counter);

    FILE* file = fopen(dot_filename, "w");

    if (!file)
    {
        perror("Error open file: ");

        return;
    }

    fprintf(file, "digraph G {\n");
    fprintf(file, "    rankdir = LR;\n");
    fprintf(file, "    bgcolor=\"#C0C0C0\";\n\n");

    List_elem_t* current_element = lst->head;
    int index = 0;

    while (current_element)
    {
        fprintf(file, "    node%03d [shape=Mrecord; style=filled; fillcolor=\"blue:white\"; label=\" { value: %d } | {next: %d} | {prev: %d} \"];\n",
                index, current_element->value,
                (current_element->next ? index + 1 : -1),
                (current_element->prev ? index - 1 : -1));

        current_element = current_element->next;
        index++;
    }

    fprintf(file, "\n");

    current_element = lst->head;
    index = 0;
    while (current_element && current_element->next)
    {
        fprintf(file, "    node%03d -> node%03d [style=bold; weight=1000; color=red; ];\n",
                                index, index + 1);

        current_element = current_element->next;
        index++;
    }

    if (lst->tail)
    {
        fprintf(file, "    tail [shape=ellipse; style=filled; color=lightcoral; label=\"TAIL\"];\n");
        fprintf(file, "    tail -> node%03d [style=dashed; color=red; ];\n", index);
    }

    current_element = lst->tail;
    while (current_element && current_element->prev)
    {
        if (index > 0)
        {
            fprintf(file, "    node%03d -> node%03d [weight=0; color= green; constraint=false; ];\n",
                                    index, index - 1);
        }

        current_element = current_element->prev;
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
}




