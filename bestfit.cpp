/*BEST FIT: you find the chunk whose size is the closest match to the allocation need. Often that
will be exactly the size required by the client, so you do not have internal fragmentation. (Here
we assume the perfect scenario to simplify the task.)*/

#include "assignedLL.h"

AssignedLL::AssignedLL(){
    allocatedList = std::list<allocation*>();
    freeList = std::list<allocation*>();
    allocationRequests = 0;
    deallocationRequests = 0;
}
        
// Destructor
AssignedLL::~AssignedLL(){

}

void* AssignedLL::alloc(std::size_t size){

    allocation* bestFitChunk = nullptr;
    std::size_t bestFitSize = std::numeric_limits<std::size_t>::max();
    std::size_t allocateMem;
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

    // Find the best fit chunk
    for (auto i = freeList.begin(); i != freeList.end(); ++i) {
        if ((*i)->size >= size) {
            if ((*i)->size < bestFitSize) {
                bestFitSize = (*i)->size;
                bestFitChunk = *i;
            }
        }
    }
    if (bestFitChunk != nullptr) {
        bestFitChunk->used = size;
        allocatedList.push_back(bestFitChunk);
        freeList.remove(bestFitChunk);
        return bestFitChunk->space;
    }

    allocation* new_chunk = new allocation{allocateMem, size, new_space};
    allocatedList.push_back(new_chunk);
    allocationRequests++;
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
    deallocationRequests++;
}

std::size_t AssignedLL::getAllocationRequests() const {
    return allocationRequests;
}

std::size_t AssignedLL::getDeallocationRequests() const {
    return deallocationRequests;
}


void AssignedLL::printLists() {
    // allocated list
    std::cout << "Allocated List" << std::endl;

    std::size_t totalAllocatedSize = 0;
    std::size_t totalUsedSize = 0;

    for (const auto& chunk : allocatedList) {

        std::cout << "Address: " << chunk->space << " Total Chunk Size: " << chunk->size << " Used Chunk Size: " << chunk->used <<std::endl;
        totalAllocatedSize += chunk->size;
        totalUsedSize += chunk->used;
        int ret = brk(chunk->space);
        if (ret == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
    }

    // free list
    std::cout << "Free List" << std::endl;

    std::size_t totalFreeSize = 0;

    for (const auto& chunk : freeList) {

        std::cout << "Address: " << chunk->space << " Total Chunk Size: " << chunk->size << " Used Chunk Size: " << chunk->used <<std::endl;
        totalFreeSize += chunk->size;
        int ret2 = brk(chunk->space);
        if (ret2 == -1) {
            std::cout << "brk encountered error" << std::endl;
        }
    }

    std::cout << "Total Allocated Size: " << totalAllocatedSize << std::endl;
    std::cout << "Total Used Size: " << totalUsedSize << std::endl;
    std::cout << "Total Free Size: " << totalFreeSize << std::endl;

}