#ifndef ERR_H_
#define ERR_H_

#include<iostream>
#include<cstdlib>
#include<string>

inline void err(const std::string &s)
{
	std::cout << "error: " << s << std::endl;
        exit(1);
}

#endif
