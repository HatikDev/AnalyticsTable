#include "result.h"

Result::Result(QString name)
    : m_name{ std::move(name) } {}

Result::Result(Result&& result) noexcept
    : m_name{ std::move(result.m_name) }, m_data{ std::move(result.m_data) } {}

Result& Result::operator=(Result&& result) noexcept
{
    m_name = std::move(result.m_name);
    m_data = std::move(result.m_data);

    return *this;
}

void Result::add(size_t index)
{
    if (m_data.find(index) == m_data.end())
        m_data[index] = 1;
    else
        ++m_data[index];
}

const QString& Result::name() const
{
    return m_name;
}

const std::unordered_map<size_t, size_t>& Result::data() const
{
    return m_data;
}
