#ifndef RESULT_H
#define RESULT_H

#include <vector>

#include <QString>

class Result {
public:
    Result(QString name);
    Result(const Result& result) = default;
    Result(Result&& result) noexcept;
    Result& operator=(const Result& result) = default;
    Result& operator=(Result&& result) noexcept;
    ~Result() = default;

    void add(size_t index);

    const QString& name() const;

    const std::unordered_map<size_t, size_t>& data() const;

private:
    QString m_name;
    // key is index of class and value is count of keys
    std::unordered_map<size_t, size_t> m_data;
};

#endif // RESULT_H