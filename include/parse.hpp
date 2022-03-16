#ifndef __parse_hpp__
#define __parse_hpp__
#include <string>

using namespace std;

class parse_echo
{
public:
	parse_echo(string response);
	string mac_addr_;
	string port_;
	string misc_;
};

#endif // __parse_hpp__
