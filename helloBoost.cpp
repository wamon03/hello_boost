#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio::ip;

int main() {
    try {
        boost::asio::io_context io_service;

        // 서버에서 사용할 TCP 소켓 및 포트
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "HTTP 서버가 시작되었습니다. http://localhost:8080 에 접속하세요.\n";

        while (true) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            // 요청을 읽어옴
            boost::asio::streambuf request;
            read_until(socket, request, "\r\n\r\n");

            // HTTP 응답

            std::string body = "<html><body><h1>Hello, Boost.Asio!</h1></body></html>";
            std::string response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: " + std::to_string(body.length()) + "\r\n";
            response += "\r\n";
            response += body;

            boost::asio::write(socket, boost::asio::buffer(response));
        }
    }
    catch (std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }

    return 0;
}