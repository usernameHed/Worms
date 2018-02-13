#ifndef TEMPLATE
#define TEMPLATE

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>

//size(somzthing)
template<class T, size_t N> //template to get the size of EVERYTHING
size_t size(T (&)[N])
{
  return (N);
}

//////////////////////////////////////////////////////template swap
template<typename T>
void swap(T &a, T &b)
{
  T tmp = a;
  a = b;
  b = tmp;
}

//////////////////////////////////////////////////////template min
template<typename T>
const T & min(const T & a, const T & b)
{
  if (a >= b)
    return (b);
  return (a);
}

template<typename T>
const T & min3(const T & x, const T & y, const T & z)
{
  return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

//////////////////////////////////////////////////////template max
template<typename T>
const T & max(const T & a, const T & b)
{
  if (a >= b)
    return (a);
  return (b);
}

template<typename T>
const T max3(const T & a, const T & b, const T & c)
{
  T max = ( a < b ) ? b : a;
  return ( ( max < c ) ? c : max );
}

//////////////////////////////////////////////////////template add
template<typename T>
T add(const T & a, const T & b)
{
  return (a + b);
}

//////////////////////////////////////////////////////template compare
template<typename T>
int compare(const T &a, const T &b)
{
  return (a == b) ? 0 : ((a < b) ? -1 : 1);
}

//////////////////////////////////////////////////////template print
template<typename T>
void print(const T &toPrint)
{
  std::cout << toPrint << std::endl;
}

//////////////////////////////////////////////////////template foreach
template<typename T>
void foreach(const T *array, void (*print)(const T &), int size)
{
  int i = -1;
  while (++i < size)
    (*print)(array[i]);
}

//////////////////////////////////////////////////////compare
template<typename T>
bool equal(const T &a, const T &b)
{
  if (a == b)
    return (true);
  return (false);
}

//////////////////////////////////////////////////////factorial
//int x = Factorial<4>::value;
template <int N>
struct Factorial
{
  enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0>
{
  enum { value = 1 };
};

///////////////////////////////////////////////////////int to string
template <typename T> std::string tostr(const T& t)
{
  std::ostringstream os;
  os<<t;
  return os.str();
}

//debug to_string
namespace patch
{
    template <typename T> std::string to_string(const T& n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

//display list
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


#endif // TEMPLATE
