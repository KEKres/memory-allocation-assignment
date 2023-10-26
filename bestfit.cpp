/*BEST FIT: you find the chunk whose size is the closest match to the allocation need. Often that
will be exactly the size required by the client, so you do not have internal fragmentation. (Here
we assume the perfect scenario to simplify the task.)*/

#include "assignedLL.h"

AssignedLL::AssignedLL(){
    allocatedList = std::list<allocation*>();
    freeList = std::list<allocation*>();
}
        
// Destructor
AssignedLL::~AssignedLL(){

}

void* AssignedLL::alloc(std::size_t size){

    std::size_t allocateMem = 512;

    //finds a chunk from the free list that is big enough to fit the size

    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size >= size) {
            if ((*i)->size < allocateMem){
                allocateMem = (*i)->size;
            }
        }
    }

    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size == allocateMem) {
            allocation* chunk = *i;
            freeList.erase(i);
            chunk->used = size;
            allocatedList.push_back(chunk);
            return chunk->space;
        }
    }

    // If no suitable chunk is found in the free list, use sbrk() to allocate more memory.

    if (size <= 32){
        allocateMem = 32;
    }

    else if (size <= 64){
        allocateMem = 64;
    }

    else if (size<= 128){
        allocateMem = 128;
    }

    else if (size <= 256){
        allocateMem = 256;
    }

    else if (size <= 512){
        allocateMem = 512;
    }

    void* new_space = sbrk(allocateMem);
    if (new_space == (void*) -1) {
        throw std::bad_alloc();
    }

    allocation* new_chunk = new allocation{allocateMem,size, new_space};
    allocatedList.push_back(new_chunk);
    return new_space;

}

void AssignedLL::dealloc(){
    //remove last chuck from allocated and add to free list

    if (allocatedList.size() == 0) {
        throw std::runtime_error("Attempted to deallocate memory that was never allocated.");
    }

    allocation* chunk = allocatedList.back();
    chunk->used = 0;
    allocatedList.pop_back();
    freeList.push_back(chunk);
}

void AssignedLL::printAllocatedList() {
    // allocated list
    for (auto i = allocatedList.begin(); i != allocatedList.end(); ++i) {

        std::cout << (*i)->space << " " << (*i)->used << " " << (*i)->size <<std::endl;
        int ret = brk((*i)->space);
        if (ret == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
        
        delete *i;
    }

    // free list
    for (auto i = freeList.begin(); i != freeList.end(); ++i) {

        std::cout << (*i)->space << " " << (*i)->used << " " << (*i)->size <<std::endl;
        int ret2 = brk((*i)->space);
        if (ret2 == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
        delete *i;
    }
}