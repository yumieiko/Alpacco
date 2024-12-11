#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <json/reader.h>
#include <ostream>
#include <spdlog/spdlog.h>
#include <string>
#include "libs/args/args.hxx"
#include "services/commands_callbacks/commands_callbacks.hpp"

int main(int argc, char **argv) 
{
    spdlog::set_level(spdlog::level::debug);
    args::ArgumentParser parser("alpacco - lightware python project manager");
    // Init
    args::Command init(parser, "init", "Init project");
    args::Positional<std::string> projectname(init, "project name", "Name of the project");
    args::Positional<std::string> entry_point(init, "entrypoint", "entry point filename");
    args::Positional<std::string> project_version(init, "project version", "project version");
    
    // add package
    args::Command add_command(parser, "add", "Add dependency");
    args::Positional<std::string> dependname(add_command, "dependency", "The name of the dependency");

    // install all packages
    args::Command install_command(parser, "install", "Install all dependencies from config");

    // Start
    args::Command start_command(parser, "start", "Start project with your command");

    // Dev
    args::Command dev_command(parser, "dev", "Start developer session");

    try
    {
        parser.ParseCLI(argc, argv);
        CommandCallbacks *commands_callbacks;
        if (init){ commands_callbacks->initCommand(projectname, entry_point,project_version); }
        if (add_command) { commands_callbacks->addPkgCommand(dependname); }
        if (start_command) { commands_callbacks->startCommand(); }
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
