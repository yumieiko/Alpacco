cmake_minimum_required(VERSION 3.11)
project(alalpacco CXX)

if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
find_package(fmt CONFIG REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(serviceslib 
    "src/services/initProject/init.cpp"
    "src/services/configParser/configParser.cpp"
    "src/services/commands_callbacks/commands_callbacks.cpp"
    "src/services/hotreload/hotreload.cpp"
    "src/services/pipInterlayer/pipInterlayer.cpp"
    )

add_executable(alpacco src/main.cpp ${serviceslib})

target_link_libraries(alpacco PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32> ${JSONCPP_LIBRARIES} fmt::fmt-header-only ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})