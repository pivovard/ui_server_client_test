#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <ctime>
#include <string.h>

/// Initialize logger
/// - set file
/// - set auto_flush true
/// - set severity 
inline void init_logger(bool file = true) {
	if (file) { // redirect outpu to the file
		auto sink = boost::log::add_file_log("info.log");
		sink->locked_backend()->auto_flush(true); // write to the log file on every log
	}
	boost::log::core::get()->set_filter
	(
		boost::log::trivial::severity >= boost::log::trivial::info
	);
}

/// Return current time as char*
inline char* get_time() {
	time_t sys_time = time(0); //get system time
	char* time = std::ctime(&sys_time); //time to string
	time[strlen(time) - 1] = '\0'; //remove \n at the end of the string
	return time;
}

#define LOG_INFO(msg)    BOOST_LOG_TRIVIAL(info)    << "INFO [" << get_time() << "] - " << msg;
#define LOG_WARNING(msg) BOOST_LOG_TRIVIAL(warning) << "WARNING [" << get_time() << "] - " << msg;
#define LOG_ERROR(msg)   BOOST_LOG_TRIVIAL(error)   << "ERROR [" << get_time() << "] - " << msg;
#define LOG_FATAL(msg)   BOOST_LOG_TRIVIAL(fatal)   << "FATAL [" << get_time() << "] - " << msg;