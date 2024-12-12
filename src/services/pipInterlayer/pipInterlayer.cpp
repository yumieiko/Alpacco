#include "pipInterlayer.hpp"
#include <boost/filesystem/directory.hpp>
#include <cstdlib>
#include <iostream>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>
#include <ostream>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include <fmt/core.h>
#include <fmt/color.h>
#include "../utils.hpp"
#include <boost/filesystem.hpp>
#include <string>
#include <fstream>

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
        Json::Value root;
        Json::Value deps(Json::arrayValue);
        for (const auto& dep : dependencies) {
            deps.append(dep);
            
        }
        root["dependencies"] = deps;
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "  ";

        Json::StreamWriterBuilder writer(builder);
        
        spdlog::debug("Writing packages.lock");
        std::ofstream packagelcok("packages.lock");
        packagelcok << Json::writeString(writer, root);
        packagelcok.close();
        // TODO: IF PACKAGES.LOCK NOT FOUND=COPY ALL DEPENDENCIES AND INSTALL THEM, IF FOUND=CHECK AF ALL DEPENDENCIES FROM CONFIG ARE == DEPENDENCIES FROM PACKAGE.LOCK, IF YES == UNINSTALL DELETED AND INSTALL NEW, IF NOT=UPDATE COMMAND
    }
    utils::sysvenv(_command.c_str());
}

void PipInterlayer::updateDependencies()
{
    Json::Value configpackages;
    Json::Value lockpackages;

    std::ifstream conffile("alpacco.config.json", std::ifstream::binary);
    Json::Reader configpackagesrdr;
    std::vector<std::string> confdeps;
    if (conffile.is_open()) {
        configpackagesrdr.parse(conffile, configpackages);
        Json::Value dependencies = configpackages["dependencies"];
        for (const auto &dep : dependencies) {
            confdeps.push_back(dep.asString());
            std::cout << dep.asString() << std::endl;
        }
        conffile.close();
    } else { spdlog::error("error while opening config file!" );}

    std::ifstream lockfile("packages.lock", std::ifstream::binary);
    Json::Reader lockpackagerdr;
    std::vector<std::string> lockdeps;
    if (lockfile.is_open()) {
        lockpackagerdr.parse(lockfile, configpackages);
        Json::Value dependencies = configpackages["dependencies"];
        for (const auto &dep : dependencies) {
            lockdeps.push_back(dep.asString());
            std::cout << dep.asString() << std::endl;
        }
        lockfile.close();
    } else { spdlog::error("error while opening config file!" );}

    std::vector<std::string> unique_items;
    for (const auto& item : confdeps) {
        if (std::find(lockdeps.begin(), lockdeps.end(), item) == lockdeps.end()) {
            unique_items.push_back(item);
        }
    }
    std::cout << "Not Found:" << std::endl;
    for (const auto& item : unique_items) {
        std::cout << item << std::endl;
    }
}