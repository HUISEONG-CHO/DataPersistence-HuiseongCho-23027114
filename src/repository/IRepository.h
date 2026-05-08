#pragma once
#include <vector>

template <typename T>
class IRepository {
public:
    virtual void           save(const T& item)            = 0;
    virtual T              findById(int id) const         = 0;
    virtual std::vector<T> findAll() const                = 0;
    virtual void           update(int id, const T& item)  = 0;
    virtual void           remove(int id)                 = 0;
    virtual ~IRepository() = default;
};
