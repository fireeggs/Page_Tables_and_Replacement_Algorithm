/*
 * ============================================================================================
 * File Name : clock.c
 * Name	: Seungkyu Kim
 * Created Date	: Oct.21.2015
 * Modified Date : Oct.28.2015
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

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	
	int victim;
	static int clock_index;
	pgtbl_entry_t *t_entry;
	int condition=1;
	while(condition) {
		t_entry = (pgtbl_entry_t *) coremap[clock_index].pte;
		if(t_entry->frame & PG_REF) {
			t_entry->frame = t_entry->frame & ~PG_REF;
		} else {
			victim = clock_index;
			condition = 0;
		}
		clock_index++;
		clock_index = clock_index % memsize;
	}
	return victim;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
}
