#pragma once

#include "globalStore/GlobalStore.hpp"

namespace fw
{

std::map<std::string, int> GlobalStore::m_ints;
std::map<std::string, float> GlobalStore::m_floats;
std::map<std::string, bool> GlobalStore::m_bools;
std::map<std::string, std::string> GlobalStore::m_strings;

void GlobalStore::setInt(std::string name, int i)
{
     m_ints[name] = i;
}

int GlobalStore::getInt(std::string name)
{
     return m_ints[name];
}

void GlobalStore::setFloat(std::string name, float f)
{
     m_floats[name] = f;
}

float GlobalStore::getFloat(std::string name)
{
     return m_floats[name];
}

void GlobalStore::setBool(std::string name, bool b)
{
     m_bools[name] = b;
}

bool GlobalStore::getBool(std::string name)
{
     return m_bools[name];
}

void GlobalStore::setString(std::string name, std::string s)
{
     m_strings[name] = s;
}

std::string GlobalStore::getString(std::string name)
{
     return m_strings[name];
}

}