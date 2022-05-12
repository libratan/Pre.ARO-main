//******************************************************************************
// Copyright XYZ PTE LTD. All Rights Reserved 
//
// FILE NAME: SymbolIDB.h
//
// AUTHOR: xxx
//
// DATE: DD/MM/YYYY
//
// DESCRIPTION
// Header file
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
#ifndef SYMBOLDB_H
#define SYMBOLDB_H

#include <map>
#include <string>
#include <windows.h>

namespace SYMDB {
    struct SymbolData {
        INT fs_FUID;        //symbol id
        std::string last_update; //last update
    };
  
    class SymbolDB
    {
    public:
        //****************************************************************************
        //* Function Name  : void SymbolDB::add_Symbol(key, id, time)
        //* Purpose        : Add symbol to sym_map
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        static BOOL add_Symbol(INT key,
            INT id,
            const std::string& time);
        //****************************************************************************
        //* Function Name  : void SymbolDB::update_SymbolTime(key, time)
        //* Purpose        : Update time in sym_map
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        static void update_SymbolTime(INT key, const std::string& time);
        //****************************************************************************
        //* Function Name  : void SymbolDB::update_SymbolUID(key, FUID)
        //* Purpose        : update symbol ID in sym_map
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        static void update_SymbolUID(INT key, INT FUID);
        //****************************************************************************
        //* Function Name  : void SymbolDB::remove_Symbol(key)
        //* Purpose        : Remove a symbol in sym_map
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : None
        //* Access         : Public
        //* Note           :
        //****************************************************************************
        static size_t remove_Symbol(INT key);
        //****************************************************************************
        //* Function Name  : INT SymbolDB::get_FSUID(key)
        //* Purpose        : Get symbol ID from sym_map
        //*                 
        //* Pre-Condition  : None
        //* Post-Condition : Returns fsuid or -1 if not found
        //* Access         : Public
        //* Note           :
        //****************************************************************************    
        static INT get_FSUID(INT key);

    private:
        static std::map<INT, SYMDB::SymbolData> sym_map;

    };
}
#endif