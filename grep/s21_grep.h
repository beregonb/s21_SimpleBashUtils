#ifndef S21_GREP_H
#define S21_GREP_H

#define size 4096
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flag;

void parser(int argc, char *argv[], flag *f, char *pattern);
void search(int argc, char *argv[], flag *f, char *pattern);
void flags(regex_t regex, flag *f, char *str, FILE *fp, int file_count,
           char *filename);
void flags_browse(flag *f);
void print(flag *f, int line, int file_count, char *filename);
void grep_e(char *pattern, char *str);
void grep_f(char *pattern, char *filename);

#endif