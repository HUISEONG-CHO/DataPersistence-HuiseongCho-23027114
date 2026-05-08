#pragma once
#include <string>

class Record {
public:
    Record();
    Record(int id, const std::string& name, double value);

    int                getId()   const;
    const std::string& getName() const;
    double             getValue() const;

private:
    int id;
    std::string name;
    double value;
};
