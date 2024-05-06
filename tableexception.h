#pragma once

#include <exception>
#include <string>

class TableException : public std::exception {
public:
    TableException(const char* messg);

private:
    std::string m_message;
};