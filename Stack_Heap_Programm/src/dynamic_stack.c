#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamic_stack.h"

int dynamic_stack_init(struct data *d)
{
	char **arr = (char**)malloc(sizeof(char*) * d->size);

	if (arr) {
		struct dynamic_stack *st = malloc(sizeof(struct dynamic_stack));
		
		if (!st)
			return FALSE;

		st->top = -1;
		st->arr = (void **)arr;
		d->data_type_pnt = (void *)st;
		return TRUE;
	} else {
		printf("Memory leak\n");
	}

	return FALSE;
}

int dynamic_stack_push(struct data *d, void *data)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;

	if (dynamic_stack_is_full(d) == FALSE) {
		st->arr[++st->top] = data;
		return TRUE;
	}

	return FALSE;
}

int dynamic_stack_is_empty(struct data *d)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;

	if (st->top == -1) {
		return TRUE;
	}

	return FALSE;
}

int dynamic_stack_pop(struct data *d)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;

	if (dynamic_stack_is_empty(d) == FALSE) {
		st->arr[st->top--] = NULL;
		return TRUE;
	}

	return FALSE;
}

int dynamic_stack_is_full(struct data *d)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;

	if (st->top + 1 == d->size) {
		printf("Stack is full\n");
		return TRUE;
	}

	return FALSE;
}

int dynamic_stack_print(struct data *d, int flag)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;
	FILE *f;

	if (flag == TO_FILE) {
		if (d->filename_download) {
			f = fopen(d->filename_download, "w");
			if (!f) {
				printf("File opening error\n");
				return FALSE;
			}
			for (int i = 0; i <= st->top; i++) {
				if (st->arr[i]) 
					fprintf(f, "%s\n", (char*)st->arr[i]);
				else
					fprintf(f, "%s\n", "NULL");
			}
			fclose(f);
			return TRUE;
		} else {
			printf("No download file specified!\n");
			return FALSE;
		}
	} else if (flag == TO_STDOUT) {
		for (int i = 0; i <= st->top; i++) {
			if (st->arr[i]) 
				printf("%s\n", (char*)st->arr[i]);
			else
				printf("NULL\n");
		}
		printf("\n======================================\n");
		return TRUE;
	}

	return FALSE;
}

int dynamic_stack_upload(struct data *d)
{
	FILE *file;
	char line[256];

	if (d->filename_upload) {	
		file = fopen(d->filename_upload, "r");
		if (file) {
			while (fgets(line, sizeof(line), file)) {
				//delete last \n charachter
				line[strlen(line) - 1] = '\0';
				if (dynamic_stack_push(d, strdup(line)) == FALSE) {
					printf("Push crashed\n");
					return FALSE;
				}
			}
			fclose(file);

			return TRUE;
		} else {
			printf("File opening error ! \n");
			return FALSE;
		}
	}

	return FALSE;
}

int dynamic_stack_download(struct data *d)
{
	struct dynamic_stack *st = (struct dynamic_stack*)d->data_type_pnt;
	if (dynamic_stack_is_empty(d) == TRUE) {
		printf("Not creating files for an empty stack\n");
		return FALSE;
	}

	return dynamic_stack_print(d, TO_FILE);
}