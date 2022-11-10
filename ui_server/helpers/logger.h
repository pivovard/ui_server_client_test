#pragma once

#include <boost/log/trivial.hpp>
#include <ctime>
#include <string.h>

inline char* get_time() {
	time_t sys_time = time(0); //get system time
	char* time = std::ctime(&sys_time); //time to string
	time[strlen(time) - 1] = '\0'; //remove \n at the end of the string
	return time;
}

#define LOG_INFO(msg)    BOOST_LOG_TRIVIAL(info)    << "INFO:    [" << get_time() << "] - " << msg;
#define LOG_WARNING(msg) BOOST_LOG_TRIVIAL(warning) << "WARNING: [" << get_time() << "] - " << msg;
#define LOG_ERROR(msg)   BOOST_LOG_TRIVIAL(error)   << "ERROR:   [" << get_time() << "] - " << msg;
#define LOG_FATAL(msg)   BOOST_LOG_TRIVIAL(fatal)   << "FATAL:   [" << get_time() << "] - " << msg;