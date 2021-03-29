// A simple tool for use with AFL (https://lcamtuf.coredump.cx/afl/)
// which reads input from stdin and has no output. It is used for
// testing the basic parser behaviour

#include "../src/commsprotocol.h"

#include <stdio.h>

static unsigned int rxfunc(unsigned char* data,unsigned int maxsize)
{
    ssize_t ret = fread(data, 1, maxsize, stdin);
}

static void txfunc(const unsigned char* data,unsigned int size)
{
    
}

int main(int argc, char** argv)
{
	comms_context_t ctx;
	comms_init(&ctx);
	ctx.send = txfunc;
	ctx.receive = rxfunc;

	while(!feof(stdin))
	{
		comms_poll(&ctx);
	}

	return 0;
}