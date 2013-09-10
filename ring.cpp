#include "ring.h"
#include "common.h"
#include <iostream>
using namespace std;
rnode* Circle::ring=(rnode*)calloc(1,sizeof(rnode));
int Circle::number=1;
node* Circle::find_node(address* p)
{
if(ring->pid==p->map)
return ring->chord_node;
else
  {
rnode* x=ring;
while(ring->next->pid!=x->pid)
    {
ring=ring->next;
if(ring->pid==p->map)
return ring->chord_node;
    }
return (node*)0;
  }
}
node* Circle::find_node(int x)
{
if(ring->pid==x)
return ring->chord_node;
else
  {
rnode* p=ring;
while(ring->next->pid!=p->pid)
    {
ring=ring->next;
if(ring->pid==x)
return ring->chord_node;
    }
return (node*)0;
  }
}
rnode* Circle::get_ring()
{
return ring;
}
void Circle::set_ring(node* p)
{
rnode* newnode=(rnode*)calloc(1,sizeof(rnode));
newnode->size=p->get_size();
newnode->pid=p->get_address()->map;
newnode->chord_node=p;
newnode->next=newnode;
ring=newnode;
number=1;
}

bool Circle::remove_node(node* p)//remove offline node
{
Network* network=common.get_network();
if(common.get_debug())
cout<<"the node:"<<p->get_address()->map<<" is being removed in the ring"<<endl;
if(find_node(p->get_address())!=0)
{
p->set_alive(false);
address* t =p->get_address();
if(ring->next->pid==ring->pid)
{
	cout<<"the only node can't be moved"<<endl;
	return false;
}
if(p->get_address()->map==network->get_center()->get_address()->map)
{
	cout<<"the current receiving commond node can't be removed"<<endl;
	return false;
}
if(ring->next->pid==t->map)
  {
	rnode* temp=ring->next;
	ring->next=temp->next;
	return true;
  }
else
    {
rnode* x=ring->next;
while(ring->next->next->pid!=x->pid)
        {
ring=ring->next;
if(ring->next->pid==t->map)
            {
	rnode* temp=ring->next;
	ring->next=temp->next;
            }
         }
--number;
if(common.get_debug())
cout<<"a node is removed in the ring"<<endl;
return true;
     }
}
else
    {
cout<<"error in remove_node ,please create a chord Network first"<<endl;
system("exit");
return false;
    }
}

bool Circle::add_node(node* p)
{
if(common.get_debug())
cout<<"new node is being add in the ring"<<endl;
if(find_node(p->get_address())==0)
{
p->set_alive(true);
rnode* newnode=(rnode*)calloc(1,sizeof(rnode));
newnode->size=p->get_size();
newnode->pid=p->get_address()->map;
newnode->chord_node=p;
if(ring->next==0)
{
cout<<"error in add_node ,please create a chord Network first"<<endl;
system("exit");
return false;
}
else
{
if(common.get_debug())
cout<<"the ring first node ip is "<<ring->chord_node->get_address()->ipaddress<<" map is "<<ring->chord_node->get_address()->map<<endl;
}
rnode* temp=ring->next;
if(number>1)
{
if(common.get_debug())
cout<<"the ring next node ip is "<<temp->chord_node->get_address()->ipaddress<<" map is "<<temp->chord_node->get_address()->map<<endl;
}
newnode->next=temp;
ring->next=newnode;
++number;
if(common.get_debug())
{
cout<<"after adding a newnode is added in the ring"<<endl;
cout<<"this node ip is "<<newnode->chord_node->get_address()->ipaddress<<"and map is "<<newnode->chord_node->get_address()->map<<endl;
}
return true;
}
else
{
	cout<<"this node have already in the ring";
	return true;
}

}
int Circle::get_number()
{
return number;
}
void Circle::print_ring()//print routing table
{
	if(ring->size==0)	
	{
		cout<<"please create a chord network first"<<endl;
	    return;
	}
	if(ring->next==ring)
	{
	ring->chord_node->print_node();
	}
	else
	{
	rnode* head=ring;
	while(ring->next->pid!=head->pid)
	{
 	    ring->chord_node->print_node();
		ring=ring->next;
	}
        ring->chord_node->print_node();
	}
}
void Circle::print_keys()
{
	if(ring->size==0)	
	{
		cout<<"please create a chord network first"<<endl;
	    return;
	}
	if(ring->next==ring)
	{
	ring->chord_node->print_keys();
	}
	else
	{
	rnode* head=ring;
	while(ring->next->pid!=head->pid)
	{
 	    ring->chord_node->print_keys();
		ring=ring->next;
	}
        ring->chord_node->print_keys();
	}


}