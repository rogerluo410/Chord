#include "define.h"
#include "network.h"
#include "common.h"
#include "ring.h"
#include <string>
#include <iostream>
using namespace std;
node* Network::arbitrariness;
node* Network::get_center()
{
	return  arbitrariness;
}
void Network::set_center(node* p)
{
    arbitrariness=p;
}
bool Network::join(node* x)//join the ring
{

if(x->isalive())
{
if(common.get_debug())
{
cout<<"now a newnode is joing......."<<endl;
cout<<"the node ip is "<<x->get_address()->ipaddress<<" "<<"and the map is "<<x->get_address()->map<<endl;
}
bool r=common.get_circle()->add_node(x);
if(r)
{
init_finger_table(x);
update_others(x);
return true;
}
else
{
	cout<<"joining error"<<endl;
	return false;
}
}
else
{
	if(common.get_debug())
	{
cout<<"now the Network first node is joing......."<<endl;
cout<<"the network size is 2^"<<x->get_size()<<endl;
cout<<"the first node ip is "<<x->get_address()->ipaddress<<" "<<"and the map is "<<x->get_address()->map<<endl;
	}
x->set_alive(true);
int size=arbitrariness->get_size();
finger* temp=(finger*)calloc(size,sizeof(finger));
for(int i=1;i<=size;i++)
{
	temp[i].start=(arbitrariness->get_finger_table())[i].start;
	temp[i].end=(arbitrariness->get_finger_table())[i].end;
	temp[i].succ=common.copyaddress(arbitrariness->get_address());
}
arbitrariness->set_predecessor(arbitrariness->get_address());
arbitrariness->set_finger_table(temp);
if(common.get_debug())
{
cout<<"after the first node join,the first node's finger table be follows"<<endl;
x->print_node();
}
return true;
}

}
bool Network::leave(node* p)
{
	if(common.get_circle()->get_ring()->size==0)
	{
		cout<<"please first create a chord network"<<endl;
		return false;
	}
	Circle* circle=common.get_circle();
	address* before=p->get_predecessor();
	address* after=p->get_successor();
	circle->find_node(before)->set_successor(after);
	circle->find_node(after)->set_predecessor(before);
	replace_others(p);
	move_keys(circle->find_node(after),p->get_keys());
    return circle->remove_node(p);

}
void Network::init_finger_table(node* p)
{
	if(common.get_debug())
	cout<<"now the network is init_finger_table of new node "<<p->get_address()->ipaddress<<endl;
	Circle* circle=common.get_circle();
	int size=arbitrariness->get_size();
	finger* p_table=p->get_finger_table();
	address* temp=(address*)calloc(1,sizeof(address));
	if(common.get_debug())
	{
	cout<<"first the known node "<<arbitrariness->get_address()->map<<" find the newnode:"<<p->get_address()->map<<"'s fing[1].start's successor"<<endl;
	cout<<"to know where should the new node be inserted "<<endl;
	}
	temp=arbitrariness->find_successor(p_table[1].start);
	if(common.get_debug())
	cout<<"it finds the successor of fing[1].start should be "<<temp->map<<endl;
	p->set_successor(temp);
	if(common.get_debug())
	cout<<"setting the new node:"<<p->get_address()->map<<"'s successor as "<<temp->map<<endl;
	node* p1=circle->find_node(p->get_successor());
	p->set_predecessor(p1->get_predecessor());  
	if(common.get_debug())
	cout<<"the new node's predecessor now should be his successor's old predecessor: "<<p1->get_predecessor()->map<<endl;
	p1->set_predecessor(p->get_address()); 
	if(common.get_debug())
	{
	cout<<"the new node's successor:"<<temp->map<<" it's new predecessor should be the newnode:"<<p->get_address()->map<<endl;
    cout<<"now the newnode updating his finger[2]-[size]......"<<endl;
	}
	for(int i=1;i<size;i++)
	{
		if(common.lies_in(p_table[i+1].start,p->get_address()->map,p_table[i].succ->map)||(p_table[i+1].start==p->get_address()->map)||(p_table[i+1].start==p_table[i].succ->map))
		  p_table[i+1].succ=common.copyaddress(p_table[i].succ);
	   else
	    {
			p_table[i+1].succ=common.copyaddress(arbitrariness->find_successor(p_table[i+1].start));

	    }
	}
	if(common.get_debug())
	{
	cout<<"after updating,the newnode finger is as follows:"<<endl;
	p->print_node();
	}

}
void Network::replace_others(node* p)

{
	address* before=p->get_predecessor();
	address* after=p->get_successor();
	if(common.get_debug())
	cout<<"now it is beginningg to update other nodes in the ring after node: "<<p->get_address()->map<<" have leaved"<<endl;
 	Circle* circle=common.get_circle();
	int size=p->get_size();
      for(int i=1;i<=size;i++)
	  {
		  if(common.get_debug())
	     cout<<"finding the  "<<i<<"th  finger table the possible other nodes whose finger["<<i<<"].succ may be the removenode.."<<endl;
		 int n=p->get_address()->map;
		 int temp=1<<(i-1);
		 int possible=n-temp;
		 if(possible<0)
		possible=possible+(1<<size);
		 if(common.get_debug())
		cout<<"the  first possible node in  "<<i<<"th finger table node is   "<<possible<<endl;
		
		address* y;

		if(circle->find_node(possible)!=0)
		{
			node * x=circle->find_node(possible);
			if(common.get_debug())
			cout<<"the possible node's predecessor is "<<x->get_address()->map<<endl;
			x->replace_finger_table(p->get_address(),i);
			
		}
		else
		{
		y=circle->find_node(before)->find_predecessor(possible);
		if(common.get_debug())
		cout<<"the possible node's predecessor is "<<y->map<<endl;
		node* p1=circle->find_node(y);
		p1->replace_finger_table(p->get_address(),i);
		}
	  }


}
void Network::update_others(node* p)
{   
	if(common.get_debug())
	cout<<"now the new node is beginningg to update other nodes in the ring..........."<<endl;
	Circle* circle=common.get_circle();
	int size=p->get_size();
      for(int i=1;i<=size;i++)
	  {
	     if(common.get_debug())
	     cout<<"finding the  "<<i<<"th  finger table the possible other nodes whose finger["<<i<<"].succ may be the newnode.."<<endl;
		 int n=p->get_address()->map;
		 int temp=1<<(i-1);
		 int possible=n-temp;
		 if(possible<0)
		possible=possible+(1<<size);
	    if(common.get_debug())
		cout<<"the  first possible node in  "<<i<<"th finger table node is   "<<possible<<endl;
		
		address* y;

		if(circle->find_node(possible)!=0)
		{
			node * x=circle->find_node(possible);
			if(common.get_debug())
			cout<<"the possible node's predecessor is "<<x->get_address()->map<<endl;
			x->update_finger_table(p->get_address(),i);
			
		}
		else
		{
		y=p->find_predecessor(possible);
        if(common.get_debug())
		cout<<"the possible node's predecessor is "<<y->map<<endl;
		node* p1=circle->find_node(y);
		p1->update_finger_table(p->get_address(),i);
		}
	  }

}

bool Network::add_file(char* filename,char* ip)
{
	if(common.get_circle()->get_ring()->size==0)
	{
		cout<<"please first create a chord network"<<endl;
		return false;
	}
	int size=common.get_size();
	int fid=hash.map_string(filename,size);
	node* p=arbitrariness;
	Circle* circle=common.get_circle();
	address* ipa=common.initaddress(ip,size);
	flist* newkey=common.initkeys(filename,ipa);
	address* result=p->find_successor(fid);
	node* save=circle->find_node(result);
	return save->store_key(newkey);

}
bool Network::find_file(char* filename)
{
	if(common.get_circle()->get_ring()->size==0)
	{
		cout<<"please first create a chord network"<<endl;
		return false;
	}
	bool h=arbitrariness->find_history(filename);
	if(h)
	return true;
	int size=arbitrariness->get_size();
	int fid=hash.map_string(filename,size);
	node* p=arbitrariness;
	Circle* circle=common.get_circle();
	address* result=p->find_successor(fid);
	node* save=circle->find_node(result);
    holder* temp=save->find_holder(filename);
	if(temp!=0)
	{   
		flist* quary=(flist*)calloc(1,sizeof(quary));
		holder* oldquary=(holder*)calloc(1,sizeof(holder));	
		char* ipname=(char*)calloc(20,sizeof(char));
		char* fname=(char*)calloc(50,sizeof(char));
		strcpy(ipname,temp->ip->ipaddress);
		strcpy(fname,filename);
		oldquary->ip=(address*)calloc(1,sizeof(address));
		oldquary->ip->ipaddress=ipname;
		oldquary->ip->map=hash.map_node(ipname,common.get_size());
		oldquary->next=temp->next;
		quary->destination=oldquary;
		quary->fid=hash.map_string(filename,common.get_size());
		quary->fname=fname;
		quary->next=0;
		arbitrariness->add_history(quary);
		save->print_holder(filename);
		return true;

	}
	else
	{
	cout<<"the file has not been added"<<endl;
	return false;
	}

}


bool Network::move_keys(node* p,flist* keys)
{
	if(keys==0)
		return true;
	else
	{
		while(keys!=0)
		{
			p->store_key(keys);
			keys=keys->next;
		}
		return true;
	}

}