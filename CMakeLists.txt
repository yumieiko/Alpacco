cmake_minimum_required(VERSION 3.11)
project(alalpacco CXX)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
find_package(fmt CONFIG REQUIRED)

set(serviceslib 
    "src/services/initProject/init.cpp"
    "src/services/configParser/configParser.cpp"
    "src/services/commands_callbacks/commands_callbacks.cpp"
    )

add_executable(alpacco src/main.cpp ${serviceslib})

target_link_libraries(alpacco PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> ${JSONCPP_LIBRARIES} fmt::fmt-header-only)