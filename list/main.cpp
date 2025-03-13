#include <stdio.h>

#include "list.h"

int main()
{
    List* lst = list_constructor();

    insert_first(lst, 50);
    graph_dump(lst);

    insert_after_tail(lst, &lst->tail, 20);
    graph_dump(lst);

    insert_before_head(lst, &lst->head, 10);
    graph_dump(lst);

    insert_after_node(lst, 1, 30);
    graph_dump(lst);

    delete_node(lst, 1);
    graph_dump(lst);

    list_destructor(lst);
}