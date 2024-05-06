#include "tableexception.h"

TableException::TableException(const char* messg)
    : m_message{ messg } {}

const char* TableException::what() const noexcept
{
    return m_message.c_str();
}
