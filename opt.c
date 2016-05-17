/*
 * ============================================================================================
 * File Name : opt.c
 * Name	: Seungkyu Kim
 * Created Date	: Nov.1.2015
 * Modified Date : Nov.3.2015
 *
 * Copyright 2015 Seungkyu Kim all rights reserved
 * ============================================================================================
 */

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;
extern int debug;
extern struct frame *coremap;

unsigned length;
unsigned file_position;
unsigned line;
addr_t *vaddr_ptr;

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {
	
	int i;
	unsigned maximum = (coremap[0]).length;
	int index = 0;

	// Take the max length from pte with coremap
	for(i = 0; i < memsize; i++){
		if((coremap[i].length > maximum)){
			maximum = (coremap[i]).length;
			index = i;
		}		
	}
	return index;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {

	addr_t current = vaddr_ptr[file_position];
	unsigned next = file_position +1;

	// Calculate and asign length
	while(next < line){
		if(current != vaddr_ptr[next]){ 
			next++;
		} else {
			break;
		}
	}
	if (next != line) {
		p->length = next; 
	} else {
		p->length = line +1;
	}
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {

}

