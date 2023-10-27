#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string> 
#include <iostream>
#include <list>
#include <cstdlib>
#include <limits>
#include <unistd.h>

class AssignedLL{
    public:
        struct allocation {
            std::size_t size;
            std::size_t used;
            void *space;
        };

        std::list<allocation*> allocatedList;
        std::list<allocation*> freeList;

        AssignedLL();
        ~AssignedLL();

        void* alloc(std::size_t chunk_size);
        void dealloc(void* chunk_space);
        void dealloc();


        std::size_t getAllocationRequests() const;
        std::size_t getDeallocationRequests() const;


        void printLists();
    
    private:
        std::size_t allocationRequests;
        std::size_t deallocationRequests;
};

#endif  // LINKEDLIST_H