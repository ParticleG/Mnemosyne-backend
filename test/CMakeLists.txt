cmake_minimum_required(VERSION 3.5)
project(Mnemosyne_test CXX)

add_executable(Mnemosyne_test test_main.cc)

target_link_libraries(
        Mnemosyne_test
        PRIVATE
        cryptopp-static
        drogon
        mailio
        magic_enum::magic_enum
)
target_include_directories(Mnemosyne_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
ParseAndAddDrogonTests(Mnemosyne_test)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config.json DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
