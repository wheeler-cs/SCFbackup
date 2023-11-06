#ifndef SCF_LIST_H
#define SCF_LIST_H

struct list_member
{
    struct list_member *next, *previous;
    void *data;
    unsigned int data_size;
};

struct data_list
{
    struct list_member *head, *tail;
    unsigned int size;
};


struct data_list *create_list();
void delete_list (struct data_list **, void (*f) (void *));
struct list_member *create_list_member (unsigned int);
void delete_list_member (struct list_member *, void (*f) (void *));
void push_front_list (struct data_list *, struct list_member *);
void push_back_list (struct data_list *, struct list_member *);
struct list_member *pop_front_list (struct data_list *);
struct list_member *pop_back_list (struct data_list *);
int is_list_empty (struct data_list *);
int is_list_malformed (struct data_list *);

#endif
