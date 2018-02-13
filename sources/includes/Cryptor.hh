#ifndef _CRYPTOR_HH_
#define _CRYPTOR_HH_

#include <iostream>

enum TypeCrypt
{
  CRYPT = 0,
  UNCRYPT = 1,
};

class Cryptor
{
protected:
  unsigned long long int key = 4200000000000000042;
public:
  Cryptor(std::string &str);
  Cryptor(std::string &str, const TypeCrypt &type);
  ~Cryptor();

  void crypt(std::string &str) const;
  void uncrypt(std::string &str) const;
};


#endif /* !Cryptor_HH_ */
