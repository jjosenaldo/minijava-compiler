#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class DefaultSymbolHandler;
class Program;

extern Program* program;
extern DefaultSymbolHandler g_defaultSymbolHandler;
extern unordered_map<string, string> g_classParentMap;
const string MAIN_METHOD_NAME = "main";
extern string g_mainClassName;

#endif