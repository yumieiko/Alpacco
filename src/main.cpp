#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <json/reader.h>
#include <ostream>
#include <spdlog/spdlog.h>
#include "libs/args/args.hxx"
#include "services/initProject/init.hpp"
#include "services/configParser/configParser.hpp"


int main(int argc, char **argv) 
{
    spdlog::set_level(spdlog::level::debug);
    args::ArgumentParser parser("alpacco - lightware python project manager");
    // Init
    args::Command init(parser, "init", "Init project");
    args::Positional<std::string> projectname(init, "projectname", "Name of the project");
    
    // add package
    args::Command add_command(parser, "add", "Add dependency");
    args::Positional<std::string> dependname(add_command, "dependency", "The name of the dependency");

    try
    {
        parser.ParseCLI(argc, argv);
        if (init)
        {
            if (!projectname) {
                spdlog::error("project name not provided!");
                exit(1);
            }
            
            InitProject *project;
            project->SetupVenv("alpaccoenv");
            project->CreateConfig(args::get(projectname).c_str());
        }
        if (add_command) {
            if (!dependname) {
                spdlog::error("Dependency error!");
            }
            configParser *cfgparser;
            cfgparser->addDependency("alpacco.config.json", args::get(dependname));
        }
        std::cout << std::endl;
    }
    catch (args::Help)
    {
        std::cout << parser;
    }
    catch (args::Error& e)
    {
        std::cerr << e.what() << std::endl << parser;
        return 1;
    }
    return 0;

}
