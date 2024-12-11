#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <set> 
class HotReload {
public:
    void reloadEvent(const boost::filesystem::path& path_to_watch, std::chrono::milliseconds interval);
};