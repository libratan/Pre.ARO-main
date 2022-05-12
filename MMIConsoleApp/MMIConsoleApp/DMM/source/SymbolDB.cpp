//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: SymbolIDB.cpp
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Implementation file
// Interfaces with the symbol database and manipulates them 
// 
// TRACEABILITY : -
//
// MODIFICATION HISTORY
//   DATE              : 
//   MODIFIER          : 
//   MODIFICATION      :     
//
//******************************************************************************
#include <../DMM/header/SymbolDB.h>
using namespace SYMDB;

//static std::map<INT, SymbolData> sym_map; //container to hold the map symbols
std::map<INT, SymbolData> SymbolDB::sym_map = std::map<INT, SymbolData>();


//****************************************************************************
//* Function Name  : void SymbolDB::add_Symbol(key, id, time)
//* Purpose        : Add symbol to sym_map
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
BOOL SymbolDB::add_Symbol(INT key, 
                          INT id, 
                          const std::string& time)
{
    SymbolData data = { id, time, }; //data to hold id and time
    std::pair<std::map<INT, SymbolData>::iterator, BOOL> ret; //to hold return values of insert function
    
    //JSF ensure that function for insert function is not type casted to a viod and will return a value
    ret = sym_map.insert(std::pair<INT, SymbolData>(key, data));

    return ret.second;
}
//****************************************************************************
//* Function Name  : void SymbolDB::update_SymbolTime(key, time)
//* Purpose        : Update time in sym_map
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void SymbolDB::update_SymbolTime(INT key, 
                                 const std::string& time)
{
    std::map<INT, SymbolData>::iterator it = sym_map.find(key); //it is an iterator
    if (it != sym_map.end())
    {
        it->second.last_update = time;
    }
}
//****************************************************************************
//* Function Name  : void SymbolDB::update_SymbolUID(key, FUID)
//* Purpose        : update symbol ID in sym_map
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
void SymbolDB::update_SymbolUID(INT key, INT FUID)
{
    std::map<INT, SymbolData>::iterator it = sym_map.find(key); //it is an iterator
    if (it != sym_map.end())
    {
        it->second.fs_FUID = FUID;
    }
}
//****************************************************************************
//* Function Name  : void SymbolDB::remove_Symbol(key)
//* Purpose        : Remove a symbol in sym_map
//*                 
//* Pre-Condition  : None
//* Post-Condition : None
//* Access         : Public
//* Note           :
//****************************************************************************
size_t SymbolDB::remove_Symbol(INT key)
{
     size_t numremoved = sym_map.erase(key); //returns no of elements removed
     return numremoved;
}
//****************************************************************************
//* Function Name  : INT SymbolDB::get_FSUID(key)
//* Purpose        : Get symbol ID from sym_map
//*                 
//* Pre-Condition  : None
//* Post-Condition : Returns fsuid or -1 if not found
//* Access         : Public
//* Note           :
//****************************************************************************
INT SymbolDB::get_FSUID(INT key)
{
    std::map<INT, SymbolData>::iterator it = sym_map.find(key); //it is an iterator
    INT result = -1; //to hold FUID value and initialises to not exist in DB first 

    if (it != sym_map.end())
    {
        // FSUID found
        result = it->second.fs_FUID;
    }

    // Symbol does not exist in DB, return -1
    return result;
}