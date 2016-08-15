struct SEEMessage {
	unsigned int id[2];
	unsigned int ready;
	char text[100];
};
struct SEEMessage msg;
char *output = msg.text;

void
print(const char *s)
{
	while(*s != 0)
		*output++ = *s++;		
}

void
start()
{
	msg.ready = 0;
	msg.id[0] = 0x0BADC0DE;
	msg.id[1] = 0x0BADC0DE;
	
	print("Hello World from PPC-IOP!\n");
	
	msg.ready = 1;
	
	return 0;
}

