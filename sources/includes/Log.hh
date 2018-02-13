#ifndef _LOG_HH_
#define _LOG_HH_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

class Log
{
private:
  std::ofstream out;
public:
    Log();
    ~Log();

    void loadGame(const char *file);
    void log(const char *text);
};


#endif /* !_HH */
