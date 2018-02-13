#include "IaThinking.hh"

IaThinking::IaThinking()
{

}

IaThinking::~IaThinking()
{

}

LUARes IaThinking::getIaMove() const
{
  return (this->iaMove);
}

void IaThinking::setIaMove(LUARes move)
{
  this->iaMove = move;
}

bool IaThinking::getAttack() const
{
  return (this->attack);
}

void IaThinking::setAttack(bool att)
{
  this->attack = att;
}
