/*
** chord ring
**  email:  pfming1989@gmail.com
*/
#ifndef RING_H
#define RING_H
#include "node.h"
#include <stdlib.h>

typedef struct rnode rnode;
struct rnode
{
	int size;
	int pid;
	node* chord_node;
	rnode* next;
};
class Circle
{
public:
Circle()
	{
	ring=(rnode*)calloc(1,sizeof(rnode));
	ring->chord_node=0;
	ring->next=ring;
	ring->pid=0;
	ring->size=0;
	}
Circle(node* p)
	{
   ring=(rnode*)calloc(1,sizeof(rnode));
   ring->chord_node=p;
   ring->next=ring;
   ring->pid=p->get_address()->map;
   ring->size=p->get_size();
	}
rnode* Circle::get_ring();
void set_ring(node* p);
bool add_node(node* p);
bool remove_node(node* p);
int get_number();
node* find_node(address* p);
node* Circle::find_node(int x);
void print_ring();
void print_keys();
private:
	static int number;
	static rnode* ring;
};
#endif
