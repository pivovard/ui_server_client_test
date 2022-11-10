#include "ui_server.h"

using namespace std;
using boost::asio::ip::tcp;

int main()
{
	// Init logging
	boost::log::add_file_log("info.log");
	boost::log::core::get()->set_filter
	(
		boost::log::trivial::severity >= boost::log::trivial::info
	);

	LOG_INFO("Server init.")

    // Initialize starting data of the cpu usage
    init_cpu_stat();

	boost::asio::io_context io_context;

	tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 5001));
	for (;;)
	{
		std::string message = "test";
		tcp::socket socket(io_context);
		acceptor.accept(socket);
		boost::system::error_code error;
		boost::asio::write(socket, boost::asio::buffer(message), error);
	}

	return 0;
}
