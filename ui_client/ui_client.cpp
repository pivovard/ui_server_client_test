#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

/**
* Send command to the server and receive a response.
*
* @param socket
* @param command
*/
void send_command(tcp::socket& socket, std::string &c)
{
    boost::system::error_code error;

    // send command to the server
    c += "\n"; //command should end by \n
    socket.write_some(boost::asio::buffer(c, c.size()), error);
    
    if (error) {
        throw boost::system::system_error(error);
    }
    
    // receive response
    boost::asio::streambuf buff_in;
    size_t len = boost::asio::read_until(socket, buff_in, '\n', error);
    
    if (error) {
        throw boost::system::system_error(error);
    }

    std::istream stream(&buff_in);
    std::string res;
    getline(stream, res);
    
    std::cout << res << std::endl;;
}

/**
* In loop read command from the command line and evaluate it.
* If command is cpu or mem send it to the server.
* exit command breaks the loop.
* 
* @param socket
*/
void commands(tcp::socket& socket)
{
    std::cout << "Enter command cpu/mem/exit." << std::endl;
    while (true) 
    {
        // Get next command
        std::cout << "Command: ";
        std::string input;
        std::cin >> input;

        if (input.compare("exit")) {
            send_command(socket, input);
        }
        // end loop on exit
        else {
            break;
        }
    }
}

/**
* Entry point of the client.
* Initialize connection with the server.
* If succesfull execute commands in loop.
*/
int main(int argc, char* argv[])
{
    // default address and port
    char* addr = "127.0.0.1";
    int port = 5001;

    // get address and port from command line arguments
    if (argc == 3)
    {
        addr = argv[1];
        try
        {
            port = std::stoi(argv[2]);
        }
        catch (const std::exception& e)
        {
            std::cout << "Unable to resolve port number." << std::endl;
            return 1;
        }
    }

    // Init and connect socket
    std::cout << "Connecting to " << addr << ":" << port << std::endl;

    boost::asio::io_context io_context;
    tcp::endpoint endpoint(boost::asio::ip::address::from_string(addr), port);
    tcp::socket socket(io_context);

    try
    {
        socket.connect(endpoint);

        if (socket.is_open()) {
            std::cout << "Connected." << std::endl;
            commands(socket); // execute commands in loop
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    // Close
    std::cout << "Closing socket." << std::endl;
    try
    {
        socket.shutdown(socket.shutdown_both);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    socket.close();

	return 0;
}