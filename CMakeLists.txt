cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

message(STATUS "C++ standard set to ${CMAKE_CXX_STANDARD}")

project(Mnemosyne CXX)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Compiler is Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Compiler is GCC")
    add_compile_options(-Wno-volatile -fcoroutines)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message(STATUS "Compiler is Intel C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Compiler is Visual Studio C++")
    add_compile_options(/MP /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS NOMINMAX)
endif ()

find_package(cryptopp CONFIG REQUIRED)
find_library(CPPREDIS_LIB cpp_redis)
#find_package(Drogon CONFIG REQUIRED)
add_subdirectory(drogon)
find_package(magic_enum CONFIG REQUIRED)
find_package(mailio CONFIG REQUIRED)
find_library(TACOPIE_LIB tacopie)

add_compile_definitions(CMAKE_PROJECT_NAME="${PROJECT_NAME}")

add_executable(${PROJECT_NAME} main.cc)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(helpers HELPER_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(structures STRUCT_SRC)
aux_source_directory(types TYPE_SRC)
aux_source_directory(utils UTIL_SRC)

target_sources(${PROJECT_NAME} PRIVATE
        ${CTL_SRC}
        ${FILTER_SRC}
        ${HELPER_SRC}
        ${MODEL_SRC}
        ${PLUGIN_SRC}
        ${STRUCT_SRC}
        ${TYPE_SRC}
        ${UTIL_SRC}
        ${HELPER_SRC})

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ${CPPREDIS_LIB}
        cryptopp-static
#        Drogon::Drogon
        drogon
        mailio
        magic_enum::magic_enum
        ${TACOPIE_LIB}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(
        FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/config.json
        ${CMAKE_CURRENT_SOURCE_DIR}/verifyEmail.html
        DESTINATION
        ${CMAKE_BINARY_DIR}
)

# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)

# ##############################################################################
# uncomment the following line for dynamically loading views
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

#add_subdirectory(test)
