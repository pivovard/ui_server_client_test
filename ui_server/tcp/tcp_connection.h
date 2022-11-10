#pragma once

#include <string>

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "../helpers/stats.h"

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    /**
    * Create new instance and return shared pointer.
    * 
    * @param io_context
    * @return shared_pointer to the new instance
    */
    static pointer create(boost::asio::io_context& io_context);

    /**
    * Entry point of the routine.
    * Asynchronously reads data from the client.
    */
    void start();

    /**
    * Return socket.
    *
    * @return socket
    */
    inline tcp::socket& socket()
    {
        return socket_;
    }

private:
    /**
    * Creates new instance, initialize client ID.
    * 
    * @param io_context
    */
    tcp_connection(boost::asio::io_context& io_context) : socket_(io_context)
    {
        ID = ++counter;
    }

    /**
    * Resolve command, get stat data and sent them to the client.
    * If command is not valid return -1.
    * 
    * @param command
    */
    void send_response(std::string& command);

    /**
    * Handler of async read function.
    * 
    * @param error code
    * @param number of bytes transferred
    */
    void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

    /**
    * Handler of async write function.
    * 
    * @param error code
    * @param number of bytes transferred
    */
    void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred);

    /**
    * Return ID as "[ID] "
    */
    inline std::string sID()
    {
        return "[" + std::to_string(ID) + "] ";
    }

    static int counter;

    int ID;
    tcp::socket socket_;
    boost::asio::streambuf buffer_;
};