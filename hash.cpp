#include "define.h"
#include <string>
using namespace std;
int Hash::map_node(const char *ip,int size)//hash node of the IP
{
string all=string(ip);
string split=".";
int max=1 << size;
char* temp[4]={new char[3],new char[3],new char[3],new char[3]};
int number=0;
int sum=0;
int i,j;
for(i=0,j=0;((j=all.find(split,i))!=string::npos);i=j)
{
	strcpy(temp[number],all.substr(i,j-i).c_str());
	j=j+1;
	++number;
}
strcpy(temp[number],all.substr(i).c_str());
for(int i=0;i<4;i++)
{
sum=sum+atoi(temp[i]);
}
return sum%max;
}

int Hash::map_string(const char *name,int size)//hash
{
		int i = 0;
	int sum = 0;
	int max = 1 << size;
	for(i = 0; i < strlen(name); i++)
		sum += name[i];
	return (sum % max);
}
