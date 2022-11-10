#include "tcp_connection.h"

int tcp_connection::counter = 0;

tcp_connection::pointer tcp_connection::create(boost::asio::io_context& io_context)
{
    return pointer(new tcp_connection(io_context));
}

void tcp_connection::start()
{
    auto addr = socket_.local_endpoint().address().to_string();
    LOG_INFO(sID() + addr)

        boost::asio::async_read_until(socket_, buffer_, "\n",
            boost::bind(&tcp_connection::handle_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

}

void tcp_connection::send_response(std::string& command)
{
    std::string output;

    // get stat data based on command
    if (!command.compare("cpu")) {
        auto res = get_cpu_usage();
        output = std::to_string(res);
    }
    else if (!command.compare("mem")) {
        auto res = get_mem_usage();
        output = std::to_string(res);
    }
    // non-valid comand returns -1
    else {
        output = std::to_string(-1);
    }

    // send
    LOG_INFO(sID() + "Send: " + output);

    output += '\n'; // end by \n

    boost::asio::async_write(socket_, boost::asio::buffer(output),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error)
    {
        // get received data
        std::istream stream(&buffer_);
        std::string input;
        std::getline(stream, input);

        LOG_INFO(sID() + "Recv: " + input);

        send_response(input);

        // read next
        boost::asio::async_read_until(socket_, buffer_, "\n",
            boost::bind(&tcp_connection::handle_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    else if (error == boost::asio::error::eof)
    {
        LOG_INFO(sID() + "Connection closed.")
    }
    else {
        LOG_ERROR(boost::system::system_error(error).what())
    }
}

void tcp_connection::handle_write(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        LOG_ERROR(boost::system::system_error(error).what())
    }
}