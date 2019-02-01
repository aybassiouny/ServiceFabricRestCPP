// HelloSF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#pragma comment(lib, "cpprest_2_10")

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::map<utility::string_t, utility::string_t> dictionary;

void handle_get(http_request request)
{
    std::cout<<"\nHandling a GET request\n";
    request.reply(status_codes::OK, "Got a request!");
}

int main()
{
    std::cout << "\nStarting ...\n";
    //http_listener listener(L"http://*:8888/restdemo");
    http_listener listener(L"http://127.0.0.1:8888/restdemo");

    listener.support(methods::GET, handle_get);

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
    }

    std::cout << "\nExiting ...\n";
    return -1;
}