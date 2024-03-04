#include "utils.h"

const char* readFile(std::ifstream& file, std::string filePath)
{
    file.open(filePath, std::ios::in);
    // If file doesn't open return nullptr and send error msg
    if (!file)
    {
        std::cout << "ERROR::OPENING::FILE" << std::endl;
        return nullptr;
    }
    // If file opens append lines and \n in result (while getline will iterate over the lines of the file)
    else
    {
        std::cout << "SUCCESS::CREATING::FILE" << std::endl;
        std::string result = "";
        std::string line;
        while (getline(file, line))
        {
            result.append(line);
            result.append("\n");
        }
        file.close();
        return result.c_str(); // turns the string into a const char*
    }
}