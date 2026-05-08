#include "repository/JsonRepository.h"
#include <iostream>

static void printAll(const std::string& label, JsonRepository& repo) {
    std::cout << "\n[" << label << "]\n";
    auto records = repo.findAll();
    if (records.empty()) {
        std::cout << "  (empty)\n";
        return;
    }
    for (const auto& r : records) {
        std::cout << "  ID=" << r.getId()
                  << " | Name=" << r.getName()
                  << " | Value=" << r.getValue() << "\n";
    }
}

int main() {
    const std::string dataFile = "records.json";

    // ── Scenario 1: Record 3개 저장 ─────────────────────────────
    std::cout << "=== Scenario 1: Save 3 Records ===";
    {
        JsonRepository repo(dataFile);
        repo.save(Record(1, "Temperature", 36.5));
        repo.save(Record(2, "Pressure",   101.3));
        repo.save(Record(3, "Humidity",    55.0));
        printAll("After save", repo);
    }
    std::cout << "  -> records.json created\n";

    // ── Scenario 2: 프로그램 재시작 → 파일에서 데이터 복원 ────────
    std::cout << "\n=== Scenario 2: Restart -> Restore from File ===";
    {
        JsonRepository repo(dataFile);
        printAll("Restored from records.json", repo);
    }

    // ── Scenario 3: 특정 레코드 수정 → 파일 갱신 ──────────────────
    std::cout << "\n=== Scenario 3: Update Record 2 ===";
    {
        JsonRepository repo(dataFile);
        repo.update(2, Record(2, "Pressure", 103.5));
        printAll("After update (Pressure: 101.3 -> 103.5)", repo);
    }

    // ── Scenario 4: 특정 레코드 삭제 → 파일 갱신 ──────────────────
    std::cout << "\n=== Scenario 4: Delete Record 1 ===";
    {
        JsonRepository repo(dataFile);
        repo.remove(1);
        printAll("After delete (ID=1 removed)", repo);
    }

    return 0;
}
