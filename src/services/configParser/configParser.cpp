#include "configParser.hpp"
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <json/writer.h>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>

std::vector<std::string> configParser::parseDependencies(const std::string &filename) {
    spdlog::debug("parsing config");
    std::ifstream ifs(filename, std::ifstream::binary);
    Json::Reader rdr;
    Json::Value root;
    std::vector<std::string> dep_list;
    if (ifs.is_open()) {
        rdr.parse(ifs, root);
        Json::Value dependencies = root["dependencies"];
        for (const auto &dep : dependencies) {
            dep_list.push_back(dep.asString());
            std::cout << dep.asString() << std::endl;
        }
        ifs.close();
    } else { spdlog::error("error while opening config file!" );}
    return dep_list;
}


int configParser::returnFormatedDeps(const std::string &filename)
{
    spdlog::info("Formatting Dependencies");
    std::vector<std::string> deps = this->parseDependencies(filename);
    for (const auto& dep : deps) {
        spdlog::debug("[DEPENDENCY] " + dep + " Founded!");
    }
    return 0;
}

void configParser::addDependency(const std::string filename, const std::string dependency_name)
{
    std::ifstream filer(filename);
    Json::Reader rdr;
    Json::Value root;
    if (filer.is_open()){
        spdlog::info("Writing dependency to file");
        spdlog::debug("Config Parsed succeful");

        rdr.parse(filer, root);
        Json::Value dependencies = root["dependencies"];

        Json::Value addedDep(dependency_name);
        dependencies.append(addedDep);
        root["dependencies"] = dependencies;

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "  ";
        Json::StreamWriterBuilder writer(builder);

        std::ofstream filew(filename);
        filew.clear();
        filew << Json::writeString(writer, root);
        filew.close();
        spdlog::debug("Config Writed succeful");
    } else { spdlog::error("config openning error!"); }
}

std::string configParser::getStartCommand(const std::string& filename)
{
    spdlog::debug("parsing config");
    std::ifstream ifs("alpacco.config.json", std::ifstream::binary);
    Json::Reader rdr;
    Json::Value root;
    std::string etp;
    if (ifs.is_open()) {
        rdr.parse(ifs, root);
        Json::Value entry_point = root["entry_point"];
        etp = entry_point.asString();
    } else { spdlog::error("error while opening config file!" );}
    return etp;
}