#include <cstdlib>
#include <spdlog/spdlog.h>
#include <string>
namespace utils {
    inline void sysvenv(const char* command) {
        std::string _venv = " source alpaccoenv/bin/activate && ";
        std::string cmd = _venv + command;
        spdlog::debug("used sysenv, builded command is - " + cmd);
        system(cmd.c_str());
    }
}