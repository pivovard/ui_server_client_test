#pragma once

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "tcp_connection.h"
#include "../helpers/stats.h"

using boost::asio::ip::tcp;

class tcp_server
{
public:
    /**
    * Initialize server and start listening on the given port.
    * 
    * @param io_context
    * @param port
    */
    tcp_server(boost::asio::io_context& io_context, int port) : io_context(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

private:
    /**
    * Create new tcp_connection instance with a socket.
    * Asynchronously listen for a client to connect
    */
    void start_accept();

    /**
    * On client connection start a service routine.
    * 
    * @param pointer to tcp_connection instance
    * @param error code
    */
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);

    boost::asio::io_context& io_context;
    tcp::acceptor acceptor;
};