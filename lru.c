/*
 * ============================================================================================
 * File Name : lru.c
 * Name	: Seungkyu Kim
 * Created Date	: Oct.25.2015
 * Modified Date : Oct.30.2015
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
long int count;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	int i;
	int index = 0;
	long int minimum = coremap[0].count;
	for(i = 0; i < memsize; i++) {
		if (minimum > coremap[i].count){
			index = i;
			minimum = coremap[i].count;
		}
	}
	return index;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {

	int i;
	for (i = 0; i < memsize; i++){
		if(coremap[i].pte == p){
			break;
		}
	}
	coremap[i].count = count++;	
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
}
