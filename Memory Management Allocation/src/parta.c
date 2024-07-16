#include <stdlib.h> // For malloc/free
#include <stdio.h>
#include "parta.h"

/**
 * Initilizes a memory region with a specified size
 *  
 * @param size The memory size allocation
 * @return pointer to the memory region that is initilized 
 */
struct mem_region* mem_region_init(int size) {
    if(size <= 0){
        return NULL;
    }
    struct mem_region *ans = malloc(sizeof(struct mem_region)*(size+3));
    ans->next = NULL;
    ans->owner = OWNER_NOBODY;
    ans->size = size;
    return ans;
}

/**
 * Terminates all of the memory regions in the linked list
 *  
 * @param regions Pointer to the head of the memory region
 */
void mem_region_term(struct mem_region* regions) {
    while(regions != NULL){
        struct mem_region *temp = regions;
        regions = regions->next;
        free(temp);
    }
}

/**
 * Assigns a new partition by splitting a part of the memory region
 * to the owner and to what is left over of the hole
 *  
 * @param r The head of the memory region
 * @param requester The owner or process requesting the region
 * @param size The amount of memory the requester is asking for
 */
void mem_region_assign(struct mem_region* r, int requester, int size) {
    
    if (r == NULL || r->size < size || size < 0 || requester == OWNER_NOBODY){
        return;
    }
    int nums = r->size - size;
    struct mem_region *ID = mem_region_init(nums);
    r->size = size;
    r->owner = requester;
    r->next = ID;
    
}

/**
 * Merges all memory regions that have no owner together
 *  
 * @param regions pointer to the head of memory region
 */
void mem_region_merge_empty(struct mem_region* regions) {
    struct mem_region *temp;
    while(regions->next != NULL){
        temp = regions->next;
        if(regions->owner == OWNER_NOBODY && temp->owner == OWNER_NOBODY){
            int new = temp->size + regions->size;
            regions->size = new;
            if(temp->next == NULL){
                regions->next = NULL;
                free(temp);
            } else {
                regions->next = temp->next;
                free(temp);
            }
        } else {
            regions = temp;
        }
        
    }
}

/**
 * Using first fit, allocates a process to a particular region of the
 * memory region 
 *  
 * @param regions The head of the memory region
 * @param requester The owner or process requesting the region
 * @param size The amount of memory the requester is asking for
 */
void mem_region_alloc(struct mem_region* regions, int requester, int size) {
    while(regions != NULL){
        if(regions->size > size){
            mem_region_assign(regions, requester, size);
            return;
        } else {
            regions = regions->next;
        }
        
    }
}

/**
 * Removes a process from the memory region
 *  
 * @param regions pointer to the head of the memory region
 * @param requester The owner or process that has finished
 */
void mem_region_free(struct mem_region* regions, int requester) {
    while(regions != NULL){
        if(regions->owner == requester){
            regions->owner = OWNER_NOBODY;
            mem_region_merge_empty(regions);
        } else {
            regions = regions->next;
        }
    }
}

