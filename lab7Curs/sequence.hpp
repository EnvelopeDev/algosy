#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Sequence {
private:
    std::vector<T> data;

public:
    Sequence() = default;

    Sequence(std::initializer_list<T> lst) : data(lst) {}

    explicit Sequence(const std::vector<T>& v) : data(v) {}

    Sequence(const Sequence& other) = default;
    Sequence& operator=(const Sequence& other) = default;
    ~Sequence() = default;

    T& at(size_t pos) {
        if (pos < 1 || pos > data.size())
            throw std::out_of_range("Sequence::at — индекс вне диапазона");
        return data[pos - 1];
    }

    const T& at(size_t pos) const {
        if (pos < 1 || pos > data.size())
            throw std::out_of_range("Sequence::at — индекс вне диапазона");
        return data[pos - 1];
    }

    size_t size()  const { return data.size(); }
    bool   empty() const { return data.empty(); }
    void   push_back(const T& val) { data.push_back(val); }
    void   clear() { data.clear(); }

    bool operator==(const Sequence& other) const { return data == other.data; }
    bool operator!=(const Sequence& other) const { return !(*this == other); }

    Sequence concat(const Sequence& other) const {
        Sequence result(*this);
        for (const T& val : other.data)
            result.data.push_back(val);
        return result;
    }

    Sequence erase(size_t p1, size_t p2) const {
        if (p1 < 1 || p2 > data.size() || p1 > p2)
            throw std::out_of_range(
                "Sequence::erase — некорректные границы [p1, p2]");

        Sequence result;
        for (size_t i = 0; i < data.size(); ++i) {
            size_t pos = i + 1;
            if (pos < p1 || pos > p2)
                result.data.push_back(data[i]);
        }
        return result;
    }

    Sequence excl(const Sequence& sub) const {
        if (sub.empty() || sub.size() > data.size())
            return *this;

        size_t n = data.size();
        size_t m = sub.data.size();

        for (size_t i = 0; i + m <= n; ++i) {
            bool match = true;
            for (size_t j = 0; j < m && match; ++j)
                if (!(data[i + j] == sub.data[j])) match = false;

            if (match)
                return erase(i + 1, i + m);
        }

        return *this;
    }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data[i];
        }
        std::cout << "]";
    }
};
