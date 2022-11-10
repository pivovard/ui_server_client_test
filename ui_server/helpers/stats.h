#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "logger.h"

constexpr int CPU_STAT_SIZE = 10;

/**
* Get data from /proc/stat.
*
* @return pair<idle, nidle>
*/
std::pair<int, int> get_cpu_stat();

/**
* Initialize starting data of the cpu usage
*/
void init_cpu_stat();

/**
* Calculates CPU usage in percentage from /proc/stat.
*
* @return CPU usage in percentage
*/
float get_cpu_usage();

/**
* Calculates used memory in kB from /proc/meminfo
* MemUsed = MemTotal - MemFree - Buffers - Cached
*
* @return MemUsed
*/
int get_mem_usage();