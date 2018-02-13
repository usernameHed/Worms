#include "Log.hh"

Log::Log()
{

}

Log::~Log()
{

}

void Log::loadGame(const char *file)
{
  this->out.open(file, std::ios::app);
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  //  this->out << "\n------ " << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << " ------" << std::endl;
  this->log("fu");
  this->log("ck");
}

void Log::log(const char *text)
{
  this->out << text;
}
