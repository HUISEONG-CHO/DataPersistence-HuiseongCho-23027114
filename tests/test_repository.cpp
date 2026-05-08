#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "repository/JsonRepository.h"
#include "json/JsonValue.h"

namespace fs = std::filesystem;

class JsonRepositoryTest : public ::testing::Test {
protected:
    const std::string testFile = "test_records.json";

    void SetUp() override {
        if (fs::exists(testFile)) fs::remove(testFile);
    }
    void TearDown() override {
        if (fs::exists(testFile)) fs::remove(testFile);
    }

    JsonRepository makeRepo() { return JsonRepository(testFile); }
};

TEST_F(JsonRepositoryTest, SaveAndFindAll) {
    auto repo = makeRepo();
    repo.save(Record(1, "Temp",     36.5));
    repo.save(Record(2, "Pressure", 101.3));

    auto all = repo.findAll();
    ASSERT_EQ(all.size(), 2u);
    EXPECT_EQ(all[0].getId(), 1);
    EXPECT_EQ(all[1].getId(), 2);
}

TEST_F(JsonRepositoryTest, FindById) {
    auto repo = makeRepo();
    repo.save(Record(1, "Temp", 36.5));

    Record r = repo.findById(1);
    EXPECT_EQ(r.getName(), "Temp");
    EXPECT_DOUBLE_EQ(r.getValue(), 36.5);
}

TEST_F(JsonRepositoryTest, Update) {
    auto repo = makeRepo();
    repo.save(Record(1, "Temp", 36.5));
    repo.update(1, Record(1, "Temperature", 37.0));

    Record r = repo.findById(1);
    EXPECT_EQ(r.getName(), "Temperature");
    EXPECT_DOUBLE_EQ(r.getValue(), 37.0);
}

TEST_F(JsonRepositoryTest, Remove) {
    auto repo = makeRepo();
    repo.save(Record(1, "Temp",     36.5));
    repo.save(Record(2, "Pressure", 101.3));
    repo.remove(1);

    auto all = repo.findAll();
    ASSERT_EQ(all.size(), 1u);
    EXPECT_EQ(all[0].getId(), 2);
}

TEST_F(JsonRepositoryTest, FindByIdThrowsOnMissing) {
    auto repo = makeRepo();
    EXPECT_THROW(repo.findById(999), std::runtime_error);
}

TEST_F(JsonRepositoryTest, FileSavedAfterSave) {
    auto repo = makeRepo();
    repo.save(Record(1, "Temp", 36.5));
    EXPECT_TRUE(fs::exists(testFile));
}

TEST_F(JsonRepositoryTest, DataPersistedAcrossInstances) {
    {
        JsonRepository repo(testFile);
        repo.save(Record(1, "Temp", 36.5));
    }
    {
        JsonRepository repo(testFile);
        auto all = repo.findAll();
        ASSERT_EQ(all.size(), 1u);
        EXPECT_EQ(all[0].getName(), "Temp");
    }
}

TEST_F(JsonRepositoryTest, CorruptedFileThrows) {
    std::ofstream f(testFile);
    f << "{invalid json}";
    f.close();
    EXPECT_THROW(JsonRepository repo(testFile), JsonParseError);
}
