struct Allocation {
    std::size_t size;
    void *space;
};


std::list<Allocation> occupiedChunks;
std::list<Allocation> freeChunks;
// Add any other global variables for tracking the allocation strategy.


void dealloc(void* chunk);
void* alloc(std::size_t chunk_size);