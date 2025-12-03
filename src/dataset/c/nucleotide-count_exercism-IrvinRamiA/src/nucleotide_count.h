#ifndef _NUCLEOTIDE_COUNT_H
#define _NUCLEOTIDE_COUNT_H

typedef struct
{
    unsigned char ctr_a;
    unsigned char ctr_c;
    unsigned char ctr_g;
    unsigned char ctr_t;
    unsigned char ctr_other;
} nucleotide_counter_t;

char *count(const char *dna_strand);

#endif
