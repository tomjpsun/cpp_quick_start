#ifndef __parse_hpp__
#define __parse_hpp__
#include <string>

using namespace std;

class ParseEcho
{
public:
	ParseEcho(string ip, string response);
	string ip_addr_;
	string mac_addr_;
	string port_;
	string misc_;
};

#endif // __parse_hpp__
