/*FIRST FIT: the first chunk that you find big enough is returned to the user.*/

#include "assignedLL.h"

void* AssignedLL::alloc(std::size_t size){
    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size >= size) {
            allocation* chunk = *i;
            freeList.erase(i);
            chunk->used = size;
            allocatedList.push_back(chunk);
            return chunk->space;
        }
    }

    // If no suitable chunk is found in the free list, use sbrk() to allocate more memory.
    std::size_t allocateMem;

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

    allocation* new_chunk = new allocation{allocateMem, size, new_space};
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

AssignedLL::~AssignedLL() {
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