#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

int idle_prev = 0;
int nidle_prev = 0;

struct CpuStat
{
	int user;
	int nice;
	int system;
	int idle;
	int iowait;
	int irq;
	int softirg;
	int steal;
	int guest;
	int guest_nice;
};