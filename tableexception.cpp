#include "tableexception.h"

TableException::TableException(const char* messg)
    : std::exception(), m_message{ messg } {}
const char* TableException::what() const
{
    return m_message.c_str();
}
{
}
