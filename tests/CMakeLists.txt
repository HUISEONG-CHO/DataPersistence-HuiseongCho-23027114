add_executable(DataPersistence_Tests
    test_placeholder.cpp
    test_json.cpp
    test_record.cpp
    test_repository.cpp
    ${CMAKE_SOURCE_DIR}/src/json/JsonValue.cpp
    ${CMAKE_SOURCE_DIR}/src/json/JsonParser.cpp
    ${CMAKE_SOURCE_DIR}/src/json/JsonSerializer.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Record.cpp
    ${CMAKE_SOURCE_DIR}/src/repository/JsonRepository.cpp
)
target_include_directories(DataPersistence_Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DataPersistence_Tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(DataPersistence_Tests)
