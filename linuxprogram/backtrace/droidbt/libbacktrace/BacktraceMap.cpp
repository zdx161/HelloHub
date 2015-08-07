/*
 * Copyright (C) 2014 The Android Open Source Project
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
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <vector>

#include <backtrace/backtrace_constants.h>
#include <backtrace/BacktraceMap.h>
//#include <log/log.h>

#include "thread_utils.h"
#include "BacktraceImpl.h"

BacktraceMap::BacktraceMap(pid_t pid) : pid_(pid) {
  if (pid_ < 0) {
    pid_ = getpid();
  }
}

BacktraceMap::~BacktraceMap() {
}

const backtrace_map_t* BacktraceMap::Find(uintptr_t addr) {
  for (BacktraceMap::const_iterator it = begin();
       it != end(); ++it) {
    if (addr >= it->start && addr < it->end) {
      return &*it;
    }
  }
  return NULL;
}

bool BacktraceMap::ParseLine(const char* line, backtrace_map_t* map) {
  unsigned long int start;
  unsigned long int end;
  char permissions[5];
  int name_pos;

// Linux /proc/<pid>/maps lines:
// 6f000000-6f01e000 rwxp 00000000 00:0c 16389419   /system/lib/libcomposer.so\n
// 012345678901234567890123456789012345678901234567890123456789
// 0         1         2         3         4         5
  if (sscanf(line, "%lx-%lx %4s %*x %*x:%*x %*d%n",
             &start, &end, permissions, &name_pos) != 3) {
    return false;
  }

  map->start = start;
  map->end = end;
  map->flags = PROT_NONE;
  if (permissions[0] == 'r') {
    map->flags |= PROT_READ;
  }
  if (permissions[1] == 'w') {
    map->flags |= PROT_WRITE;
  }
  if (permissions[2] == 'x') {
    map->flags |= PROT_EXEC;
  }

  while (isspace(line[name_pos])) {
    name_pos += 1;
  }
  map->name = line+name_pos;
  if (!map->name.empty() && map->name[map->name.length()-1] == '\n') {
    map->name.erase(map->name.length()-1);
  }

  printf("Parsed map: start=%p, end=%p, flags=%x, name=%s",
        reinterpret_cast<void*>(map->start), reinterpret_cast<void*>(map->end),
        map->flags, map->name.c_str());
  return true;
}

bool BacktraceMap::Build() {
  char path[sizeof(pid_t)*3 + sizeof("/proc//maps") + 1];
  char line[1024];

  // path is guaranteed to always be big enough to hold this string.
  snprintf(path, sizeof(path), "/proc/%d/maps", pid_);
  FILE* fp = fopen(path, "r");
  if (fp == NULL) {
    return false;
  }

  while(fgets(line, sizeof(line), fp)) {
    backtrace_map_t map;
    if (ParseLine(line, &map)) {
      maps_.push_back(map);
    }
  }
  fclose(fp);

  return true;
}
