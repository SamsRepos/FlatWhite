#pragma once
#include <string>
#include <map>

namespace fw
{

class GlobalStore
{
public:
    GlobalStore() = delete;

    static void setInt(std::string name, int i);
    static int getInt(std::string name);

    static void setFloat(std::string name, float f);
    static float getFloat(std::string name);
    
    static void setBool(std::string name, bool b);
    static bool getBool(std::string name);
    
    static void setString(std::string name, std::string s);
    static std::string getString(std::string name);

private:
    static std::map<std::string, int> m_ints;
    static std::map<std::string, float> m_floats;
    static std::map<std::string, bool> m_bools;
    static std::map<std::string, std::string> m_strings;
};

}