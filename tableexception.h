#pragma once

#include <exception>
#include <string>

class TableException : public std::exception {
public:
    TableException(const char* messg);

    virtual const char* what() const noexcept;

private:
    std::string m_message;
};