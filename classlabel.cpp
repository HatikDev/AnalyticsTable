#include "classlabel.h"

ClassLabel::ClassLabel(std::string name, size_t index)
    : m_name{ std::move(name) }, m_index{ index } {}

ClassLabel::ClassLabel(ClassLabel&& label) noexcept
    : m_name{ std::move(label.m_name) }, m_index{ label.m_index } {}

ClassLabel& ClassLabel::operator=(ClassLabel&& label) noexcept
{
    m_name = std::move(label.m_name);
    m_index = label.m_index;

    return *this;
}

const std::string& ClassLabel::name() const
{
    return m_name;
}

size_t ClassLabel::index() const
{
    return m_index;
}
