/*|============================================================================|*
 *| Chess Application: file DoubleLinkedList.cpp                               |*
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

/*=========== Other files used =====================*/
#include "DoubleLinkedList.h"
#include <iostream>
/*==================================================*/


//from DobleNode.h
//#include <stdlib.h>
typedef struct doublenode DoubleNode;
//Constractor of DoubleNode
DoubleNode *DoubleNodeConstruct();
//add's an item in DoubleNode
void DoubleNodeAdd(DoubleNode *p,void *item);
//return's the item of the DoubleNode
void * DoubleNodeGet(DoubleNode *p);
//return's the next DoubleNode of the DoubleNode
DoubleNode * DoubleNodeGetNext(DoubleNode *p);
//set's a DoubleNode as the next node of DoubleNode
void DoubleNodeSetNext(DoubleNode *p,DoubleNode *nxt);
//return's the previous DoubleNode of the DoubleNode
DoubleNode * DoubleNodeGetPrev(DoubleNode *p);
//set's a DoubleNode as the previous node of DoubleNode
void DoubleNodeSetPrev(DoubleNode *p,DoubleNode *prv);
//erase the DoubleNode
void DoubleNodeDel(DoubleNode *p);
struct doublenode
{
	void *obj;
	DoubleNode *next;
	DoubleNode *prev;
};
DoubleNode *DoubleNodeConstruct()
{
 DoubleNode *p;
 p=new DoubleNode();

 p->next=NULL;
 p->prev=NULL;
 return p;
}
void DoubleNodeAdd(DoubleNode *p,void *item)
{
	if(p!=NULL)
		p->obj=item;
}
void DoubleNodeDel(DoubleNode *p)
{
	//free(p->obj);
	delete p;//free(p);
	return;
}
void * DoubleNodeGet(DoubleNode *p)
{
	if(p==NULL) return NULL;
	return p->obj;
}
DoubleNode * DoubleNodeGetNext(DoubleNode *p)
{
	if(p==NULL) return NULL;
	return p->next;
}
void DoubleNodeSetNext(DoubleNode *p,DoubleNode *nxt)
{
	if(p!=NULL)
		p->next=nxt;
	return;
}
DoubleNode * DoubleNodeGetPrev(DoubleNode *p)
{
	if(p==NULL) return NULL;
	return p->prev;
}
void DoubleNodeSetPrev(DoubleNode *p,DoubleNode *prv)
{
	if(p!=NULL)
		p->prev=prv;
	return;
}


//End of DoubleNode.h

struct doublelinkedlist
{
	DoubleNode *head;
	DoubleNode *tail;
	int last;
	DoubleNode * lastp;
	int size;
	int issorted;
};

DoubleNode *DoubleLinkedListFind(DoubleLinkedList *d,int i)
{

	int j=0;
	DoubleNode *p=NULL;
	if(d!=NULL)
	{
		if(i>d->size) return NULL;
		if(i<(d->last - 0)/2) //scan list from head to right
		{
			p=d->head;
			while(p != NULL && i>j++)
			{
				p=DoubleNodeGetNext(p);
			}
		}
		else if(i>d->last + ((d->size-1)- d->last)/2) //scan list from tail to left
		{
			p=d->tail;
			while(p != NULL && ((d->size-1)-i)>j++)
			{
				p=DoubleNodeGetPrev(p);
			}
		}
		else if(i<d->last)		//scan list from last to left
		{
			
			p=d->lastp;
			while(p != NULL && (d->last-i)>j++)
			{
				p=DoubleNodeGetPrev(p);
			}
		}
		else					//scan list from last to right
		{
			p=d->lastp;
			while(p != NULL && (i-d->last)>j++)
			{
				p=DoubleNodeGetNext(p);
			}
		}

		if(p==NULL) return NULL;
		d->last=i;
		d->lastp=p;
		return p;
	}
	return NULL;
}

DoubleLinkedList *DoubleLinkedListConstruct()
{
 DoubleLinkedList *p;
 p=new DoubleLinkedList();
 
 p->head=NULL;
 p->tail=NULL;
 p->size=0;
 p->last=0;
 p->lastp=p->head;
 p->issorted=0;
 return p;
}
void DoubleLinkedListAddInHead(DoubleLinkedList *p,void *item)
{
	DoubleNode *tmp;
	if(p!=NULL)
	{
		if(p->head!=NULL)
		{
			tmp=p->head;
			p->head=DoubleNodeConstruct();
			DoubleNodeAdd(p->head,item);
			DoubleNodeSetNext(p->head,tmp);
			DoubleNodeSetPrev(tmp,p->head);
			p->size++;
			p->last=0;
			p->lastp=p->head;
			p->issorted=0;
		}
		else if(p->head==NULL)
		{
			p->head=DoubleNodeConstruct();
			p->tail=p->head;
			DoubleNodeAdd(p->head,item);
			p->size=1;
			p->last=0;
			p->lastp=p->head;
			p->issorted=1;
		}
	}
}
void DoubleLinkedListAddInTail(DoubleLinkedList *p,void *item)
{
	DoubleNode *tmp;
	if(p!=NULL)
	{
		if(p->head!=NULL)
		{
			tmp=p->tail;
			p->tail=DoubleNodeConstruct();
			DoubleNodeAdd(p->tail,item);
			DoubleNodeSetPrev(p->tail,tmp);
			DoubleNodeSetNext(tmp,p->tail);
			DoubleNodeSetNext(p->tail,NULL);
			p->size++;
			p->issorted=0;
		}
		else if(p->head==NULL)
		{
			DoubleLinkedListAddInHead(p,item);
		}
	}
}
void DoubleLinkedListAdd(DoubleLinkedList *d,int i,void *item)
{
	DoubleNode *p;
	DoubleNode *tmp;
	if(d!=NULL)
	{
		if(d->head==NULL || i==0)
		{
			DoubleLinkedListAddInHead(d,item);
			return;
		}
		if(i==d->size) 
		{
				DoubleLinkedListAddInTail(d,item);
				return;
		}
		if(i>d->size) return;

		p=DoubleLinkedListFind(d,i-1);
		if(p==NULL) return;
		if(p!=NULL)
		{
			tmp=p;
			p=DoubleNodeConstruct();
			DoubleNodeAdd(p,item);
			DoubleNodeSetNext(p,DoubleNodeGetNext(tmp));
			DoubleNodeSetPrev(p,tmp);
			DoubleNodeSetNext(tmp,p);
			DoubleNodeSetPrev(DoubleNodeGetNext(p),p);

			d->size++;
			d->last=i;
			d->lastp=p;
			d->issorted=0;
		}
	}
	return ;
}


void *DoubleLinkedListGet(DoubleLinkedList *d,int i)
{
	DoubleNode *p;
	p=DoubleLinkedListFind(d,i);
	if(p==NULL)
		return NULL;
	return DoubleNodeGet(p);
}
void *DoubleLinkedListGetHead(DoubleLinkedList *p)
{
	if(p!=NULL)
		if(p->head!=NULL)
			return DoubleNodeGet(p->head);
	return NULL;
}
void *DoubleLinkedListGetTail(DoubleLinkedList *p)
{
	if(p!=NULL)
		if(p->tail!=NULL)
			return DoubleNodeGet(p->tail);
	return NULL;
}
int DoubleLinkedListGetSize(DoubleLinkedList *p)
{
	if(p!=NULL)
		return (p->size);
	return 0;
}
void DoubleLinkedListDelHead(DoubleLinkedList *p)
{
	DoubleNode *tmp;
	tmp=p->head;
	p->head=DoubleNodeGetNext(tmp);
	DoubleNodeSetPrev(p->head,NULL);
	p->size--;
	p->last=0;
	p->lastp=p->head;
	DoubleNodeDel(tmp);
	if(p->size==1)
		p->tail=p->head;
	p->last=0;
	p->lastp=p->head;
	return;
}
void DoubleLinkedListDelTail(DoubleLinkedList *p)
{
	DoubleNode *tmp;
	tmp=p->tail;
	p->tail=DoubleNodeGetPrev(tmp);
	DoubleNodeSetNext(p->tail,NULL);
	p->size--;
	DoubleNodeDel(tmp);
	if(p->size==1)
		p->head=p->tail;
	p->last=0;
	p->lastp=p->head;
	if(p->size==0)
	{
		p->head=NULL;
		p->tail=NULL;
		p->lastp=NULL;
		p->last=0;
	}
	return;
}
void DoubleLinkedListDel(DoubleLinkedList *d,int i)
{
	DoubleNode *p;
	if(d!=NULL)
	{
		if(i>=d->size || i<0) return;
		p=d->head;
		if(i==0)
		{
			DoubleLinkedListDelHead(d);
			return;
		}
		if(i==d->size-1)
		{
			DoubleLinkedListDelTail(d);
			return;
		}
		p=DoubleLinkedListFind(d,i);
		if(p==NULL) return;
		DoubleNodeSetNext(DoubleNodeGetPrev(p),DoubleNodeGetNext(p));
		DoubleNodeSetPrev(DoubleNodeGetNext(p),DoubleNodeGetPrev(p));
		d->last-=1;
		d->lastp=DoubleNodeGetPrev(p);
		d->size--;
		DoubleNodeDel(p);
	}
	return ;
}
int DoubleLinkedListSearch(DoubleLinkedList *d,void *item,int (*cmp)(void *,void *))
{
	int j=0;
	DoubleNode *p;
	if(d!=NULL)
	{
		p=d->head;
		while(p != NULL && cmp(DoubleNodeGet(p),item)!=0)
		{
			p=DoubleNodeGetNext(p);
			j++;
		}
		if(p==NULL) return -1;
		return (j);
	}
	return -1;
}
DoubleLinkedList *DoubleLinkedListMultiSearch(DoubleLinkedList *d,void *item,int (*cmp)(void *,void *))
{
	int j=0;
	DoubleNode *p;
	DoubleLinkedList *res=NULL;
	if(d!=NULL)
	{
		p=d->head;
		while(p != NULL)
		{
			if(cmp(DoubleNodeGet(p),item)==0)
			{
				if(res==NULL)
				{
					res=DoubleLinkedListConstruct();
					DoubleLinkedListAddInHead(res,DoubleNodeGet(p));
				}
				else
				{
					DoubleLinkedListAddInTail(res,DoubleNodeGet(p));
				}
			}
			p=DoubleNodeGetNext(p);
			j++;
		}
		if(res==NULL) return NULL;
		res->issorted=d->issorted;
		return (res);
	}
	return NULL;
}

//add an item shorted the Linked List
void DoubleLinkedListAddSorted(DoubleLinkedList *d,void *item,int(*cmp)(void *,void *)  )
{
	int i=0;
	int sz;
	DoubleNode *r;
	if(d==NULL || cmp==NULL ||  item==NULL )
		return;
	sz=DoubleLinkedListGetSize(d);
	if(d->issorted==0)
	{
		DoubleLinkedListSort(d,cmp);
	}
	do
	{
		r=DoubleLinkedListFind(d,i++);
	}
	while( i<=sz && r!=NULL && cmp(r->obj,item)>0);
	DoubleLinkedListAdd(d,i-1,item);

}
//Apply a Function in all nodes of list
void DoubleLinkedListAplay(DoubleLinkedList *d,void (*func)(void *))
{
	int i=0;
	int sz;
	if(d==NULL || func==NULL)
		return;
	sz=DoubleLinkedListGetSize(d);
	for(i=0;i<sz;i++)
	{
		func(DoubleLinkedListGet(d,i));
	}
}
//Drop a LinkedList d
void DoubleLinkedListDrop(DoubleLinkedList *d)
{
	int i;
	int isz;
	if(d==NULL)
		return;
	isz=DoubleLinkedListGetSize(d);
	for(i=0;i<isz;i++)
	{
		DoubleLinkedListDel(d,0);	
	}
	delete d;//free(d);
}

DoubleLinkedList *DoubleLinkedListCopy(DoubleLinkedList *d)
{
	DoubleLinkedList *tmp;
	int i;
	int sz;
	tmp=DoubleLinkedListConstruct();
	sz=DoubleLinkedListGetSize(d);
	for(i=0;i<sz;i++)
	{
		DoubleLinkedListAdd(tmp,i,DoubleLinkedListGet(d,i));
	}
	return tmp;
}
DoubleLinkedList *DoubleLinkedListReverse(DoubleLinkedList *d)
{
	DoubleLinkedList *tmp;
	int i;
	int sz;
	tmp=DoubleLinkedListConstruct();
	sz=DoubleLinkedListGetSize(d);
	for(i=0;i<sz;i++)
	{
		DoubleLinkedListAdd(tmp,i,DoubleLinkedListGet(d,sz-(i+1)));
	}
	return tmp;
}
DoubleLinkedList *DoubleLinkedListSplit(DoubleLinkedList *d,int j)
{
	DoubleLinkedList *tmp;
	int i,sz;
	tmp=DoubleLinkedListConstruct();
	sz=DoubleLinkedListGetSize(d);
	for(i=0;i<sz;i++)
	{
		if(i<j)
		{
			
		}
		else
		{
			DoubleLinkedListAdd(tmp,i-j,DoubleLinkedListGet(d,j));
			DoubleLinkedListDel(d,j);
		}
	}
	return tmp;
}
DoubleLinkedList *DoubleLinkedListMergeCopy(DoubleLinkedList *t1,DoubleLinkedList *t2)
{
	DoubleLinkedList *tmp;
	int i;
	tmp=DoubleLinkedListCopy(t1);
	for(i=0;i<DoubleLinkedListGetSize(t2);i++)
	{
		DoubleLinkedListAddInTail(tmp,DoubleLinkedListGet(t2,i));
	}
	return tmp;
}
void DoubleLinkedListMerge(DoubleLinkedList *t1,DoubleLinkedList *t2)
{
	DoubleNodeSetNext(t1->tail,t2->head);
	DoubleNodeSetPrev(t2->head,t1->tail);
	t1->size+=t2->size;
	t1->tail=t2->tail;
	t2->head=NULL;
	t2->tail=NULL;
	t2->lastp=NULL;
	t2->size=0;
	t2->last=0;
}

void DoubleLinkedListSort(DoubleLinkedList *d,int(*cmp)(void *,void *) )
{
	int i=0,sz;

	
	sz=DoubleLinkedListGetSize(d);

	//Sort 2
	while(i<sz)		//for each 2 nodes do sort
	{
		DoubleNode *r;
		r=DoubleLinkedListFind(d,i);

		if(r->next!=NULL  && cmp(r->obj,r->next->obj)<0)
		{
			void *tmp;
			tmp=r->obj;
			r->obj=r->next->obj;
			r->next->obj=tmp;
		}
		i+=2;
	}

	//Merge

	i=2; //Segment 2
	while(i<sz)//Merge the Sorted  Sub List 
	{
		int j;
		DoubleNode *llast;
		DoubleNode *l1;
		DoubleNode *l2;
		llast=NULL;

		j=0;
		do //merge all segments by 2
		{
			int v1;
			int v2;
			v1=j;
			v2=j+i;
			l1=DoubleLinkedListFind(d,v1);
			l2=DoubleLinkedListFind(d,v2);
//			printf("v1:%d l1:%d  v2:%d l2:%d tail:%d",v1,*(int *)l1->obj,v2,*(int *)l2->obj,*(int *)d->tail->obj);
			while(l1 !=NULL && l2!=NULL && v2<j+2*i && v1<j+i )//Merge 2 Segment
			{

				if(cmp(l1->obj,l2->obj)>=0)		//Copy nodes from 1 Segment
				{
					if(llast==NULL)			//First Node 
					{
						llast=l1;
						v1++;
						l1=DoubleNodeGetNext(l1);
					}
					else					
					{
						DoubleNodeSetNext(llast,l1);
						DoubleNodeSetPrev(l1,llast);
						llast=l1;
						v1++;
						l1=DoubleNodeGetNext(l1);
					}
				}
				else						//copy nodes from 2 Segment
				{
					if(llast==NULL)		//First Node 
					{
						d->head=l2;
						DoubleNodeSetPrev(l2,NULL);
						llast=l2;
						v2++;
						l2=DoubleNodeGetNext(l2);						
					}
					else
					{
						DoubleNodeSetNext(llast,l2);
						DoubleNodeSetPrev(l2,llast);
						llast=l2;
						v2++;
						l2=DoubleNodeGetNext(l2);
					}
				}
			}
			if(v1>=j+i || l1==NULL)			//Segment 1 Finished
				{
					while(v2<j+2*i && v2<d->size)	
					{
						DoubleNodeSetNext(llast,l2);
						DoubleNodeSetPrev(l2,llast);
						llast=l2;
						v2++;
						l2=DoubleNodeGetNext(l2);
					}
				}
			if(v2>=j+2*i || l2==NULL)	//Segment 2 Finished
				{
					while(v1<j+i && v1<d->size)
					{
						DoubleNodeSetNext(llast,l1);
						DoubleNodeSetPrev(l1,llast);
						llast=l1;
						v1++;
						l1=DoubleNodeGetNext(l1);
					}
				}
			j+=i*2;
			l2=DoubleLinkedListFind(d,j);
			DoubleNodeSetNext(llast,l2);
			if(l2!=NULL)
				DoubleNodeSetPrev(l2,llast);
		}
		while(j<sz);	//merge all segments by 2
		d->lastp=d->head;
		d->last=0;
		d->tail=llast;

	i*=2;
	}

	d->issorted=1;

}

DoubleLinkedList *DoubleLinkedListMergeSorted(DoubleLinkedList *t1,DoubleLinkedList *t2,int(*cmp)(void *,void *))
{
	DoubleLinkedList *tmp;
	int v1,v2,max,sz1,sz2;
	tmp=DoubleLinkedListConstruct();
	DoubleLinkedListSort(t1,cmp);
	DoubleLinkedListSort(t2,cmp);
	v1=0;
	v2=0;
	sz1=DoubleLinkedListGetSize(t1);
	sz2=DoubleLinkedListGetSize(t2);
	max=sz1+sz2;
	while(v1+v2<max)
	{
		void *l;
		if(v2>=sz2)
		{
			l=DoubleLinkedListGet(t1,v1);
			v1++;
		}
		else if(v1>=sz1)
		{
			l=DoubleLinkedListGet(t2,v2);
			v2++;
		}	
		else if(cmp(DoubleLinkedListGet(t1,v1),DoubleLinkedListGet(t2,v2))>0)
		{
			l=DoubleLinkedListGet(t1,v1);
			v1++;
		}
		else
		{
			l=DoubleLinkedListGet(t2,v2);
			v2++;
		}


		DoubleLinkedListAdd(tmp,v1+v2-1,l);
	}
	tmp->issorted=1;
	return tmp;
}
