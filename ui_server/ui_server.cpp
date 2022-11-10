#include <boost/asio.hpp>

#include "helpers/logger.h"
#include "helpers/stats.h"
#include "tcp/tcp_server.h"

using boost::asio::ip::tcp;

int main()
{
	// Init logging
	init_logger(false); // call init_logger(false); to redirect log to stdout
	LOG_INFO("Server initialization.")

    // Initialize starting data of the cpu usage
    init_cpu_stat();

	int port = 5001;

	LOG_INFO("Server starting at port " + std::to_string(port))
	try
	{
		boost::asio::io_context io_context;
		tcp_server server(io_context, port);
		io_context.run();
	}
	catch (std::exception& e)
	{
		LOG_ERROR(e.what())
	}

	return 0;
}
