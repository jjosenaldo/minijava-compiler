#include "global.hpp"
#include "type.hpp"

DefaultSymbolHandler g_defaultSymbolHandler = DefaultSymbolHandler();
unordered_map<string, string> g_classParentMap = unordered_map<string, string>();
string g_mainClassName = "";
