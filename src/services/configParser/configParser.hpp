#include <iostream>
#include <string>
#include <vector>
class configParser {
private:
    std::vector<std::string> parseDependencies(const std::string& filename);
public:
    int returnFormatedDeps(const std::string& filename);
};