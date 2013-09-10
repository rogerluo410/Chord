#ifndef COMMOND_H
#define COMMOND_H
#include <string>
using namespace std;
class Commond{
public:
	Commond(string &p=string(""))
	{
       input=p;
	}
	void commond_to_array();
	string& get_result(int i);
	int Commond::get_cid();
private:
	string input;
	string result[2];
};

#endif