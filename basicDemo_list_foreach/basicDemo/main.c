#include <stdio.h>
#include <stdlib.h>
#include "list_each.h"

struct list_head head = {&head, &head};

void print_list(struct example *ca1, struct example *ca2, struct list_head *head)
{
	printf("head 0x%x 0x%x 0x%x\n", head, head->prev, head->next);
	printf("ca1 0x%x 0x%x 0x%x\n", &ca1->list, ca1->list.prev, ca1->list.next); //ca1
	printf("ca2 0x%x 0x%x 0x%x\n", &ca2->list, ca2->list.prev, ca2->list.next); //ca2
	printf("\n");
}

int main(int argc, char *argv)
{
	struct example *cur = NULL;
	struct example ca1 = {.a = 9, .b = 8};
	struct example ca2 = { .a = 19,.b = 18};
	//head
	list_add(&ca1.list, head.prev, &head);
	list_add(&ca2.list, head.prev, &head);
	print_list(&ca1, &ca2, &head);
	//
	list_for_each_entry_cus(cur, head, list) {
		printf("a %d b %d, cur 0x%x 0x%x 0x%x\n", cur->a, cur->b,
			&cur->list, cur->list.prev, cur->list.next); //cur
	}

	return 0;
}