#include "ui_server.h"
using namespace std;


/**
* Get data from /proc/stat.
* 
* @return vector of int data
*/
std::vector<int> get_cpu_stat()
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
		stream >> cpu; // first column is a name of the CPU

		while (stream >> val) 
		{
			data.push_back(val);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	file.close();

	return data;
}

/**
* Calculates CPU usage in percentage from /proc/stat.
* 
* @return CPU usage in percentage
*/
float get_cpu_usage() 
{
	std::vector<int> data = get_cpu_stat();

	//user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
	int idle = data[3] + data[4];
	int nidle = data[0] + data[1] + data[2] + data[5] + data[6];

	int total = idle + nidle;
	int total_prev = idle_prev + nidle_prev;

	int total_d = total - total_prev;
	int idle_d = idle - idle_prev;

	float CPU_Percentage = (total_d - idle_d) / (float)total_d;

	idle_prev = idle;
	nidle_prev = nidle;

	return CPU_Percentage * 100;
}

/**
* Calculates used memory in kB from /proc/meminfo
* MemUsed = MemTotal - MemFree - Buffers - Cached
*
* @return MemUsed
*/
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
		std::cerr << e.what() << std::endl;
	}

	file.close();

	return data["MemTotal:"] - data["MemFree:"] - data["Buffers:"] - data["Cached:"];
}

int main()
{
	// Initialize starting data of the cpu usage
	std::vector<int> data = get_cpu_stat();
	
	//user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
	idle_prev = data[3] + data[4];
	nidle_prev = data[0] + data[1] + data[2] + data[5] + data[6];
	
	cout << get_mem_usage() << endl;

	return 0;
}
