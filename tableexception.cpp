#include "tableexception.h"

TableException::TableException(const char* messg)
     : std::exception(messg) {}
{
}
