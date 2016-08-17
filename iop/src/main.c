#include "types.h"
#include "defs.h"
#include "irx.h"
#include "stdio.h"
#include "thbase.h"


#define MODNAME "ppc_trigger"
#define M_PRINTF(format, args...)	\
	printf(MODNAME ": " format, ## args)
#define TRIGGER_ADDR 0xBF801000

IRX_ID(MODNAME, 1, 0);

#define BLOCK_SIZE	(64*1024)
#define BLOCK_SIZE32	(BLOCK_SIZE / 4)
unsigned int block[BLOCK_SIZE32];

static void thread(void* param)
{
	unsigned int data = 0;
	unsigned int i;

	// Wait so the EE will see this module is loaded.
	// Otherwise is we hang the IOP, the EE will hang too
	DelayThread(500 * 1000);

	while (1) {
		// Flush PPC write cache?
		// Write 64KiB
		for (i=0; i<BLOCK_SIZE32; i++)
			block[i] = data;

		// Flush PPC read cache?
		// Read 64KiB
		for (i=0; i<BLOCK_SIZE32; i++)
			data += block[i];

		// Read from trigger addr
		// This will trigger our custom PPC-IOP code
		// If the PPC code does not return we will never see this message
		M_PRINTF("trigger value = 0x%x\n", *((vu32 *)TRIGGER_ADDR));

		DelayThread(2 * 1000 * 1000);
	}
}

int _start(int argc, char *argv[])
{
	iop_thread_t param;
	int th;

	/*create thread*/
	param.attr	= TH_C;
	param.thread	= thread;
	param.priority	= 40;
	param.stacksize	= 0x1000;
	param.option	= 0;

	th = CreateThread(&param);
	if (th > 0) {
		StartThread(th, 0);
		return 0;
	} else  {
		M_PRINTF("failed to create thread\n");
		return 1;
	}
}
