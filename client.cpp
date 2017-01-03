


#include <boost/asio.hpp>
#include <beast/core/to_string.hpp>
#include <beast/websocket.hpp>
#include <iostream>
#include <string>

int main()
{
    // Normal boost::asio setup
    std::string const host = "localhost";
    std::string incoming_message;
    std::string outgoing_message="RCV ACK: ";
    
    boost::asio::io_service ios;
    boost::asio::ip::tcp::resolver r{ios};
    boost::asio::ip::tcp::socket sock{ios};
    boost::asio::connect(sock,
        r.resolve(boost::asio::ip::tcp::resolver::query{host, "9002"}));

    // Upgrading to websocket
    beast::websocket::stream<boost::asio::ip::tcp::socket&> ws{sock};
    ws.handshake(host, "/");
    

    // Receive WebSocket message, print and close using beast
    beast::streambuf sb;
    beast::websocket::opcode op;
    ws.read(op, sb);
    incoming_message= beast::to_string(sb.data());
    std::cout << incoming_message << "\n";
    outgoing_message += incoming_message;
    ws.write(boost::asio::buffer(outgoing_message));
    ws.close(beast::websocket::close_code::normal);
    std::cout<<"Connection Closed\n";
}
