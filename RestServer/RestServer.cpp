#include <iostream>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include <boost/asio/ip/host_name.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::map<utility::string_t, utility::string_t> dictionary;

std::string c_hostName;

struct GetHandler
{
    GetHandler()
    {
        m_hostName  = boost::asio::ip::host_name();
    }

    void operator()(http_request request)
    {
        std::string msg = "Node " + m_hostName + " ready to serve!";
        request.reply(status_codes::OK, msg);
    }

private:
    std::string m_hostName;
};

int main()
{
    std::cout << "\nStarting ...\n";
    http_listener listener(L"http://*:9009/processrequest");

    GetHandler getHandler;
    listener.support(methods::GET, getHandler);

    try
    {
        listener
            .open()
            .then([&listener]() {std::cout<<"\nstarting to listen\n"; })
            .wait();

        while (true);
    }
    catch (std::exception const & e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    std::cout << "\nExiting ...\n";
    return 0;
}