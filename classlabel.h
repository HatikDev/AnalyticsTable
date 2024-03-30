#ifndef CLASSLABEL_H
#define CLASSLABEL_H

#include <string>

class ClassLabel {
public:
    ClassLabel(std::string name, size_t index);
    ClassLabel(const ClassLabel& label) = default;
    ClassLabel(ClassLabel&& label) noexcept;
    ClassLabel& operator=(const ClassLabel& label) = default;
    ClassLabel& operator=(ClassLabel&& label) noexcept;
    ~ClassLabel() = default;

    const std::string& name() const;

    size_t index() const;

private:
    std::string m_name;
    size_t m_index;
};

#endif // CLASSLABEL_H