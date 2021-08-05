#include "list_stack.h"
#include <stdlib.h>
#include <stdio.h>

int list_stack_init(struct data *d)
{
	(d->anon_s).structure_pointer = &List_Stack;
	struct stack_list *st = (struct stack_list*)malloc(sizeof(struct stack_list));
	if (st) {
		st->item = NULL;
		st->next = NULL;
		d->anon_s.structure_pointer = st;
		return TRUE;
	}
	return FALSE;
}
int list_stack_push(struct data *d)
{
	struct stack_list *st = d->anon_s.structure_pointer;
	while (st->next != NULL) {
		st = st->next;
	}
	st->next = (struct stack_list*)malloc(sizeof(struct stack_list));
	st = st->next;
	st->item = d->data_ptr;
	st->next = NULL;
	return TRUE;
}
int list_stack_pop(struct data *d)
{
	struct stack_list *st = d->anon_s.structure_pointer;
	struct stack_list *q = st;	
	while (st->next != NULL ){
		q = st;
		st = st->next;
	}
	
	q->next = NULL;
	free(st);
	
}
int list_stack_upload(struct data *d)
{
	return TRUE;
}
int list_stack_download(struct data *d)
{
	return TRUE;
}
int list_stack_print(struct data *d)
{
	struct stack_list *st = d->anon_s.structure_pointer;
	while (st->next != NULL) {
		st = st->next;
		printf("%s\n", st->item);
	}
}