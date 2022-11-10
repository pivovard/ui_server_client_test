#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <boost/asio.hpp>

#include "helpers/logger.h"
#include "helpers/stats.h"
#include "tcp/tcp_server.h"

using boost::asio::ip::tcp;

/* Fork and create damon */
void daemon() 
{
	pid_t pid = fork();

	// Child
	if (pid == 0) {
		// ignore SIGHUP signal so when parent process exits child is not terminated
		signal(SIGHUP, SIG_IGN);
	}

	// Terminate parent process
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	// Error
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	LOG_INFO("Daemon created.")
}

int main(int argc, char* argv[])
{
	// Init logging
	init_logger(); // call init_logger(false); to redirect log to stdout
	LOG_INFO("Server initialization.")

	// Create daemon
	daemon();

    // Initialize starting data of the cpu usage
    init_cpu_stat();

	int port = 5001;

	// get port from command line arguments
	if (argc == 2)
	{
		try
		{
			port = std::stoi(argv[1]);
		}
		catch (const std::exception& e)
		{
			LOG_FATAL("Unable to resolve port number.")
			return 2;
		}
	}

	LOG_INFO("Server starting at port " + std::to_string(port))
	try
	{
		boost::asio::io_context io_context;
		tcp_server server(io_context, port);
		io_context.run();
	}
	catch (std::exception& e)
	{
		LOG_FATAL(e.what())
	    return 2;
	}

	return 0;
}
