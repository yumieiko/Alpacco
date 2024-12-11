#include "hotreload.hpp"
#include <set>
#include <string>
namespace fs = boost::filesystem;

void HotReload::reloadEvent(const fs::path& path_to_watch, std::chrono::milliseconds interval)
{
    std::unordered_map<std::string, std::time_t> paths_last_write_time;
    std::set<std::string> directories;
    std::set<std::string> _envname =  {"alpaccoenv"};

    // Initialize the map with current file modification times
    for (fs::recursive_directory_iterator it(path_to_watch), end; it != end; ++it) {
        if (fs::is_regular_file(it->path())) {
            paths_last_write_time[it->path().string()] = fs::last_write_time(it->path());
        }
    }

    while (true) {
        std::this_thread::sleep_for(interval);

        std::set<std::string> current_directories;

        for (fs::recursive_directory_iterator it(path_to_watch), end; it != end; ++it) {
            if (fs::is_regular_file(it->path())) {
                auto current_file_last_write_time = fs::last_write_time(it->path());

                // Check if the file is new or modified
                if (paths_last_write_time.find(it->path().string()) == paths_last_write_time.end()) {
                    std::cout << "File added: " << it->path().string() << '\n';
                    paths_last_write_time[it->path().string()] = current_file_last_write_time;
                } else if (paths_last_write_time[it->path().string()] != current_file_last_write_time) {
                    std::cout << "File modified: " << it->path().string() << '\n';
                    paths_last_write_time[it->path().string()] = current_file_last_write_time;
                }
            }
        }

        // Check for removed files
        auto it = paths_last_write_time.begin();
        while (it != paths_last_write_time.end()) {
            if (!fs::exists(it->first)) {
                std::cout << "File removed: " << it->first << '\n';
                it = paths_last_write_time.erase(it);
            } else {
                ++it;
            }
        }
    }
}