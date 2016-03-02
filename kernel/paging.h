#ifndef PAGING_H
#define PAGING_H

//page fault causes
#define PAGE_PRESENT 0x01
#define PAGE_WRITE 0x02
#define PAGE_USR  0x04
#define PAGE_RSVD 0x08
#define PAGE_FETCH 0x10

#include "include/stdtypes.h"

//page descriptor structure :32bit word
typedef struct{
	//page present in the memory ->1 else 0
	uint32_t present:1;
	//read only->0 or rw->1
	uint32_t rw:1;
	//0 ->supervisor 1->user mode
	uint32_t user:1;
	//Reserved 2 bits for CPU
//	uint32_t rsvd:2;
	//page accessed ->1
	uint32_t accessed:1;
	//page has been written to (dirty bit)
	uint32_t dirty:1;
	//reserved :2 bits
	//3 bits available for kernel &unused.
	uint32_t unused:7;
	uint32_t frame:20;
}page_t;

typedef struct{
	page_t pages[1024];
}page_table_t;

/*
 * Page table directory structure
 * Stores th info on page table 
 * */
typedef struct{
	//array of pointers to page tables;
	page_table_t *pages[1024];
	/** array of page table physical address
	 * for loading into CR3
	 * */
	uint32_t table_physical_addr[1024];
	/* store the starting pointer address
	 * of table_phy_addr
	 * future use for cloning table
	 * */
	uint32_t physical_addr;
}page_directory_t;

//paging utility functions

void initialize_paging();

//page directory loader -> CR3

void switch_page_dir(page_directory_t *new_dir);

/*get page pointer
 * make : if not present in page table create it
 * */
page_t *get_page(uint32_t address,uint8_t make,page_directory_t *dir);

//page falut handler int 14.
void page_fault_handler();
#endif /*PAGING_H */
