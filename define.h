#ifndef DEFINE_H
#define DEFINE_H
typedef struct finger finger;
typedef struct address address;
typedef struct holder holder;
typedef struct flist flist;

struct finger{
	int      start;
	int      end;
	address *succ;
};
struct address{
	char    *ipaddress;
	int      map;
};

struct holder{
	address* ip;
	holder *next;
};
struct flist{
	char    *fname;
	int      fid;
	holder   *destination;
	flist   *next;
};
static class Hash
{
public:
	static int map_node(const char *ip,int size);
	static int map_string(const char *name,int size);
}  hash;

#endif


