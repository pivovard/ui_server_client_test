#include <boost/asio.hpp>

#include "helpers/logger.h"
#include "helpers/stats.h"
#include "tcp/tcp_server.h"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	// Init logging
	init_logger(); // call init_logger(false); to redirect log to stdout
	LOG_INFO("Server initialization.")

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
			return 1;
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
	    return 1;
	}

	return 0;
}
