//2019039843

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#include "cachelab.h"


typedef union Options_ {
    struct
    {
        char _ : 3;
        char v : 1;
        char s : 1;
        char e : 1;
        char b : 1;
        char t : 1;
    };
    
    char optbit : 8;
} Options;

typedef struct Line_ {
    int64_t tag;
    uint64_t last_modified;
} Line;

typedef struct Set_ {
    Line* lines;
    int64_t num;
    uint64_t clock;
} Set;


bool is_vervose = false;
int idx_bit_num = 0;
int line_num = 0;
int block_offset = 0;

Set* cache;

int hit_num;
int miss_num;
int eviction_num;


void printHelp() {
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
           "Options:\n"
           "-h         Print this help message.\n"
           "-v         Optional verbose flag.\n"
           "-s <num>   Number of set index bits.\n"
           "-E <num>   Number of lines per set.\n"
           "-b <num>   Number of block offset bits.\n"
           "-t <file>  Trace file.\n\n"

           "Examples:\n"
           "linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n"
           "linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

void putToCache(int64_t tag, int64_t set_id) {
    Set* target_set = cache + set_id;
    bool block_found = false;
    uint64_t least_clock = UINT64_MAX;

    (target_set->clock)++;

    int eviction_target;
    for (int i = 0; i < target_set->num; i++) {
        if ((target_set->lines)[i].last_modified < least_clock) {
            least_clock = (target_set->lines)[i].last_modified;
            eviction_target = i;
        }
        if ((target_set->lines)[i].tag == tag) {
            block_found = true;
            (target_set->lines)[i].last_modified = target_set->clock;
            hit_num++;
            if (is_vervose) {
                printf("hit");
            }
            return;
        }
    }

    if (!block_found) {
        miss_num++;
        if (is_vervose) {
            printf("miss");
        }
        if (target_set->num < line_num) {
            (target_set->lines)[target_set->num].tag = tag;
            (target_set->lines)[target_set->num++].last_modified = target_set->clock;
        } else {
            (target_set->lines)[eviction_target].tag = tag;
            (target_set->lines)[eviction_target].last_modified = target_set->clock;

            eviction_num++;
            if (is_vervose) {
                printf(" eviction");
            }
        }
    }
}

int main(int argc, char** argv)
{
    Options option_chk;
    option_chk.optbit = 0x00;

    FILE* trace_file;

    char option;
    while ((option = getopt(argc, argv, "hvs:E:b:t:")) != EOF) {
        switch (option) {
            case 'h':
                printHelp();
                return 0;
            case 'v':
                is_vervose = true;
                option_chk.v = 1;
                break;
            case 's':
                idx_bit_num = atoi(optarg);
                if (idx_bit_num != 0) {
                    option_chk.s = 1;
                }
                break;
            case 'E':
                line_num = atoi(optarg);
                if (line_num != 0) {
                    option_chk.e = 1;
                }
                break;
            case 'b':
                block_offset = atoi(optarg);
                if (block_offset != 0) {
                    option_chk.b = 1;
                }
                break;
            case 't':
                trace_file = fopen(optarg, "r");
                if (trace_file == NULL) {
                    printf("%s: %s\n", optarg, strerror(errno));
                    return 0;
                }
                option_chk.t = 1;
        }
    }

    if ((option_chk.optbit & 0xf0) != 0xf0) {
        printf("%s: Mising required command line argument\n", argv[0]);
        printHelp();
        return 0;
    }

    cache = malloc(sizeof(Set) * (1 << idx_bit_num));
    for (int i = 0; i < (1 << idx_bit_num); i++) {
        cache[i].lines = malloc(sizeof(Line) * line_num);
        cache[i].num = 0;
        cache[i].clock = 0;
    }

    char buf[100];
    char* line;

    char* address_str;
    int64_t address;
    int64_t tag;
    int64_t set_id;

    while (fgets(buf, 100, trace_file) != NULL) {
        if (buf[0] == ' ') {
            line = buf + 1;
        } else {
            continue;
        }

        if (is_vervose) {
            printf("%s", strtok(line, "\n"));
        }

        line += 1;
        
        address_str = strtok(line, ",");
        address = strtol(address_str, NULL, 16);

        address >>= block_offset;
        
        tag = address >> idx_bit_num;
        
        int64_t mask = 0;
        for (int i = 0; i < idx_bit_num; i++) {
            mask <<= 1;
            mask |= 1;
        }
        
        set_id = address & mask;

        if (buf[1] == 'L' || buf[1] == 'S') {
            printf(" ");
            putToCache(tag, set_id);
        } else {
            printf(" ");
            putToCache(tag, set_id);
            printf(" ");
            putToCache(tag, set_id);
        }
        printf("\n");
    }
    
    printSummary(hit_num, miss_num, eviction_num);
    return 0;
}
