#include "configParser.hpp"
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <vector>
#include <spdlog/spdlog.h>

std::vector<std::string> configParser::parseDependencies(const std::string &filename) {
    spdlog::info("parsing config");
    std::ifstream ifs("pacco.config.json", std::ifstream::binary);
    Json::Reader rdr;
    Json::Value root;
    std::vector<std::string> dep_list;
    if (ifs.is_open()) {
        rdr.parse(ifs, root);
        Json::Value dependencies = root["dependencies"];
        for (const auto &dep : dependencies) {
            dep_list.push_back(dep.asString());
        }
    } else { spdlog::error("error while opening config file!" );}
    return dep_list;
}


int configParser::returnFormatedDeps(const std::string &filename)
{
    spdlog::info("Formatting Dependencies");
    std::vector<std::string> deps = this->parseDependencies(filename);
    for (const auto& dep : deps) {
        std::cout << "[DEP] " << dep << " Founded!" << std::endl;
    }
    return 0;
}