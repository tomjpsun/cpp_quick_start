//
// main.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "asio.hpp"
#include <atomic>
#include "parse.hpp"
using asio::ip::udp;

int main(int argc, char* argv[])
{
	asio::io_context io_context;
	asio::error_code error;
	asio::ip::udp::socket socket(io_context);
	int port = 65535;
	const int max_length = 1024;
	double timeout_sec = 1.8;
	std::atomic<bool> continue_polling_readers{ true };
	char data[] = {'X'};

	socket.open(asio::ip::udp::v4(), error);
	if (!error)
	{
		// broadcast for reader info
		socket.set_option(asio::ip::udp::socket::reuse_address(true));
		socket.set_option(asio::socket_base::broadcast(true));
		asio::ip::udp::endpoint senderEndpoint(
			asio::ip::address_v4::broadcast(), port);
		socket.send_to(asio::buffer(data), senderEndpoint);

		// waiting for reader data coming
		using namespace std::this_thread;
		using namespace std::chrono;
		sleep_for(milliseconds(100));

		// start timer
		auto start = std::chrono::system_clock::now();

		while( continue_polling_readers ) {

			// compare if timeout
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			if (elapsed_seconds.count() > timeout_sec)
				continue_polling_readers = false;; // timeout, leave this loop

			char reply[max_length];
			std::memset(reply, 0, max_length);
			udp::endpoint sender_endpoint;

			try {
				// pre scan how many bytes can be read, prevent from blocking
				asio::socket_base::bytes_readable has_response(true);
				socket.io_control(has_response);
				std::size_t bytes_readable = has_response.get();
				if (bytes_readable) {
					size_t reply_length = socket.receive_from(
						asio::buffer(reply, bytes_readable), sender_endpoint);
					asio::ip::address sender_address = sender_endpoint.address();
					string ip_addr = sender_address.to_string();
					std::cout << "(" << ip_addr << ") "
						  << reply << std::endl;
					parse_echo p{ip_addr, reply};
				}
			} catch (asio::error_code& ec) {
				// should not happen
				std::cout << "error code = " << ec
					  << " message: " << ec.message() << std::endl;
				continue_polling_readers = false;
			}

		}
		socket.close(error);
	}
}
