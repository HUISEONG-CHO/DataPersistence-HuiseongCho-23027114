#pragma once
#include "IRepository.h"
#include "model/Record.h"
#include <string>
#include <vector>

class JsonRepository : public IRepository<Record> {
public:
    explicit JsonRepository(const std::string& filePath);

    void           save(const Record& item)            override;
    Record         findById(int id) const              override;
    std::vector<Record> findAll() const                override;
    void           update(int id, const Record& item)  override;
    void           remove(int id)                      override;

private:
    std::string filePath;
    std::vector<Record> records;

    void loadFromFile();
    void saveToFile() const;
};
