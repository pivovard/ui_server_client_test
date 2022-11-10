#include "ui_client.h"

using boost::asio::ip::tcp;
using namespace std;

/**
* Send command to the server and receive a response.
*
* @param socket
* @param command
*/
void send_command(tcp::socket& socket, string &c)
{
    // send command to the server
    boost::array<char, 4> buff_in;
    c += "\n"; //command should end by \n
    std::copy(c.begin(), c.end(), buff_in.begin());
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(buff_in, c.size()), error);
    
    if (error) {
        throw boost::system::system_error(error);
    }
    
    // receive response
    size_t len = socket.read_some(boost::asio::buffer(buff_in), error);
    
    if (error) {
        throw boost::system::system_error(error);
    }
    
    std::cout.write(buff_in.data(), len);
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
    cout << "Enter command cpu/mem/exit." << endl;
    while (true) 
    {
        // Get next command
        cout << "Command: ";
        string input;
        cin >> input;

        // send command to the server
        if (!input.compare("cpu") || !input.compare("mem")) {
            send_command(socket, input);
        }
        // end loop on exit
        else if (!input.compare("exit")) {
            break;
        }
        else {
            cout << "Invalid command." << endl;
        }
    }
}

/**
* Entry point of the client.
* Initialize connection with the server.
* If succesfull execute commands in loop.
*/
int main()
{
    // Init socket
    boost::asio::io_context io_context;
    tcp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), 5001);
    tcp::socket socket(io_context);

    try
    {
        socket.connect(endpoint);

        if (socket.is_open()) {
            cout << "Connected." << endl;
            commands(socket); // execute commands in loop
        }
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    cout << "Closing socket." << endl;
    socket.close();

	return 0;
}