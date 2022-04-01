#ifndef VMM_H
#define VMM_H


typedef struct {
    uint32_t p : 1;
    uint32_t rw : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t unused : 7;
    uint64_t frame : 20;
} page_t;


typedef struct {
    page_t pages[1024];
} page_table_t;


typedef struct {
    page_table_t* tables;
    uint64_t tablesPhys;
    uint32_t physicalAddr;
} page_dir_t;



#endif
