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
    args::ArgumentParser parser("Pacco - lightware python project manager");
    // Init
    args::Command init(parser, "init", "Init project");
    args::Group init_args(init, "arguments", args::Group::Validators::DontCare, args::Options::Global);
    args::ValueFlag<std::string> projectname(init_args, "projectname", "", {"n"});
    
    // Install
    args::Command install(parser, "install", "install all dependencies");
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
            project->SetupVenv("paccoenv");
            project->CreateConfig(projectname->c_str());
        }
        if (install) {
            configParser *configParser;
            configParser->returnFormatedDeps("pacco.config.json");
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
