//
//  WorldSQLite.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldSQLite__
#define __JLIGameEngineTest__WorldSQLite__

#include "Util.h"
#include <sqlite3.h>
#include <string>

namespace njli
{
    /// <#Description#>
    class WorldSQLite
    {
    public:
        /**
         *  <#Description#>
         */
        WorldSQLite();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        virtual ~WorldSQLite();
        /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
        operator std::string() const;
        
        //TODO: fill in specific methods for WorldSQLite
        
        /**
         *  <#Description#>
         *
         *  @param database_name <#database_name description#>
         *
         *  @return <#return value description#>
         */
        bool openDatabase(const char *database_name);
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        bool getBool(const char *key);
        /**
         *  <#Description#>
         *
         *  @param key   <#key description#>
         *  @param value <#value description#>
         */
        void setBool(const char *key, bool value);
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        s32 getInt(const char *key);
        /**
         *  <#Description#>
         *
         *  @param key   <#key description#>
         *  @param value <#value description#>
         */
        void setInt(const char *key, s32 value);
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        f32 getFloat(const char *key);
        /**
         *  <#Description#>
         *
         *  @param key   <#key description#>
         *  @param value <#value description#>
         */
        void setFloat(const char *key, f32 value);
        
        /**
         *  <#Description#>
         *
         *  @param key <#key description#>
         *
         *  @return <#return value description#>
         */
        const char *getString(const char *key);
        /**
         *  <#Description#>
         *
         *  @param key   <#key description#>
         *  @param value <#value description#>
         */
        void setString(const char *key, const char *value);
        
        /**
         *  <#Description#>
         *
         *  @param filename <#filename description#>
         *  @param buffer   <#buffer description#>
         *
         *  @return <#return value description#>
         */
        bool createFile(const char *filename, const char *buffer);
        /**
         *  <#Description#>
         *
         *  @param filename <#filename description#>
         *
         *  @return <#return value description#>
         */
//        FileData readFile(const char *filename);
        /**
         *  <#Description#>
         *
         *  @param filename <#filename description#>
         *  @param offset   <#offset description#>
         *  @param size     <#size description#>
         *  @param buffer   <#buffer description#>
         *
         *  @return <#return value description#>
         */
        bool updateFile(const char *filename, s32 offset, s32 size, const void *buffer);
        /**
         *  <#Description#>
         *
         *  @param filename <#filename description#>
         *
         *  @return <#return value description#>
         */
        bool deleteFile(const char *filename);
        
        /**
         *  <#Description#>
         *
         *  @param void <#void description#>
         *  @param size <#size description#>
         */
        static void setBuffer(const void *, int size);
        /**
         *  <#Description#>
         */
        static void createBuffer();
        /**
         *  <#Description#>
         */
        static void deleteBuffer();
    protected:
    private:
        WorldSQLite(const WorldSQLite &);
        WorldSQLite &operator=(const WorldSQLite &);
        
        sqlite3 *m_db;
        static void *s_Buffer;
    };
}

#endif /* defined(__JLIGameEngineTest__WorldSQLite__) */
