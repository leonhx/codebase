#include <iostream>

struct node {
	void *item;
	struct node *next;
};

struct Queue {
	struct node *first;
	int (*comp)(void *, void *);
};

<<<<<<< HEAD
struct SortList* NewSortList(int (*comp)(void *, void *)){
	struct SortList* q = new struct SortList;
	q->comp = comp;
	return q;
}

void Insert(void* x, struct SortList* q) {
	struct node *l = new struct node;
	l->item = x;
=======
struct Queue* NewQueue(){
	struct Queue* q = new struct Queue;
	return q;
}

void Enqueue(void* x, struct Queue* q) {
>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
	struct node* n = q->first;
	struct node* l = new struct node;
	l->item = x;
	l->next = NULL;
	if(n == NULL)
		q->first = l;
<<<<<<< HEAD
		l->next = n;
		return;		
	}
	if(q->comp(x, n->item) < 0) {
		q->first = l;
		l->next = n;
		return;
	}

	while((nn = n->next) != NULL){
		if(q->comp(x, nn->item) < 0){
			n->next = l;
			l->next = nn;
			return;
		}
=======
	while(n->next != NULL)
>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
		n = n->next;
	n->next = l;
}

void* Dequeue(struct Queue* q) {
	struct node *n = q->first;
	if(n == NULL)
		return NULL;
	if(n->next == NULL){
		q->first = NULL;
		void* i = n->item;
		delete n;
		return i;
	}
	struct node *nn;
	while((nn = n->next)->next != NULL)
		n = n->next;
	n->next = NULL;
	void* i = nn->item;
	delete nn;
	return i;
}

void Sort(struct Queue* q, (int (*comp)(void*, void*))) {
	struct node* n = q->first;
	struct node* nn;
	if(n == NULL || (nn = n->next) == NULL)
		return;
	int i = 1;
	while(nn != NULL) {
		n->next = nn->next;
		insert(nn, q, i++, comp);
		n = n->next;
		nn = n->next;
	}
}

<<<<<<< HEAD
int Delete(void* x, struct SortList* q) {
	struct node *n = q->first;
	if(q->comp(n->item, x) == 0){
		q->first = n->next;
		delete q->first;
		return 0;
	}
	struct node *nn;
	while((nn = n->next) != NULL){
		if(q->comp(nn->item, x) == 0){
			n->next = nn->next;
			delete nn;
			return 0;
=======
void insert(struct node* n, struct Queue* q, int i, (int (*comp)(void*, void*))) {
	struct node* p = q->first;
	int c;
	if(comp(n->item, p->item) < 0) {
		q->first = n;
		n->next = p;
		return;
	}
	struct node* pn = p->next;
	int j = 0;
	while(++j < i) {
		if(comp(n->item, pn->item) < 0){
			p->next = n;
			n->next = pn;
>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
		}

		p = p->next;
		pn = p->next;
	}
}

<<<<<<< HEAD
int comp(int* i1, int* i2){
	if(*i1 < *i2)
=======
int comp(int* i1, int* i2) {
	if(*i1 > *i2)
>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
		return -1;
	else if(*i1 >*i2)
		return 1;
	else
		return 0;
}

<<<<<<< HEAD
int main(int argc, char const *argv[])
{
	int x[] = {3, 1, -2, 9, 10, 0};
	struct SortList* sl = NewSortList((int (*)(void *, void *))comp);
	for (int i = 0; i < 6; ++i) {
		Insert((void*)&x[i], sl);
	}
	Delete(&x[1], sl);
	struct node* n = sl->first;
=======
int main(int argc, char const *argv[]) {
	int a = {5, 1, 0, 4, 7, 6, -1};
	struct Queue* q = NewQueue();
	for (int i = 0; a[i] != -1; ++i){
		Enqueue(&a[i], q);
	}
	Sort(struct Queue *q, int (*)(int (*)(void *, void *)))

>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
	while(n != NULL){
		std::cout<< *(int *)n->item <<std::endl;
		n = n->next;
	}
<<<<<<< HEAD
	delete sl;
	
=======

>>>>>>> 84dc2c47dacdacf14157a337aca730a3086f7b9f
	return 0;
}
