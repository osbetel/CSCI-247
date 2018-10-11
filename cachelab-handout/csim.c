
#include "cachelab.h"
#include <math.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * A line. LRU is the least recently used portion.
 * We will use an LRU algortihm to determine evictions
 */
typedef struct{
    int valid;
    int tag;
    int bits;
    int LRU;
} Line;

/*
 * A Set of lines, of the form S = {all lines L in this given set}
 * Relevant for the cache which is a set C of all sets S, of all lines L
 * L ϵ S ϵ C is the mathematical representation here.
 */
typedef struct{
    Line* lines;
} lineSet;

/*
 * L ϵ S ϵ C, where C represents the cache. It can also be thought of as a 2D matrix/array of sorts.
 * It would require workarounds to make it function like one, but it is very similar
 */
typedef struct {
    lineSet* lineAR;
} Cache;

/*
 * S = number of lineSets in the cache
 * E = number of lines contained in a lineSet (set of lines)
 * B = Block size
 * m = address
 * b = offset
 * s = index
 */
typedef struct{
    int S;
    int E;
    int B;
    int m;
    int b;
    int s;
} cacheData;

/*
 * Generates data on the cache. cacheData obj is different from the cache obj
 * The cache obj is the actual cache being simulated, cacheData is for convenience of access
 * to commonly used data
 */
cacheData* cacheDataGen(int S, int E, int B, int s, int b) {
    cacheData *data = (cacheData*) malloc(sizeof(cacheData));
    data->S = S;
    data->E = E;
    data->B = B;
    data->s = s;
    data->b = b;
    return data;
}

/*
 * Records evictions or misses
 */
void recordEvictOrMiss(lineSet* lineSet, int tag, int E, int boolFlag, int numlru) {
    Line* Lptr = lineSet->lines;

    if(boolFlag) {

        Line* LRU = Lptr;
        int min = numlru;
        int i;

        //Finds the LRU, if exists, evict...
        for (i = 0; i < E; i++) {
            if (min > (Lptr->LRU)) {
                min = Lptr->LRU;
                LRU = Lptr;
            }
            Lptr++;
        }
        LRU->LRU = numlru;
        LRU->tag = tag;
    }
    //...Else miss
    else {
        while (Lptr->valid) Lptr++;
        Lptr->valid = 1;
        Lptr->tag = tag;
        Lptr->LRU = numlru;
    }
}

/*
 * Records hits. If it is not a hit, it must be a miss or an eviction
 * Those are handled separately. Hit = 1, other = 0.
 */
int recordDataInsertion(Line* lineData, int tag, int upperLim, int count) {
    int dataFull;

    //Valid bits and tags must match
    int i;
    for (i = 0; i < upperLim; i++) {
        if ((lineData->tag == tag) && (lineData->valid == 1)) {
            lineData->LRU = count;
            return 1;
        }

        else {
            dataFull = lineData->valid;
            lineData++;
        }
    }

    if (dataFull) return 2; // cache miss+eviction.
    return 0;
}

/* This function is for making the actual cache but not filled in yet.
 * As well, we allocated space for the cache, the sets, and the lines in sets.
 */
Cache* makeCache(cacheData* cacheData) {

    //Begin allocation of data for the cache
    //Cache is a set of lineSets, which are sets of lines
    //Must allocate for all three of these
    Cache *cache = (Cache*) malloc(sizeof(Cache));
    cache->lineAR = (lineSet*) malloc(sizeof(lineSet)*(cacheData->S));
    lineSet* lineSet = cache->lineAR;

    int i,j;
    for(i = 0; i < cacheData->S; i++) {
        lineSet->lines = (Line*) malloc(sizeof(Line)* (cacheData->E));
        Line* tolineSet = lineSet->lines;

        //Set data for initial portion of the cache, to be inserted into the current lineSet (in for loop i)
        for(j = 0; j < cacheData->E; j++){
            tolineSet->valid = 0;
            tolineSet->tag = 0;
            tolineSet->bits = 0;
            tolineSet->LRU = 0;
            tolineSet++;
        }
        lineSet++;
    }
    return cache;
}

/*
 * A helper struct to hold data from the terminal inputs
 */
typedef struct {
    int x;
    int S;
    int B;
    int s; // input number of set index bits.
    int E; // input number of lines per set
    int b; // input number of block bits.
    char* t; // name of the input trace file
} terminalInput;

/*
 * Builds and returns a struct containing all terminal input for the current trace
 */
terminalInput *fetchTerminalInput(int argc, char* argv[]) {
    terminalInput *input = (terminalInput*) malloc(sizeof(terminalInput));
    int terminal = (getopt(argc, argv, "s:E:b:t:"));

    while (terminal != -1) {
        switch(terminal) {
            case('s'):
                input->s =  atoi(optarg);
                break;
            case('E'):
                input->E = atoi(optarg);
                break;
            case('b'):
                input->b = atoi(optarg);
                break;
            case('t'):
                input->t = optarg;
                break;
            default:
                abort();
        }
        terminal = (getopt(argc, argv, "s:E:b:t:"));
    }

    input->S = pow(2.0, input->s);
    input->B = pow(2.0, input->b);
    return input;
}

int main(int argc, char* argv[]) {
    int h = 0;  //hit
    int m = 0;  //miss
    int e = 0;  //evict
    int c = 1;
    int isFilled;

    unsigned int sindex;
    unsigned int tag;

    //Collect input and build the cache data/parameters from the input struct
     terminalInput *input = fetchTerminalInput(argc, argv);
    cacheData* data = cacheDataGen(input->S, input->E, input->B, input->s, input->b);

    //Cache, the instructions, address and size all allocated, opens trace
    Cache* cache = makeCache(data);
    char instruction;
    unsigned int addr, size;
    FILE *trace = fopen(input->t, "r");

    int i; //for the inner for loop
    while (fscanf(trace, " %c %x,%d", &instruction, &addr, &size) == 3){

        sindex = (addr & ((~0 << input->b) ^ (~0 << (input->b + input->s)))) >> input->b;
        tag = addr & ((~0) << (input->b + input->s));

        if (instruction != 'I'){
            lineSet* lsetPtr = cache->lineAR;

            //Incrementing the lineSet pointer
            for(i = 0; i < sindex; i++) {
                lsetPtr++;
            }

            Line* Lptr = lsetPtr->lines;
            isFilled = 0;
            input->x = recordDataInsertion(Lptr, tag, data->E, c);

            //Handles misses, inserts
            if (input->x == 1) {
                h += 1;
            } else {
                m += 1;
                if (input->x == 2){
                    e++;
                    isFilled = 1;
                }
                recordEvictOrMiss(lsetPtr, tag, data->E, isFilled, c);
            }

            if (instruction == 'M') h++;
            c++;
        }
    }
    printSummary(h, m, e);
    return 0;
}
