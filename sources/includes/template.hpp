#ifndef _TEMPLATE_HPP_
# define _TEMPLATE_HPP_

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

template <class T>
inline void printList(const T& coll, const char* optcstr="\n")
{
    typename T::const_iterator pos;

    bool start = true;
    for (pos=coll.begin(); pos!=coll.end(); ++pos)
    {
        if (!start)
            std::cout << optcstr;
        std::cout << *pos;
        start = false;
    }
    std::cout << std::endl;
}

#endif /* !TEMPLATE_HPP_ */
