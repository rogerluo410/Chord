#include "define.h"
#include "common.h"
#include "network.h"
#include <stdlib.h>
#include <iostream>
#include <string>

bool Common::flag=false;
int Common::size=4;
node* Common::local_node=new node();
Circle* Common::circle=new Circle();
Network* Common::network=new Network(Common::local_node);
bool Common::DEBUG=false;

