#ifndef SCF_LIST_H
#define SCF_LIST_H

struct string_list_member
{
    struct string_list_member *next, *previous;
    char *c_string;
};

struct string_linked_list
{
    struct string_list_member *head, *tail;
    unsigned int size;
};


struct string_linked_list * create_string_linked_list();

#endif
