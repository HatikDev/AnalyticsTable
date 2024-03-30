#pragma once

#include <exception>

class TableException : public std::exception {
public:
    TableException(const char* messg);
};