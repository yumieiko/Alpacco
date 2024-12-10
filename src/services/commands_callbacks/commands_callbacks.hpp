#include "../../libs/args/args.hxx"

class CommandCallbacks {
public:
    void initCommand(args::Positional<std::string> projectname, args::Positional<std::string> entry_point, args::Positional<std::string> project_version);
    void addPkgCommand(args::Positional<std::string> dependname);
    void startCommand();
};