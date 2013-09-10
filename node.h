#ifndef NODE_H
#define NODE_H
#include "define.h"
class node
{
public:
node::node();
node(address* ipaddress,int m);
bool leave();
bool join();
bool isalive();
void update_finger_table(address* p,int i);
void replace_finger_table(address* p,int i);
address* get_address();
address* get_predecessor();
address* get_successor();
int get_size();
void set_predecessor(address* p);
void set_alive(bool x);
void set_successor(address* p);
void set_finger_table(finger* f);
bool set_keys(flist* newkey);
void set_history(flist* f);
bool store_key(flist* newkey);
flist* get_history();
flist* get_keys();
finger* get_finger_table();
address* find_successor(int d);
address* find_predecessor(int d);
address* closest_preceding_successor(int d);
void print_node();
void print_holder(char* filename);
void print_keys();
holder* find_holder(char* filename);
void add_holder(char* filename,char* p);
void add_history(flist *oldquary);
bool node::find_history(char* filename);


private:
    int size;
 	address *ip;
	address *predecessor;
	flist* keys;
	flist* history;
	finger  *ftable;
	bool life;

};
#endif


