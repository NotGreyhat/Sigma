#include <memory/pmm.h>
#include <util/limine.h>


static volatile struct limine_memmap_request mmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};


static void* placement_addr = NULL;
static uint8_t init = 0;
static uint64_t memlimit = 0;
static uint64_t mem;


static struct limine_memmap_entry* fetch_largest_segment() {
    uint32_t biggestSize = 0;
    struct limine_memmap_entry* lastEntry = NULL;

    for (int i = 0; i < mmap_request.response->entry_count; ++i) {
        struct limine_memmap_entry* entry = mmap_request.response->entries[i];
        if (entry->length > biggestSize) {
            biggestSize = entry->length;
            lastEntry = entry; 
        }
    }

    return lastEntry;
}


uint64_t getmem() {
    return mem;
}


void pmm_init() {
    if (init) return;
    init = 1;
    struct limine_memmap_entry* placementLoc = fetch_largest_segment();
    memlimit = mem = placementLoc->length - 1;
    placement_addr = (void*)placementLoc->base;
}


void* kmalloc(size_t size) {
    if (!(init)) return NULL;
    if (placement_addr + size > placement_addr + memlimit || mem == 0) return NULL;
    mem -= size;

    void* ret_addr = placement_addr;
    placement_addr += size;
    return ret_addr;
}
