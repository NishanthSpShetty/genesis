#include "kernel/paging.h"
#include "include/stdtypes.h"
#include "kernel/tty.h"
#include "kernel/interrupt.h"
#include "include/string.h"
extern uint32_t kernel_heap_addr;

//macros for bit testing

#define index_from_bit(a) (a/32)
#define offset_from_bit(a) (a%32)
//bit set frames used / free
uint32_t *frames;
uint32_t nframes;

//kernel page directory
page_directory_t *kernel_page_dir=0;
//current page direcory 
page_directory_t *current_page_dir=0;


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
	uint32_t i,j;

	for(i=0; i<index_from_bit(nframes); i++){
		//check whether no frame exist
		if(frames[i]!=0xffffffff){
			//if exist check for that one frame
			for(j=0;j<32;j++){
				uint32_t test = 0x1<<j;
				if(!(frames[i] & test)){
					return i*4*8+j;
				}
			}
		}
	}
	return -1;
}


//frame allocator functions.

void alloc_frame(page_t *page,int is_kernel,int is_writable){

	uint32_t free_index;
	if(page->frame != 0){
		return;
	}
	else{
		free_index=first_frame();
		if(free_index == (uint32_t)-1){
			asm volatile("int $14");
			return;
		}
	set_frame(free_index*0x1000);
	page->present=0x1;
	page->rw = (is_writable)?1:0;
	page->user = (is_kernel)?0:1;
	page->frame = free_index;
	}
}

//function deallocate the frame

void free_frame(page_t *page){

	uint32_t frame;
	if(!(frame=page->frame)){
		//page is no present in the given frame
		return;
	}
	else{
		clear_frame(frame);
		page->frame=0x0;
	}
}


//page initializer

void initialize_paging(){
	uint32_t end_page = 0x1000000; //2^64
	int i = 0;
	nframes = end_page/0x1000; //4096/4K

	frames = (uint32_t*) kmalloc(index_from_bit(nframes),0,0);

	memset(frames,0,index_from_bit(nframes));

	//create page directory
	kernel_page_dir = (page_directory_t*)kmalloc(sizeof(page_directory_t),1,0);
	memset(kernel_page_dir,0,sizeof(page_directory_t));
	current_page_dir = kernel_page_dir;
	//make kernel code space into page
	
	uint32_t page_addr=0;
	while(page_addr<kernel_heap_addr){
		alloc_frame(get_page(page_addr,1,kernel_page_dir),1,0);
		page_addr+=0x1000;
		
	}

	//enable paging by swithcing into kernel_page_dir
	switch_page_dir(kernel_page_dir);
}

//enable paging by writing CR0 reg 
void switch_page_dir(page_directory_t *dir){
	uint32_t cr0;
	current_page_dir = dir;
	asm volatile("mov %0,%%cr3"::"r"(dir->table_physical_addr));
	asm volatile("mov %%cr0,%0":"=r"(cr0));
	write_dec(cr0);
	cr0|=0x80000000; //enable paging
	asm volatile("mov %0,%%cr0"::"r"(cr0));
}

//get page function to return page from page_table_dir
page_t * get_page(uint32_t address,uint8_t  make, page_directory_t *dir){
	uint32_t table_index,temp;
	address/=0x1000; //index
	table_index = address/1024;

	if(dir->pages[table_index]){
		return &dir->pages[table_index]->pages[address%1024];
	}
	else if(make){
		dir->pages[table_index] = (page_table_t*)kmalloc((sizeof(page_table_t)),1,&temp);

		memset(dir->pages[table_index],0,0x1000);
		dir->table_physical_addr[table_index] = temp|0x7;
		terminal_writestring("\nPage table address : ");
		//write_dec(dir->table_physical_addr);
		terminal_writestring("\nPage table index : ");
		write_dec(table_index);
		return &dir->pages[table_index]->pages[address%1024];
	}
	else{
		return 0;
	}
}


//define page fault handler
void page_fault_handler(register_t reg){
 	uint32_t fault_addr;
	terminal_writestring("Page fault accured at : ");
	write_dec(fault_addr);
	terminal_writestring("\n Due to ");
	write_dec(reg.err_no);
}
