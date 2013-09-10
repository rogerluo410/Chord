/***********************************
* author:Pengfei M                  *
* date:2013.08.27                   *
* funtion: chord network            *
* email: pfming1989@gmail.com       *
* version 1.0                       *
*                                   *
************************************/
#include "define.h"
#include "network.h"
#include "node.h"
#include "common.h"
#include "commond.h"
#include "ring.h"
#include <iostream>
#include <string>
#include <stdlib.h>
void introduction()
{
system("cls");
cout<<"**************Whelcome to chord  system simulation system*****************"<<endl;
cout<<"**************program was built in 2013-08*************************"<<endl;
cout<<"**************system default ip in the network is 10.3.80.31***************"<<endl;
cout<<"**************commonds will be executed from this node,you can change it*********"<<endl;
cout<<"**************help please type \"help\" ****************************"<<endl;
}
void help()
{
system("cls");
cout<<"you can choose a selection from below,the ipaddress should be in ipv4 format"<<endl<<endl;
cout<<"1: creat a new chord ring";  
cout.width(50);
cout.fill('.');
cout<<"create size"<<endl;
cout<<"2: add new node in network";
cout.width(49);
cout.fill('.');
cout<<"addnode ipaddress"<<endl;
cout<<"3: remove node in network";
cout.width(50);
cout.fill('.');
cout<<"removenode ipaddress"<<endl;
cout<<"4: add new key in network";
cout.width(50);
cout.fill('.');
cout<<"addkey charname"<<endl;
cout<<"5: find key in network";
cout.width(53);
cout.fill('.');
cout<<"findkey charname"<<endl;
cout<<"6: print the routing process when find node";
cout.width(32);
cout.fill('.');
cout<<"findnode ipaddress"<<endl;
cout<<"7: show node's finger table,\"all\" for all nodes";
cout.width(28);
cout.fill('.');
cout<<"shownode ipaddress"<<endl;
cout<<"8: show node's flist talbe,\"all\" for all nodes";
cout.width(29);
cout.fill('.');
cout<<"showkey ipaddress"<<endl;
cout<<"9: change the recieving commond node";
cout.width(39);
cout.fill('.');
cout<<"change ipaddress"<<endl;
cout<<"10:open the debug mode";
cout.width(53);
cout.fill('.');
cout<<"debug  true(faslse)"<<endl;
cout<<"11:exit";
cout.width(68);
cout.fill('.');
cout<<"exit"<<endl;

}

string getcommond()
{
	string commond;
	getline(cin,commond);
	return commond;
}
void init(int size)
{
     address* ip=(address*)calloc(1,sizeof(address));
	 ip->ipaddress="10.3.80.1";
	 ip->map=hash.map_node(ip->ipaddress,size);
	 node* local=new node(ip,size);
	 Circle* c=new Circle(local);
	 c->set_ring(local);
	 Network* n=new Network(local);
	 common.set_flag(false);
	 common.set_size(size);
	 common.set_local(local);
     common.set_circle(c);
	 common.set_network(n);
	 common.set_flag(true);
	 n->join(local);
}
void execommond(Commond& commond)
{
int type=commond.get_cid();
string x1=commond.get_result(1);
	switch(type)
	{
				 case 0:
					 {
						 int size=atoi(x1.c_str());
						 if(size==0)
						 {
						 cout<<"incorrect size,please input the correct size"<<endl;
						 break;
						 }
						 else
						 {
						 init(size);
						 cout<<"the network initialized,the default receiving commond node is 10.3.80.31"<<endl;
						 if(common.get_debug())
						 {
						 cout<<"after initializing the first node have been added in the network"<<endl;
						 cout<<"the finger table is as follows"<<endl;
						 common.get_circle()->print_ring();
						 }
						 break;
						 }
					 }
				 case 1:
					
					 {
						 if(!x1.size())
						 {
						 cout<<"input error,please input the ipv4 of the node"<<endl;
						 break;
						 }
						 else
						 {
						 int size=common.get_size();			 
             			 address* z=(address*)calloc(1,sizeof(address));
						 char* temp=(char*)calloc(20,sizeof(char));
						 strcpy(temp,x1.c_str());
						 z->ipaddress=temp;
						 z->map=hash.map_node(z->ipaddress,size);
						 node* y=common.get_circle()->find_node(z->map);
						 if(y!=0)
						 {
							 cout<<"error,the node is already in the network or the node's id conficts with other added nodes"<<endl;
						     break;
						 }
						 node* newnode=new node(z,size);
						 newnode->set_alive(true);
						 bool result=false;
						 result=common.get_network()->join(newnode);
						 if(result==true)
						 {
							 cout<<"addnode complete!!"<<endl;
							 if(common.get_debug())
							 {
						     cout<<"after adding , the network nodes finger tables are as follows"<<endl;
                             common.get_circle()->print_ring();
							 }
						 }
						 break;
						 }
					 }
				 case 2:
					 {
						 address* p=(address*)calloc(1,sizeof(address));
						 int size=common.get_size();
						 char* temp=(char*)calloc(20,sizeof(char));
						 strcpy(temp,x1.c_str());
						 p->ipaddress=temp;
						 p->map=hash.map_node(p->ipaddress,size);
						 Circle* circle=common.get_circle();
						 node* removded=circle->find_node(p->map);
						 if(removded==0)
						 {
							 cout<<"the node is not in the network"<<endl;
							 break;
						 }
						 else
						 {
							 if(common.get_network()->leave(removded))
							 {
							 cout<<"removed complete!!"<<endl;
                             if(common.get_debug())
							 {
						     cout<<"after removing the network nodes fing table are as follows"<<endl;
                             common.get_circle()->print_ring();
							 }
							 }
							 else
							 {
						     cout<<"error in removing"<<endl;
							 }
					         break;
						 }
					 }
				 case 3:
			
					 {
			 if(!x1.size())
						 {
						 cout<<"input error,please input the key name"<<endl;
						 break;
						 }
						 else
						 {
						 int size=common.get_size();
						 Network* network=common.get_network();
						 char* ip=network->get_center()->get_address()->ipaddress;
						 char* temp=(char*)calloc(50,sizeof(char));
						 strcpy(temp,x1.c_str());
						 char* filename=temp;
						 bool result=network->add_file(filename,ip);
						 if(result)
						 {
						 cout<<"addkey complete!!"<<endl;
						 break;
						 }
						 else
						 {
						 cout<<"addkey error"<<endl;
						 break;
						 }
			              }
					 }
				 case 4:
				
					 {
						 int size=common.get_size();
						 Network* network=common.get_network();
                         char* temp=(char*)calloc(50,sizeof(char));
						 strcpy(temp,x1.c_str());
						 char* filename=temp;
						 network->find_file(filename);
					 break;
					 }
				 case 5:
					 {

                    char* temp=(char*)calloc(50,sizeof(char));
				     strcpy(temp,x1.c_str());
					 int id=hash.map_node(temp,common.get_size());
                     Network* network=common.get_network();
					 node* sourse=network->get_center();
					 bool x=common.get_debug();
                     common.set_debug(true);
					 address* result=sourse->find_successor(id);
                     common.set_debug(x);
					 cout<<result->ipaddress<<endl;
					 break;
					 }
				 case 6:
					 {
						int x=strcmp("all",x1.c_str());
						if(x==0)
						{
                             common.get_circle()->print_ring();
						}
						else
						{
                          char* temp=(char*)calloc(50,sizeof(char));
						  strcpy(temp,x1.c_str());
						  int pid=hash.map_node(temp,common.get_size());
						  node* p=common.get_circle()->find_node(pid);
						  if(p!=0)
						  {
						  int m=strcmp(temp,p->get_address()->ipaddress);
						  if(m==0)
						  p->print_node();
						  else
						  cout<<"the address is not right"<<endl;
						  }
						  else
						  {
						 cout<<"not find the node"<<endl;
						  }
						}
						 break;
					 }
				 case 7:
					 {
						int x=strcmp("all",x1.c_str());
						if(x==0)
						{
                             common.get_circle()->print_keys();
						}
						else
						{
                          char* temp=(char*)calloc(50,sizeof(char));
						  strcpy(temp,x1.c_str());
						  int pid=hash.map_node(temp,common.get_size());
						  node* p=common.get_circle()->find_node(pid);
				         if(p!=0)
						  {
						  int m=strcmp(temp,p->get_address()->ipaddress);
						  if(m==0)
						  p->print_keys();
						  else
						  cout<<"the address is not right"<<endl;
						  }
						  else
						  {
						 cout<<"not find the key"<<endl;

						  }
						}
					 break;
					 }
			    case 8:
					 {
                          char* temp=(char*)calloc(50,sizeof(char));
						  strcpy(temp,x1.c_str());
						  int pid=hash.map_node(temp,common.get_size());
						  node* p=common.get_circle()->find_node(pid);
						  if(p!=0)
						  {
						  int m=strcmp(temp,p->get_address()->ipaddress);
						  if(m==0)
						    {
						 	  common.get_network()->set_center(p);
							  cout<<"change complete!"<<endl;
							  break;
						     }
						  else
						     {
						  cout<<"the address is not right"<<endl;
						  break;
						     }
						  }
						  else
						  {
						 cout<<"not find the node"<<endl;
						 break;
						  }
						}
			
			    case 9:
					 {
				  	 help();
					 break;
					 }
	            case 10:
					 {
					 if(!x1.compare("true"))
					 {
				     common.set_debug(true);
					 cout<<"now debug mode is:"<<"true"<<endl;
					 }
					 else if(!x1.compare("false"))
					 {
					 common.set_debug(false);			 
					 cout<<"now debug mode is:"<<"false"<<endl;
					 }
					 else
					 {		 
					 cout<<"debug set error"<<endl;
					 }
					 break;
					 }
			 default:
					 {
					 cout<<"unrecognized commond"<<endl;
					 break;
					 }

}
}
int main()
{
introduction();
string q=getcommond();
while(q.size()&&q.compare("exit"))
{
Commond commond=Commond(q);
commond.commond_to_array();
execommond(commond);
q=getcommond();
}
if(q.compare("exit")==0)
{
	cout<<"goodbye"<<endl;
	system("pause");
}

return 0;
}