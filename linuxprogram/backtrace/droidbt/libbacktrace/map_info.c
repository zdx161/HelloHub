/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
//#include <log/log.h>
#include <sys/time.h>

#include <backtrace/backtrace.h>


// Linux /proc/<pid>/maps lines:
// 6f000000-6f01e000 rwxp 00000000 00:0c 16389419   /system/lib/libcomposer.so\n
// 012345678901234567890123456789012345678901234567890123456789
// 0         1         2         3         4         5
static backtrace_map_info_t* parse_maps_line(const char* line)
{
  unsigned long int start;
  unsigned long int end;
  char permissions[5];
  int name_pos;
  if (sscanf(line, "%lx-%lx %4s %*x %*x:%*x %*d%n", &start, &end,
             permissions, &name_pos) != 3) {
    return NULL;
  }

  while (isspace(line[name_pos])) {
    name_pos += 1;
  }
  const char* name = line + name_pos;
  size_t name_len = strlen(name);
  if (name_len && name[name_len - 1] == '\n') {
    name_len -= 1;
  }

  backtrace_map_info_t* mi = calloc(1, sizeof(backtrace_map_info_t) + name_len + 1);
  if (mi) {
    mi->start = start;
    mi->end = end;
    mi->is_readable = strlen(permissions) == 4 && permissions[0] == 'r';
    mi->is_writable = strlen(permissions) == 4 && permissions[1] == 'w';
    mi->is_executable = strlen(permissions) == 4 && permissions[2] == 'x';
    memcpy(mi->name, name, name_len);
    mi->name[name_len] = '\0';
    printf("Parsed map: start=0x%08x, end=0x%08x, "
          "is_readable=%d, is_writable=%d, is_executable=%d, name=%s",
          mi->start, mi->end,
          mi->is_readable, mi->is_writable, mi->is_executable, mi->name);
  }
  return mi;
}

backtrace_map_info_t* backtrace_create_map_info_list(pid_t tid) {
  char path[PATH_MAX];
  char line[1024];
  FILE* fp;
  backtrace_map_info_t* milist = NULL;

  if (tid < 0) {
    tid = getpid();
  }
  snprintf(path, PATH_MAX, "/proc/%d/maps", tid);
  fp = fopen(path, "r");
  if (fp) {
    while(fgets(line, sizeof(line), fp)) {
      backtrace_map_info_t* mi = parse_maps_line(line);
      if (mi) {
        mi->next = milist;
        milist = mi;
      }
    }
    fclose(fp);
  }
  return milist;
}


void backtrace_destroy_map_info_list(backtrace_map_info_t* milist) {
  while (milist) {
    backtrace_map_info_t* next = milist->next;
    free(milist);
    milist = next;
  }
}

const backtrace_map_info_t* backtrace_find_map_info(
    const backtrace_map_info_t* milist, uintptr_t addr) {
  const backtrace_map_info_t* mi = milist;
  while (mi && !(addr >= mi->start && addr < mi->end)) {
    mi = mi->next;
  }
  return mi;
}
