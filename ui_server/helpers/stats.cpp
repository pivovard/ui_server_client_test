#include "stats.h"

int idle_prev = 0;
int nidle_prev = 0;

std::pair<int,int> get_cpu_stat()
{
	std::ifstream file;
	std::string line;
	std::string cpu;
	int val;
	std::vector<int> data;

	try
	{
		file.open("/proc/stat");
		getline(file, line); // get first line (sum of all CPUs)

		std::stringstream stream(line);
		stream >> cpu; // first column is a name of the CPU which is not needed

		while (stream >> val)
		{
			data.push_back(val);
		}
	}
	catch (const std::exception& e)
	{
		LOG_ERROR(e.what());
	}

	file.close();

	// pair<idle, nidle>
	std::pair<int, int> res;

	//user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
	if (data.size() == CPU_STAT_SIZE) {
		res.first = data[3] + data[4]; //idle
		res.second = data[0] + data[1] + data[2] + data[5] + data[6]; //nidle
	}
	else {
		// res == <0,0>
		LOG_ERROR("Failed to load the cpu stats.");
	}

	return res;
}

void init_cpu_stat()
{
	std::pair<int,int> data = get_cpu_stat();

	idle_prev = data.first;
	nidle_prev = data.second;
	
}

float get_cpu_usage()
{
	std::pair<int, int> data = get_cpu_stat();

	int idle = data.first;
	int nidle = data.second;

	int total = idle + nidle;
	int total_prev = idle_prev + nidle_prev;

	int total_d = total - total_prev;
	int idle_d = idle - idle_prev;

	float CPU_Percentage = (total_d - idle_d) / (float)total_d;

	idle_prev = idle;
	nidle_prev = nidle;

	return CPU_Percentage * 100;
}

int get_mem_usage()
{
	std::ifstream file;
	std::string line;
	std::string item;
	int val;
	std::map<std::string, int> data;

	try
	{
		// get mem data and store them in the map
		file.open("/proc/meminfo");
		while (getline(file, line))
		{
			std::stringstream stream(line);
			stream >> item;
			stream >> val;

			data.emplace(item, val);
		}
	}
	catch (const std::exception& e)
	{
		LOG_ERROR(e.what());
	}

	file.close();

	int res = 0;

	if (data.size() > 0) {
		res = data["MemTotal:"] - data["MemFree:"] - data["Buffers:"] - data["Cached:"];
	}
	else {
		LOG_ERROR("Failed to load the mem stats.");
	}

	return res;
}