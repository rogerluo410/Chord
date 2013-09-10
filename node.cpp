/*Node
**basic element of chord ring
**  email:  pfming1989@gmail.com
*/
#include "define.h"
#include "node.h"
#include "network.h"
#include "common.h"
#include "ring.h"
#include <string>
#include <iostream>
using namespace std;
node::node(address* ipaddress,int m)
{
ip=ipaddress;
size=m;
int MAX=1<<m;
ftable=(finger*)calloc(m+1,sizeof(finger));
for(int i=1;i<=m;i++)
{
int j=i-1;
int k=1<<i;
int temp=1<<j;
ftable[i].start=(ip->map+temp)%MAX;
ftable[i].end=(ip->map+k)%MAX;
ftable[i].succ=0;
}
predecessor=0;
keys=0;
history=0;
life=false;
} 
node::node()
{
address* first=(address*)calloc(1,sizeof(address));
first->ipaddress="127.0.0.1";
first->map=hash.map_node(first->ipaddress,4);
int m=4;
size=4;
ip=first;
int MAX=1<<m;
ftable=(finger*)calloc(m,sizeof(finger));
for(int i=1;i<=m;i++)
{
ftable[i].start=(ip->map+1<<i-1)%MAX;
ftable[i].end=(ip->map+1<<i)%MAX;
ftable[i].succ=0;
}

predecessor=0;
keys=0;
history=0;
life=false;
} 
address* node::get_address()
{
	return ip;
}

address* node::get_predecessor()
{
	return predecessor;
}

finger* node::get_finger_table()
{
	return ftable;
}

address* node::get_successor()
{
	finger* table=get_finger_table();
	return table[1].succ;
}

flist* node::get_keys()
{
	return keys;
}
int node::get_size()
{
	return size;
}

void node::set_successor(address* p)
{
finger* table=get_finger_table();
table[1].succ=(address*)calloc(1,sizeof(address));
table[1].succ->ipaddress=p->ipaddress;
table[1].succ->map=p->map;
}

void node::set_predecessor(address* p)
{
predecessor=(address*)calloc(1,sizeof(address));
predecessor->ipaddress=p->ipaddress;
predecessor->map=p->map;
}

void node::set_finger_table(finger* f)
{

	ftable=f;

}

bool node::set_keys(flist* newkey)
{
	
	flist* p=(flist*)calloc(1,sizeof(flist));
	p->fname=(char*)calloc(50,sizeof(char));
	strcpy(p->fname,newkey->fname);
	p->fid=newkey->fid;
	p->destination=common.copyholder(newkey->destination);
	p->next=0;
	keys=p;
	if(keys!=0)
		return true;
	else
		return false;
}

void node::set_history(flist* f)
{
history=f;
}
void node::set_alive(bool p)
{
	life=p;
}

void node::replace_finger_table(address* p,int i)
{
if(common.get_debug())
cout<<"node: "<<ip->map<<" is beginning to update other tables whose finger succ might be this removed node"<<endl;
Circle* circle=common.get_circle();
bool temp=(p->map==ftable[i].succ->map);
address* after=circle->find_node(p)->get_successor();

if(temp)
{
if(common.get_debug())
{
cout<<"in the node: "<<ip->map<<"'s updating"<<endl;
cout<<"the remove node: "<<p->map<<" is node: "<<ip->map<<"'s finger["<<i<<"].succ:"<<ftable[i].succ->map<<endl;
cout<<"now finger ["<<i<<"].succ have been set to "<<after->map<<endl;
cout<<"after updating the node: "<<ip->map<<" finger table is as follows"<<endl;
}
ftable[i].succ->map=after->map;
if(common.get_debug())
print_node();
}
else
{
	if(common.get_debug())
	{
	cout<<"in the node: "<<ip->map<<"'s updating"<<endl;
	cout<<"the remove node is not on this node's finger table"<<endl;
	print_node();
	}
}
node* pre=circle->find_node(predecessor);
if(pre->get_address()->map!=after->map)
{
if(common.get_debug())
cout<<"now updading his pre node"<<endl;
pre->replace_finger_table(p,i);
}
else
{
	if(common.get_debug())
	{
	cout<<"the pre node:"<<pre->get_address()->map<<" is exceed"<<after->map<<" stop!"<<endl;
	print_node();
	}
}

}
void node::update_finger_table(address* p,int i)
{
if(common.get_debug())
cout<<"node: "<<ip->map<<" is beginning to update his finger table for which finger succ might be the newnode"<<endl;
Circle* circle=common.get_circle();
bool temp=common.lies_in(p->map,ftable[i].start,ftable[i].succ->map)||(p->map==ftable[i].start);
if(temp)
{
if(common.get_debug())
{
cout<<"in the node: "<<ip->map<<"'s updating"<<endl;
cout<<"the new node: "<<p->map<<" is between node: "<<ip->map<<"'s finger["<<i<<"].start:"<<ftable[i].start<<" and the finger succ node:"<<ftable[i].succ->map<<endl;
cout<<"now finger ["<<i<<"].succ have been set to "<<p->map<<endl;
cout<<"after updating the node: "<<ip->map<<" is as follows"<<endl;
}
ftable[i].succ=common.copyaddress(p);
if(common.get_debug())
print_node();
}
else
{
    if(common.get_debug())
	{
	cout<<"in the node: "<<ip->map<<"'s updating"<<endl;
	cout<<"the new node: "<<p->map<<" is not between node: "<<ip->map<<"'s finger["<<i<<"].start:"<<ftable[i].start<<" and the finger succ node:"<<ftable[i].succ->map<<endl;
	}
}
node* pre=circle->find_node(predecessor);
if(pre->get_address()->map!=p->map)
{
if(common.get_debug())
cout<<"now updading his pre node"<<endl;
pre->update_finger_table(p,i);
}
else
{
	if(common.get_debug())
	cout<<"the pre node:"<<pre->get_address()->map<<" is exceed"<<p->map<<" stop!"<<endl;
}

}
bool node::isalive()
{
	return life;
}

address* node::find_successor(int d)
{
if(common.get_debug())
cout<<"the node: "<<get_address()->ipaddress<<" is finding successor"<<endl;
Circle* circle=common.get_circle();
address* N=find_predecessor(d);
node* p=circle->find_node(N);
if(common.get_debug())
cout<<"the node: "<<N->ipaddress<<" return his successor"<<endl;
return p->get_successor();
}

address* node::find_predecessor(int d)
{
if(common.get_debug())
cout<<"the node: "<<get_address()->ipaddress<<" is finding predecessor"<<endl;
Circle* circle=common.get_circle();
address* N=get_address();
int n;
int m;
while(true)
  {
node* p=circle->find_node(N);
n=p->get_address()->map;
m=p->get_successor()->map;
if(common.lies_in(d,n,m)||(d==m))
     {                                                                                 
	if(common.get_debug())
	       {
	cout<<"the node:"<<p->get_address()->ipaddress<<" return the get_predecessor message,"<<endl;
	cout<<"predecessor has been found"<<endl;
	       }
	return N;
     }
else
    {
address *M=p->closest_preceding_successor(d);
if((N->map==M->map)||(common.lies_in(d,N->map,M->map))||(d==M->map))
          {
if(common.get_debug())
               {
cout<<"the node:"<<p->get_address()->ipaddress<<" send find get_predecessor message to node: "<<M->ipaddress<<endl;
cout<<"node: "<<M->ipaddress<<" return his predecessor"<<endl;
                }
return circle->find_node(M)->get_predecessor(); 
          }
else
          {
			  if(common.get_debug())
			  cout<<"the node:"<<p->get_address()->ipaddress<<" send the get_predecessor message to node:"<<M->ipaddress<<endl;
N=M;
          }
     }
  }
}


address* node::closest_preceding_successor(int d)
{
int n=get_address()->map;
finger *p=get_finger_table();
if((common.lies_in(d,p[size].start,p[size].end))||(d==p[size].start)||(d==p[size].end))
{
if(common.get_debug())
        {
cout<<"the node:"<<get_address()->ipaddress<<"find node from his closest_preceding_successor"<<endl;
cout<<"it get the node: "<<p[size].succ->ipaddress<<"and return "<<endl;
         }
return p[size].succ;
}
for(int i=size-1;i>=1;i--)
{
if(common.lies_in(d,p[i].start,p[i].end)||d==p[i].start)
{
if(common.get_debug())
        {
cout<<"the node:"<<get_address()->ipaddress<<"find node from his closest_preceding_successor"<<endl;
cout<<"it get the node: "<<p[i].succ->ipaddress<<"and return "<<endl;
         }
return p[i].succ;
}
}
return get_address();
}
void node::print_node()
{
	finger* table=get_finger_table();
	cout<<"***********************************"<<endl;
	cout<<"**node ip: "<<ip->ipaddress<<"*node id: "<<ip->map<<"**"<<endl;
	cout<<"*predecessor: "<<get_predecessor()->map<<"     successor: "<<table[1].succ->map<<endl;
	cout<<"*interval               succ"<<endl;
	for(int i=1;i<=get_size();i++)
	{
	    cout<<"*"<<"["<<table[i].start<<"-"<<table[i].end<<")";
		cout.fill('.');
		cout.width(20);
		cout<<table[i].succ->map<<endl;
	}
	cout<<"***********************************"<<endl;

}
void node::print_holder(char* filename)
{

holder* p=find_holder(filename);
if(p!=0)
{
holder* hhead=p;
cout<<"The file key have been stored in the node : "<<ip->ipaddress<<endl;
cout<<"The download list is as follows"<<endl;
cout<<"filename: "<<filename<<endl;
for(;p;p=p->next)
{
cout<<p->ip->ipaddress<<endl;
}
p=hhead;
}
else
{
	cout<<"this file has not been added"<<endl;
}
}

void node::print_keys()
{
flist* head=keys;
while(keys!=0)
{
cout.setf(ios_base::left);
cout.width(20);
cout<<keys->fname;
cout.unsetf(ios_base::left);
cout<<":   ";
holder* p=keys->destination;
holder* hhead=p;
for(;p;p=p->next)
{
cout<<p->ip->ipaddress;
cout<<",";
}
cout<<endl;
p=hhead;
keys=keys->next;
}
keys=head;
}
bool node::store_key(flist* newkey)
{
if(keys==0)
{
	return set_keys(newkey);
}
holder* x=find_holder(newkey->fname);
if(x!=0)
{
holder* hhead=x;
char* temp=newkey->destination->ip->ipaddress;
for(;x->next;x=x->next)
{
if(strcmp(x->ip->ipaddress,temp)==0)
  {
cout<<"the file is already be added"<<endl;
return false;
  }
}
if(strcmp(x->ip->ipaddress,temp)==0)
  {
cout<<"the file is already be added"<<endl;
return false;
  }
holder* newholder=(holder*)calloc(1,sizeof(holder));
char* newip=(char*)calloc(50,sizeof(char));
newholder->ip=(address*)calloc(1,sizeof(address));
strcpy(newip,temp);
newholder->ip->ipaddress=newip;
newholder->ip->map=hash.map_node(newip,get_size());
newholder->next=0;
x->next=newholder;
x=hhead;
return true;
}
else
{
	flist* head=keys;
	while(keys->next!=0)
	{
		keys=keys->next;
	}
	flist* p=(flist*)calloc(1,sizeof(flist));
	char* temp=(char*)calloc(50,sizeof(char));
	strcpy(temp,newkey->fname);
	p->fname=temp;
	p->fid=newkey->fid;
	p->destination=common.copyholder(newkey->destination);
	p->next=0;
	keys->next=p;
	keys=head;
	return true;
}

}
holder* node::find_holder(char* filename)
{
 flist* head=keys;
while(keys!=0)
{
	int r=strcmp(keys->fname,filename);
	if(r==0)
	{
		flist* p=keys;
		keys=head;
		return p->destination;

	}
	else
	{
     keys=keys->next;
	}
	
}
keys=head;
return (holder*)0;
}

void node::add_holder(char* filename,char* p)
{

	holder* temp=find_holder(filename);
	holder* hhead=temp;
	while(temp->next)
		temp=temp->next;
	holder* newholder=(holder*)calloc(1,sizeof(holder));
	newholder->ip=(address*)calloc(1,sizeof(address));
	strcpy(newholder->ip->ipaddress,p);
	newholder->ip->map=hash.map_node(p,get_size());
	newholder->next=0;
	temp->next=newholder;
	temp=hhead;


}

void node::add_history(flist* oldquary)
{
	
if(history==0)
{
	set_history(oldquary);
}
else
{
flist* head=history;
int i=1;
for(;(history->next);history=history->next,i++)
{
if(strcmp(history->fname,oldquary->fname)==0)
  {
    return;
  }
}
if(strcmp(history->fname,oldquary->fname)==0)
  {
return;
  }
if(i<4)
{
history->next=common.copy_flist(oldquary);
history=head;
return;
}
else
{
history->next=common.copy_flist(oldquary);
history=head->next;
return ;
 }
}
}

bool node::find_history(char* filename)
{
flist* head=history;
while(history!=0)
{
	int r=strcmp(history->fname,filename);
if(r==0)
{
holder* p=history->destination;
holder* hhead=p;
cout<<"The file key have been find in history:"<<endl;
cout<<"The download list is as follows"<<endl;
cout<<"filename: "<<filename<<endl;
for(;p;p=p->next)
{
cout<<p->ip->ipaddress<<endl;
}
p=hhead;
history=head;
return true;
}
else
{
   history=history->next;
}
	
}
history=head;
return false;
}