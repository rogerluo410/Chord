#ifndef COMMON_H
#define COMMON_H
#include "network.h"
#include <stdlib.h>
#include <string.h>
static class Common
{
public:
	Common()
	{
	}
static void set_flag(bool p)//init the switch
{
	flag=p;
}
static Network* get_network()//get the network
{
	if(flag)
	{
		return network;
	}
	else
	return (Network*)0;
}
static int get_size()//size of network
{
	if(flag)
	{
		return size;
	}
	else
	return 0;
}
static void set_network(Network* p)
{
	if(!flag)
	{
	    network=p;
	}
}
static node* get_local()//local node 
{
	if(flag)
	{
		return local_node;
	}
	else
	return (node*)0;
}
static bool get_debug()
{
	return DEBUG;
}

static void set_local(node* p)//local node
{
	if(!flag)
	{
		local_node=p;
	}
}
static bool lies_in(int a, int x, int y){//judge whether a is betwwen x and y
	int max = 1 << size;
	if(y < x){
		if(((a>x) && (a<=max)) || ((a>=0) && (a<y)))
			return true;
	}
	else if((a>x) && (a<y))
		return true;
	return false;
}

static bool lies_in_address(int a, address *x, address *y){//judge whether a is betwwen x and y on the ring
	int X = x->map;
	int Y = y->map;
	return lies_in(a, X, Y+1);
}

static address* initaddress(const char* name,int size){
	int map = hash.map_node(name,size);
	address* temp=(address*)calloc(1,sizeof(address));
	char* p=(char*)calloc(100,sizeof(char));
	strcpy(p,name);
	temp->ipaddress=p;
	temp->map=map;
	return temp;
}
static flist* initkeys(const char* name,address* i)
{
	flist* p=(flist*)calloc(1,sizeof(flist));
	holder* h=(holder*)calloc(1,sizeof(holder));
	h->ip=common.copyaddress(i);
	h->next=0;
	p->destination=h;
	p->fid=hash.map_string(name,size);
	p->fname=(char*)calloc(50,sizeof(char));
	strcpy(p->fname,name);
	p->next=0;
	return p;
}
static address *copyaddress(const address *S)
{
		address *T;
		T = (address *)calloc(1, sizeof(address));
		T->ipaddress = (char *)calloc(sizeof(char), 20);
		strcpy(T->ipaddress, S->ipaddress);
		T->map = S->map;
		return T;
}

static holder *copyholder(const holder* B)
{
		holder* T;
		T=(holder*)calloc(1,sizeof(holder));
		T->ip=common.copyaddress(B->ip);
		while(B->next)
		{
		holder* temp=(holder*)calloc(1,sizeof(holder));
		temp->ip=common.copyaddress(B->next->ip);
		B=B->next;
		T->next=temp;
		T=T->next;
		}
		T->next=0;
		return T;
	}
static flist* copy_flist(const flist* A)
{
flist* newflist=(flist*)calloc(1,sizeof(flist));
holder* newholder=(holder*)calloc(1,sizeof(holder));
char* x=(char*)calloc(20,sizeof(char));
newholder->ip=(address*)calloc(1,sizeof(address));
strcpy(x,A->destination->ip->ipaddress);
newholder->ip->ipaddress=x;
newholder->ip->map=hash.map_node(x,get_size());
newholder->next=A->destination->next;
newflist->destination=newholder;
newflist->fid=hash.map_string(A->fname,get_size());
newflist->fname=A->fname;
newflist->next=0;
return newflist;
}
static void set_size(int x)
{
	size=x;
}
 static Circle* get_circle()
{
	if(flag)
	{
	return circle;
	}
	else
	return (Circle*)0;
}
 static void set_circle(Circle* p)
 {
	 if(!flag)
	 {
    circle=p;
	 }
 }
 static void set_debug(bool p)
 {
	 DEBUG=p;
 }
private:
	static Network* network;
	static Circle* circle;
	static node* local_node;
	static bool flag;
	static int size;
	static bool DEBUG;



} common;
#endif