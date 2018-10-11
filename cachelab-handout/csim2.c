#include "cachelab.h"
#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valid;
    int tag;
    int bits;
    int LRU;
    /*
     * Least Recently Used is the algorithm used to keep track of which lines to
     * evict from the cache. See the algorithm page or assignment pdf
     */
} Line;

typedef struct {
    Line* lineAR;
} lineSet;

typedef struct {
    lineSet* setAR;
} Cache;

typedef struct {
    int S; //Number of Sets
    int E; //Number of Lines per Set
    int B; //Block size
    int m; //address bits
    int b; //block offset
    int s; //set index
} cacheData;

/* This function is for making a struct with all the data about the cache,
 * such as number of sets and number of lines per set.*/
cacheData* makeCacheData(int S, int E, int B, int s, int b) {
    cacheData *data = (cacheData*) malloc(sizeof(cacheData));
    data->S = S;
    data->E = E;
    data->B = B;
    data->s = s;
    data->b = b;

    return data;
}

/* This function is for making the actual cache but not filled in yet.
 * As well, we allocated space for the cache, the sets, and the lines in sets.
 */
Cache* makeCache(cacheData* cacheData) {

    //Allocation of space for the cache and its internal components
    //ie: Cache is an array of Sets, where each Set is an array of Lines
    //This forms a 2D matrix of sorts (not as easy as in Java or Python for example)
    //Still it can be made to function like a 2D array. Visualize a "block" of cache
    Cache *dataOfCache = (Cache*) malloc(sizeof(Cache));
    dataOfCache->setAR = (lineSet*) malloc(sizeof(lineSet)*(cacheData->S));

    int i,j;
    lineSet* set = dataOfCache->setAR;
    for(i = 0; i<(cacheData->S);i++){
        //malloc per Line, per Set, for the Cache
        set->lineAR= (Line*) malloc(sizeof(Line)*(cacheData->E));
        Line* line = set->lineAR;

        //Valid bit, tag, rest of the bits, per line
        for(j=0; j<(cacheData->E); j++){
            line->valid = 0;
            line->tag = 0;
            line->bits = 0;
            line->LRU = 0;
            line++;
        }
        set++;
    }
    return dataOfCache;
}

/*
 * runs free() on all the components of a Cache struct, as well as on the cacheData struct
 * Deallocates memory for all respective objects
 */
void cleanCache(Cache* cache, cacheData* cacheData) {

    free((cache->setAR)->lineAR);
    free(cache->setAR);
    free(cache);
    free(cacheData);
}

/*
 * Hit is data in cache, returns 1
 * Miss if data not in cache, returns 0
 */
int isHitOrMiss(Line* lines, int count, int tag, int size) {
    int i; //loop counter
    int flag;
    // loop goes through every line, checks if valid and if tags match.
    for(i = 0; i < size; i++){
        if((lines->tag == tag)&&(lines->valid == 1)){
            lines->LRU=count;
            return 1;   //Hit
        } else {
            flag = lines->valid;
            lines++;
        }
    }

    if (flag) {
        return 2;   //miss and/or eviction in the cache
    } else {
        return 0; //cache miss
    }
}

/*
 * Handles non-hit cases (eviction and miss)
 */
void recordNonHits(lineSet* lineSet, int address, int tag, int E, int isFull, int count) {
    Line* ptr = lineSet->lineAR;
    if(isFull) {
        Line* lineAtLRU = ptr;
        int min = count;

        int i;
        for(i = 0; i < E; i++) {
            if(min > ptr->LRU){
                min = ptr->LRU;
                lineAtLRU = ptr;
            }
            ptr++;
        }
        lineAtLRU->tag = tag;
        lineAtLRU->LRU = count;
    } else {
        while(ptr->valid) ptr++;
        ptr->valid = 1;
        ptr->tag = tag;
        ptr->LRU = count;
    }
}

int main(int argc, char* argv[]) {
    int s; // input number of set index bits.
    int E; // input number of lines per set
    int b; // input number of block bits.
    char* t; // name of the input trace file
    int command_line_in;
    int x;
    // getopt gets the argument after, -s, -E, -b, -t
    while ((command_line_in = (getopt(argc, argv, "s:E:b:t:"))) != -1){
        switch(command_line_in)
        {
            case('s'):
                s =  atoi(optarg);
                break;
            case('E'):
                E = atoi(optarg);
                break;
            case('b'):
                b = atoi(optarg);
                break;
            case('t'):
                t = optarg;
                break;
            default:
                abort();
        }
    }

    int S = pow(2.0, s);
    int B = pow(2.0, b);

    // make a cache data struct using the information from the command line, s, E, and b.
    cacheData* cacheData= makeCacheData(S, E, B, s, b);

    // make an empty cache used for the simulation.
    Cache* cache = makeCache(cacheData);
    char cmd; // holds char representing the instruction on each line: I,S,L, and M.
    unsigned int address, size;
    FILE *traces = fopen(t, "r");

    unsigned int set_index;  // bits in the address to which set address should go in.
    unsigned int block_offset; // bits in the address representing the offset (b).
    unsigned int tag; // bits in the address representing the tag (t).
    int c1; //loop counter

    int hits = 0;
    int misses = 0;
    int evictions = 0;
    int count = 1;
    int isFull;

    // loops until it sees a line that doesn't have 3 arguments in it (char, hex address, int).
    while (fscanf(traces, " %c %x,%d", &cmd, &address, &size) == 3) {
        printf("%c %x,%d\n", cmd, address, size);

        // isolate the middle bits that are part of the s block, representing the set index.
        set_index = (address &((~0 << b) ^ (~0 << (b + s)))) >> b;

        // isolate the b-bits chunk representing the block offset.
        block_offset = (address &~((~0) << b));
        block_offset++;

        // isolate the tag bits from the address.
        tag = address&((~0 )<< (b + s));


        if (cmd != 'I'){
            lineSet* set_pointer = cache->setAR;
            // find to which set the address belongs to.
            for(c1=0;c1<set_index;c1++)
                set_pointer++;
            Line* line_pointer = set_pointer->lineAR;
            isFull=0;
            // if the tag and valid bit match to an address already in the set then call hit.
            x = isHitOrMiss(line_pointer, tag, cacheData->E, count);

            if (x == 1){
                printf("hit\n");
                hits += 1;
            } else{ // if there's no such address then call a miss & add to cache.
                misses += 1;
                printf("miss\n");
                if (x == 2){
                    evictions++;
                    printf("eviction\n");
                    isFull = 1;
                }
                recordNonHits(set_pointer, address, tag, cacheData->E, isFull, count);


            }
            if (cmd == 'M'){
                hits++;
            }
            count++;
        }
    }


    printSummary(hits, misses, evictions);
    fclose(traces);

    cleanCache(cache, cacheData);
    return 0;
}
