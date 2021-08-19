#pragma once
#ifndef LIST_EACH_H
#define LIST_EACH_H

struct list_head {
	struct list_head *next, *prev;
};

struct example {
	int a;
	int b;
	struct list_head list;
};
typedef struct example caseInfo;

void list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;
}

#ifdef offsetof
#undef offsetof
#endif
#define offsetof(TYPE, MEMBER)    ((size_t) &((TYPE *)0)->MEMBER)

/**
* container_of - cast a member of a structure out to the containing structure
* @ptr: the pointer to the member.
* @type: the type of the container struct this is embedded in.
* @member: the name of the member within the struct.
*
*/
#ifdef container_of
#undef container_of
#endif
#define container_of(ptr, type, member)    (type*)( (char*)(ptr) - offsetof(type, member) )

/**
* list_for_each_entry     -     iterate over list of given type
* @pos:      the type * to use as a loop cursor.
* @head:     the head for your list.
* @member:   the name of the list_struct within the struct.
*/
#define list_for_each_entry_cus(pos, head, member)                    \
		for (pos = container_of(head.next, struct example, member); \
			&pos->list != &head; \
			pos = container_of(pos->list.next, struct example, member))

#endif