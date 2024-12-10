#include "init.hpp"
#include <cstdlib>
#include <json/writer.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <string>
#include <iostream>
#include <json/json.h>

using namespace Json;

void InitProject::SetupVenv(const char* venvname) 
{
    std::string _venvnamestr = (venvname);
    std::string _venvinit = (" python -m venv " + _venvnamestr + " ");
    std::string command = _venvinit;
    spdlog::info("Creating Virtual env");
    spdlog::debug("Creating Python VENV With '" + command + "'");
    system(command.c_str());
}

void InitProject::CreateConfig(const char* projectname)
{

    Json::Value root;
    spdlog::info("Creating config file");
    try {
        spdlog::debug("Formatting pretty-json");
        root["projectname"] = projectname;
        Json::Value dependencies(Json::arrayValue);
        root["dependencies"] = dependencies;
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "    ";
        Json::StreamWriterBuilder writer(builder);
        spdlog::debug("Writing Config to alpacco.config.json");
        std::ofstream config("alpacco.config.json");
        config << Json::writeString(writer, root);
        config.close();
        
    } catch (...) {
        spdlog::error("Creting config file returned error!");
    }
    spdlog::debug("Creating config file done");

}