#include <regex>
#include "parse.hpp"

parse_echo::parse_echo(string response)
{
	// example response :
        // A0.36.119.86.79.213/000001001/N**M*/**///4
	const regex rgx( "A(([0-9a-fA-F]\.){6})/([0-9]*)/(.*)/.*" );
	smatch index_match;
	bool is_match = std::regex_match(response, index_match, rgx);
	if ( is_match ){
		mac_addr_ = index_match[1].str();
		port_ = index_match[2].str();
		misc_ = index_match[3].str();
	}

}
