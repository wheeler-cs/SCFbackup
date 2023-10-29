#ifndef SCF_LIST_H
#define SCF_LIST_H

struct string_list_member
{
    struct string_list_member *next, *previous;
    char *c_string;
};

struct string_list
{
    struct string_list_member *head, *tail;
    unsigned int size;
};


struct string_list *create_string_list();
void delete_string_list (struct string_list **);
struct string_list_member *create_string_list_member (char *);
void delete_string_list_member (struct string_list_member *);
void push_front_string_list (struct string_list *, struct string_list_member *);
void push_back_string_list (struct string_list *, struct string_list_member *);
struct string_list_member *pop_front_string_list (struct string_list *);
struct string_list_member *pop_back_string_list (struct string_list *);
int is_string_list_empty (struct string_list *);
int is_string_list_malformed (struct string_list *);
void traverse_print_string_list (struct string_list *);

#endif
