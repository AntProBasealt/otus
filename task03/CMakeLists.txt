cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build google test" ON)

configure_file(version.h.in version.h)
include(cmake/GoogleBenchmark.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ip_filter
  main.cpp
)

add_executable(ip_filter_bench main_bench.cpp)
add_library(ip_filter_lib ip_filter_lib.cpp)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE ip_filter_lib)
target_link_libraries(ip_filter_bench PRIVATE ip_filter_lib benchmark::benchmark)

if(WITH_GTEST)
    find_package(GTest)

    add_executable(ip_filter_tests ip_filter_tests.cpp)

    target_link_libraries(ip_filter_tests
        GTest::gtest_main
        ip_filter_lib
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    if(WITH_GTEST)
        target_compile_options(ip_filter_tests PRIVATE
            /W4
    )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GTEST)
        target_compile_options(ip_filter_tests PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    add_test(ip_filter_tests ip_filter_tests)
endif()
