#pragma once
#include <map>
#include <string>

using namespace std;

struct SymbolData {
    int fs_FUID;
    string last_update;
};

class SymbolDB
{
public:
    static void add_Symbol(int key, int id, string time);
    static void update_SymbolTime(int key, string time);
    static void update_SymbolUID(int key, int FUID);
    static void remove_Symbol(int key);
    static int get_FSUID(int key);

private:
    static std::map<int, SymbolData> sym_map;

};