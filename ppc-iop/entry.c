// This buffer should be located right after our code
unsigned int buffer[1];

void
_entry()
{
	unsigned int data = 0;
	unsigned int *pbuffer = buffer;

	// Write a recognizable pattern, filling the entire deckard LUT
	// Writing this much will cause the cache to flush and data to become visible by the EE
	while ((unsigned int)pbuffer < 0x00AFFFFF) {
		*pbuffer++ = data;
		data += 0x11111111;
	}

	// Wait forever
	while(1){}
}

