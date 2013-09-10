#ifndef NETWORK_H
#define NETWORK_H
#include "node.h"
#include "ring.h"
class Network
{
public:
	Network(node* p)
	{
		arbitrariness=p;

	}
	bool join(node* p);
	bool leave(node* p);
	void update_others(node* p);//refresh
	void Network::replace_others(node* p);
    void init_finger_table(node* p);
	node* get_center();
	void set_center(node* p);
	bool add_file(char* filename,char* ip);
	bool find_file(char* filename);
	bool move_keys(node* p,flist* keys);
private:
	static node* arbitrariness;
};
#endif
