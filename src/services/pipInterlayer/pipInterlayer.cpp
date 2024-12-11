#include "pipInterlayer.hpp"
#include <boost/filesystem/directory.hpp>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include <fmt/core.h>
#include <fmt/color.h>
#include "../utils.hpp"
#include <boost/filesystem.hpp>

void PipInterlayer::installDependencies(std::vector<std::string> dependencies)
{
    spdlog::debug("Formatting oneline");
    std::string _ext;
    for (const auto& str : dependencies)
    {
        if (str == "") {
            spdlog::error("Nothing to installl!");
            exit(0);
        }
        _ext += " " + str + " ";
        std::cout << _ext << std::endl;
    }

    spdlog::debug("Installing All dependencies");
    std::string _command = "pip --no-input --no-color --no-python-version-warning install " + _ext + "--progress-bar raw";
    fmt::print(fg(fmt::color::lawn_green), "  $ ");
    fmt::print(fg(fmt::color::spring_green), "{}\n", _command);
    if (!boost::filesystem::exists("./packages.lock")) {
        spdlog::debug("not founded packages.lock, creating");
        // TODO: IF PACKAGES.LOCK NOT FOUND=COPY ALL DEPENDENCIES AND INSTALL THEM, IF FOUND=CHECK AF ALL DEPENDENCIES FROM CONFIG ARE == DEPENDENCIES FROM PACKAGE.LOCK, IF YES == UNINSTALL DELETED AND INSTALL NEW, IF NOT=UPDATE COMMAND
    }
    utils::sysvenv(_command.c_str());
}