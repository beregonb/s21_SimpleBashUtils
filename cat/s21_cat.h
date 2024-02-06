#ifndef S21_CAT_H
#define S21_CAT_H

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void cat(char *name);
void cat_n(char *name);
void cat_b(char *name);
void cat_e(char *name);
void cat_s(char *name);
void cat_t(char *name);
void cat_v(char *name);
void cat_T(char *name);
void cat_E(char *name);
void print_encodings(char a);

static struct option long_options[] = {
    {"show-nonprinting", no_argument, 0, 'v'},
    {0, no_argument, 0, 'e'},
    {"number", no_argument, 0, 'n'},
    {0, no_argument, 0, 't'},
    {"squeeze-blank", no_argument, 0, 's'},
    {"number-nonblank", no_argument, 0, 'b'},
    {"show-tabs", no_argument, 0, 'T'},
    {"show-ends", no_argument, 0, 'E'},
    {0, 0, 0, 0}};

#endif