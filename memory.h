/**
 * Immortal Operating System - immortalOS 
 * 
 */

#ifndef MEMORY_H
#define	MEMORY_H

#define NEAR_MODEL
#define	MAX_HEAP_SIZE		0x200

#if defined(NEAR_MODEL)
#define	NEAR	near
#else
#define NEAR
#endif


#define	_MAX_SEGMENT_SIZE	0x7F
#define _MAX_HEAP_SIZE 	MAX_HEAP_SIZE-1

unsigned char * NEAR SRAMalloc(NEAR unsigned char nBytes);
void SRAMfree(unsigned char * NEAR pSRAM);
void SRAMInitHeap(void);

#endif	/* MEMORY_H */

