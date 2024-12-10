cmake_minimum_required(VERSION 3.11)
project(pacco CXX)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(serviceslib 
    "src/services/initProject/init.cpp"
    )

add_executable(pacco src/main.cpp ${serviceslib})

target_link_libraries(pacco PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> ${JSONCPP_LIBRARIES})