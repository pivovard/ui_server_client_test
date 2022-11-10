#include "tcp_server.h"

void tcp_server::start_accept()
{
    // create ne connection
    tcp_connection::pointer new_connection = tcp_connection::create(io_context);

    // async listen for a client to connect
    acceptor.async_accept(new_connection->socket(), boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
    LOG_INFO("Listening...")
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error) {
        LOG_INFO("Connection accepted.")
            new_connection->start();
    }
    else {
        LOG_ERROR(boost::system::system_error(error).what())
    }

    start_accept(); // listen to next connection
}