#ifndef SCF_LIST_H
#define SCF_LIST_H

typedef struct linked_list
{
    struct linked_list *head, *tail;
    unsigned int size;
};

#endif
