#include "JsonRepository.h"
#include "json/json.h"
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

JsonRepository::JsonRepository(const std::string& filePath) : filePath(filePath) {
    if (fs::exists(filePath)) loadFromFile();
}

void JsonRepository::loadFromFile() {
    JsonValue data = Json::parseFile(filePath);
    for (size_t i = 0; i < data.size(); ++i) {
        int         id    = static_cast<int>(data[i]["id"].asDouble());
        std::string name  = data[i]["name"].asString();
        double      value = data[i]["value"].asDouble();
        records.emplace_back(id, name, value);
    }
}

void JsonRepository::saveToFile() const {
    JsonValue arr = JsonValue::makeArray();
    for (const auto& r : records) {
        JsonValue obj = JsonValue::makeObject();
        obj["id"]    = JsonValue(static_cast<double>(r.getId()));
        obj["name"]  = JsonValue(r.getName());
        obj["value"] = JsonValue(r.getValue());
        arr.push(obj);
    }
    Json::saveFile(arr, filePath, true);
}

void JsonRepository::save(const Record& item) {
    records.push_back(item);
    saveToFile();
}

Record JsonRepository::findById(int id) const {
    for (const auto& r : records)
        if (r.getId() == id) return r;
    throw std::runtime_error("Record not found: " + std::to_string(id));
}

std::vector<Record> JsonRepository::findAll() const {
    return records;
}

void JsonRepository::update(int id, const Record& item) {
    for (auto& r : records) {
        if (r.getId() == id) { r = item; saveToFile(); return; }
    }
    throw std::runtime_error("Record not found: " + std::to_string(id));
}

void JsonRepository::remove(int id) {
    auto it = std::remove_if(records.begin(), records.end(),
        [id](const Record& r) { return r.getId() == id; });
    records.erase(it, records.end());
    saveToFile();
}
