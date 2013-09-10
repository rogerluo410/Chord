#include "commond.h"
#include <string>
#include <iostream>
using namespace std;
int Commond::get_cid()
{
if(result[0]=="create")
return 0;
else if(result[0]=="addnode")
return 1;
else if(result[0]=="removenode")
return 2;
else if(result[0]=="addkey")
return 3;
else if(result[0]=="findkey")
return 4;
else if(result[0]=="findnode")
return 5;
else if(result[0]=="shownode")
return 6;
else if(result[0]=="showkey")
return 7;
else if(result[0]=="change")
return 8;
else if(result[0]=="help")
return 9;
else if(result[0]=="debug")
return 10;
return -1;


}
void Commond::commond_to_array()
{
size_t i,j;
i=input.find(" ",0);
if(i!=string::npos)
{
result[0]=input.substr(0,i);
result[1]=input.substr(i+1);
}
else
{
result[0]=input.substr(0);
result[1]=string("");
}
}
string& Commond::get_result(int i)
{
	if(i>1)		
	{
		system("exit");
	}
	else
	return result[i];
}
