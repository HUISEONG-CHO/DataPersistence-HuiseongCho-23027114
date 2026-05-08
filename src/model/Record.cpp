#include "Record.h"

Record::Record() : id(0), name(""), value(0.0) {}

Record::Record(int id, const std::string& name, double value)
    : id(id), name(name), value(value) {}

int                Record::getId()    const { return id;    }
const std::string& Record::getName()  const { return name;  }
double             Record::getValue() const { return value; }
