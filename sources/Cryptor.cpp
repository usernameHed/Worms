#include "Cryptor.hh"

Cryptor::Cryptor(std::string &str)
{
  this->crypt(str);
}

Cryptor::Cryptor(std::string &str, const TypeCrypt &type)
{
  (void)type;
  this->crypt(str);
}

Cryptor::~Cryptor()
{

}

void Cryptor::crypt(std::string &toBeCrypt) const
{
  unsigned int i = 0;
  while (i < toBeCrypt.length())
  {
    toBeCrypt[i] = toBeCrypt[i] ^ this->key;
    i++;
  }
}
