/*|============================================================================|*
 *| Chess Application: file DoubleLinkedList.h                                 |*
 *|                                                                            |*
 *| Developed and programmed by:                                               |*
 *|           Milios Nikos, RN: 1523, email: milios@csd.uoc.gr                 |*
 *|        Velegrakis Ioannis, RN: 1494, email: jveleg@csd.uoc.gr              |*
 *|                                                                            |*
 *|                                                                            |*
 *| Copyright 2006: All rights reserved. Any copying, lending, seling or       |*
 *|                 public performance without a written permission is         |*
 *|					prohibited.                                                |*
 *| You must accept the enclosed License Agreement before you can use this     |*
 *| product. This is licensed as a single product. Its component parts may not |*
 *| be separated for use by more than one user. if you do not accept the terms |*
 *| of the License Agreement, you should promptly return the product for a     |*
 *| refund.                                                                    |*
 *|============================================================================|*/

#ifndef _DOUBLELINKEDLIST_H
	#define _DOUBLELINKEDLIST_H

	/*========== Other files used ====================*/
	#include <stdlib.h>
	/*================================================*/

typedef struct doublelinkedlist DoubleLinkedList;
#endif
#define CHECKED
//Constractor of  Double Linked List
extern DoubleLinkedList *DoubleLinkedListConstruct();						CHECKED
//add's an item in head of Double Linked List
extern void DoubleLinkedListAddInHead(DoubleLinkedList *p,void *item);		CHECKED
//add's an item in tail of Double Linked List
extern void DoubleLinkedListAddInTail(DoubleLinkedList *p,void *item);		CHECKED
//ad's an item in the i position of the Double Linked List
extern void DoubleLinkedListAdd(DoubleLinkedList *d,int i,void *item);		CHECKED
//return's an item of the i position of Double Linked List
extern void *DoubleLinkedListGet(DoubleLinkedList *d,int i);				CHECKED
//return's the item of the head of Double Linked List
extern void *DoubleLinkedListGetHead(DoubleLinkedList *p);					CHECKED
//return's the item of the tail of Double Linked List
extern void *DoubleLinkedListGetTail(DoubleLinkedList *p);					CHECKED
//return's the size of Double Linked List
extern int DoubleLinkedListGetSize(DoubleLinkedList *p);					CHECKED
//erase the item from head of Double Linked List
extern void DoubleLinkedListDelHead(DoubleLinkedList *p);					CHECKED
//erase the item from tail of Double Linked List
extern void DoubleLinkedListDelTail(DoubleLinkedList *p);					CHECKED
//erase the item from the i position of Double Linked List
extern void DoubleLinkedListDel(DoubleLinkedList *d,int i);					CHECKED
//find's if an item exist in Linked List
extern int DoubleLinkedListSearch(DoubleLinkedList *d,void *item,int(*cmp)(void *,void *));
																			CHECKED
//add an item shorted the Linked List
extern void DoubleLinkedListAddSorted(DoubleLinkedList *d,void *item,int(*cmp)(void *,void *)  );
																			CHECKED
//Aplay a Function in all nodes of list
extern void DoubleLinkedListAplay(DoubleLinkedList *d,void (*func)(void *));
																			CHECKED
//drops a LinkedList d
extern void DoubleLinkedListDrop(DoubleLinkedList *d);						CHECKED
//copy a List d to a new that return as result
extern DoubleLinkedList *DoubleLinkedListCopy(DoubleLinkedList *d);			CHECKED
//reverse a List d to a new that return as result
extern DoubleLinkedList *DoubleLinkedListReverse(DoubleLinkedList *d);		CHECKED
//split a List d at node i.(The size of d is i, and the rest nodes returned as a List)
extern DoubleLinkedList *DoubleLinkedListSplit(DoubleLinkedList *d,int i);	CHECKED
//Join 2 Lists(t1,t2) and return the result As a copy of t1+t2
extern DoubleLinkedList *DoubleLinkedListMergeCopy(DoubleLinkedList *t1,DoubleLinkedList *t2);
																			CHECKED
//Join 2 Lists(t1,t2) (t1 have the nodes of t2 and t2 is empty)
extern void DoubleLinkedListMerge(DoubleLinkedList *t1,DoubleLinkedList *t2);
																			CHECKED
//short a List d
extern void DoubleLinkedListSort(DoubleLinkedList *d,int(*cmp)(void *,void *));
																			CHECKED
//Join 2 Lists(t1,t2) and return the result As a New sorted List
extern DoubleLinkedList *DoubleLinkedListMergeSorted(DoubleLinkedList *t1,DoubleLinkedList *t2,int(*cmp)(void *,void *));
																			CHECKED
//find's if an item exist in Linked List return a list with the items
extern DoubleLinkedList *DoubleLinkedListMultiSearch(DoubleLinkedList *d,void *item,int(*cmp)(void *,void *));
																				CHECKED

