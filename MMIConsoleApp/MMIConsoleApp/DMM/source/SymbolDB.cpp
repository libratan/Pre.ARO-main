#include <../DMM/header/SymbolDB.h>

static std::map<int, SymbolData> sym_map;
std::map<int, SymbolData> SymbolDB::sym_map = std::map<int, SymbolData>();

void SymbolDB::add_Symbol(int key, int id, std::string time)
{
    SymbolData data = { id, time, };
    sym_map.insert(std::pair<int, SymbolData>(key, data));
}

void SymbolDB::update_SymbolTime(int key, string time)
{
    std::map<int, SymbolData>::iterator it = sym_map.find(key);
    if (it != sym_map.end())
    {
        it->second.last_update = time;
    }
}

void SymbolDB::update_SymbolUID(int key, int FUID)
{
    std::map<int, SymbolData>::iterator it = sym_map.find(key);
    if (it != sym_map.end())
    {
        it->second.fs_FUID = FUID;
    }
}

void SymbolDB::remove_Symbol(int key)
{
    sym_map.erase(key);
}

int SymbolDB::get_FSUID(int key)
{
    std::map<int, SymbolData>::iterator it = sym_map.find(key);
    if (it != sym_map.end())
    {
        // FSUID found
        return it->second.fs_FUID;
    }

    // Symbol does not exist in DB, return -1
    return -1;
}