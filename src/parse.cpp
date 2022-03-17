#include <regex>
#include <iostream>
#include "parse.hpp"

using namespace std;

ParseEcho::ParseEcho(string ip_addr, string response)
{
	// example response :
        // A0.36.119.86.79.213/000001001/N**M*/**///4
	const regex rgx( "A(([0-9a-fA-F]+.){5}[0-9a-fA-F]+)/([0-9]*)/(.*)/.*" );
	smatch index_match;
	bool is_match = std::regex_match(response, index_match, rgx);
	if ( is_match ){
		ip_addr_ = ip_addr;
		mac_addr_ = index_match[1].str();
		port_ = index_match[3].str();
		misc_ = index_match[4].str();
		cout << "ip_addr_ = " << ip_addr_ << endl
		     << "mac_addr_ = " << mac_addr_ << endl
		     << "port_ = " << port_ << endl
		     << "misc_ " << misc_ << endl;
	}
	else cout << "unmatched " << endl;

}
