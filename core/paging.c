#include "kernel/paging.h"
#include "kernel/stdtypes.h"

extern uint32_t kernel_heap_addr;

//macros for bit testing

#define index_from_bit(a) (a/32)
#define offset_from_bit(a) (a%32)
uint32_t *frames;
uint32_t nframes;


//static frame utility function
//implementing bit vector for paging
static void set_frame(uint32_t frame_addr){
	//convert frame addr to frame index [4KB]
	uint32_t frame = frame_addr/0x1000;
	uint32_t index = index_from_bit(frame);
	uint32_t offset = offset_from_bit(frame);
	frames[index] |= (0x1 << offset);
}

static void clear_frame(uint32_t frame_addr){

	uint32_t frame = frame_addr/0x1000;
	uint32_t index = index_from_bit(frame);
	uint32_t offset = offset_from_bit(frame);
	frames[index] &= ~(0x1 << offset);
}

static uint32_t test_frame(uint32_t frame_addr){
	
	uint32_t frame = frame_addr/0x1000;
	uint32_t index = index_from_bit(frame);
	uint32_t offset = offset_from_bit(frame);
	return (frames[index] & (0x1<<offset));
}

static uint32_t first_frame(){
	uint32_t i,j,test;

	for(i=0; i<index_from_bit(nframes); i++){
		//check whether no frame exist
		if(frames[i]!=0xffffffff){
			//if exist check for that one frame
			for(j=0;j<32;j++){
				test = 0x1<<j;
				if(!(frames[i]&test)){
					return i*(32)+j;
				}
			}
		}
	}
}


//frame allocator functions.
