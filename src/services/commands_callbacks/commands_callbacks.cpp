#include "commands_callbacks.hpp"
#include <spdlog/spdlog.h>
#include "../initProject/init.hpp"
#include "../configParser/configParser.hpp"

void CommandCallbacks::initCommand(args::Positional<std::string> projectname, 
                                    args::Positional<std::string> entry_point, 
                                    args::Positional<std::string> project_version
                                    )
{
    std::string _entry_point, _projectname, _projectversion; 
            if (!projectname) {
                std::cout << "Enter Project Name (e.g alpacco): ";
                std::getline(std::cin, _projectname);
            } else { spdlog::debug("entrypoint provided as flag"); _projectname = args::get(projectname); }

            if (!entry_point) {
                std::cout << "Enter Entry Point file (e.g main.py, empty if edit in config): ";
                std::getline(std::cin, _entry_point);
            } else { spdlog::debug("entrypoint provided as flag"); _entry_point = args::get(entry_point); }

            if (!project_version) {
                std::cout << "Enter Entry Point file (e.g 1.0.0): ";
                std::getline(std::cin, _projectversion);
            } else { spdlog::debug("entrypoint provided as flag"); _projectversion = args::get(project_version); }

            InitProject *project;
            project->SetupVenv("alpaccoenv");
            project->CreateConfig(_projectname.c_str(), _entry_point.c_str(), _projectversion.c_str());
}

void CommandCallbacks::addPkgCommand(args::Positional<std::string> dependname)
{
    if (!dependname) {
        spdlog::error("Dependency not provided!");
    }
    configParser *cfgparser;
    cfgparser->addDependency("alpacco.config.json", args::get(dependname));
}