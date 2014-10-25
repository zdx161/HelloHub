#ifndef OPTION_STRUCT_H
#define OPTION_STRUCT_H
#include "common.h"

void help(void);
void print_config(AudioInfo optinfo);
int parse_option(int argc, char **argv, AudioInfo *optinfo);
void set_default_config(AudioInfo *definfo);
#endif
