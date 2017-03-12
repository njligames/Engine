//
//  WorldSQLite.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

//http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
//http://stackoverflow.com/questions/18092240/sqlite-blob-insertion-c

#include "WorldSQLite.h"
#include "File.h"
#define FORMATSTRING "{\"njli::WorldSQLite\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

static void * s_FileData = NULL;
static int s_FileSize = 0;

void *njli::WorldSQLite::s_Buffer = NULL;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    char t[32] = "HELLO FLAVA FLAV";
    njli::WorldSQLite::setBuffer(t, sizeof(t));
    return 0;
    
//    int i;
//    fprintf(stderr, "%s: ", (const char*)data);
//    
//    for(i=0; i<argc; i++)
//    {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
}

static sqlite3 *openDatabase_Internal(const char *database_name)
{
    sqlite3 *db = NULL;
    int rc = sqlite3_open(database_name, &db);
    
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    return db;
}

static bool fileTableExists_Internal(sqlite3 *db)
{
    return true;
}

static bool createFileTable_Internal(sqlite3 *db)
{
    const char *sql = "CREATE TABLE IF NOT EXISTS `file` (" \
    "`filename`	TEXT NOT NULL UNIQUE," \
    "`data`	BLOB NOT NULL," \
    "`size`	INTEGER NOT NULL," \
    "PRIMARY KEY(filename)" \
    ");";
    
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if(rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }
    return true;
}

static bool createFileData_Internal(sqlite3 *db, const char *filename, const void *data, int size)
{
    sqlite3_stmt *stmt = NULL;
    char sql_buffer[2048] = "";
    sprintf(sql_buffer, "INSERT OR IGNORE INTO `file`(`filename`,`data`,`size`) VALUES ('%s',?,%d);", filename, size);
//    sprintf(sql_buffer, "INSERT INTO `file`(`filename`,`data`,`size`) VALUES ('%s',?,%d);", filename, size);
    
    int rc = sqlite3_prepare_v2(db, sql_buffer, -1, &stmt, NULL);
    
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "prepare failed: %s", sqlite3_errmsg(db));
        return false;
    }
    else
    {
        
        rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
        if(rc != SQLITE_OK)
        {
            fprintf(stderr, "bind failed: %s", sqlite3_errmsg(db));
            return false;
        }
        else
        {
            rc = sqlite3_step(stmt);
            if(rc != SQLITE_DONE)
            {
                fprintf(stderr, "execution failed: %s", sqlite3_errmsg(db));
                return false;
            }
            fprintf(stdout, "Inserted data successfully successfully\n");
        }
    }
    return true;
}

namespace njli
{
    WorldSQLite::WorldSQLite() :
    m_db(NULL)
    {
        
    }
    
    WorldSQLite::~WorldSQLite()
    {
        if(m_db)
        {
            sqlite3_close(m_db);
        }
    }
    
    WorldSQLite::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    WorldSQLite &WorldSQLite::operator=(const WorldSQLite &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    bool WorldSQLite::openDatabase(const char *database_name)
    {
        if(m_db)
        {
            sqlite3_stmt *stmt = NULL;
            while(NULL != (stmt = sqlite3_next_stmt(m_db, stmt)))
                sqlite3_finalize(stmt);
            sqlite3_close(m_db);
        }
        
        
        m_db = openDatabase_Internal(database_name);
        if(m_db)
        {
            createFileTable_Internal(m_db);
            return true;
        }
        
        return false;
    }
    
    bool WorldSQLite::getBool(const char *key)
    {
        return false;
    }
    
    void WorldSQLite::setBool(const char *key, bool value)
    {
        
    }
    
    s32 WorldSQLite::getInt(const char *key)
    {
        return 0;
    }
    
    void WorldSQLite::setInt(const char *key, s32 value)
    {
        
        
    }
    
    f32 WorldSQLite::getFloat(const char *key)
    {
        return 0.0f;
    }
    
    void WorldSQLite::setFloat(const char *key, f32 value)
    {
        
    }
    
    const char *WorldSQLite::getString(const char *key)
    {
        return "empty";        
    }
    
    void WorldSQLite::setString(const char *key, const char *value)
    {
        
    }
    
    bool WorldSQLite::createFile(const char *filename, const char *buffer)
    {
        s32 size = strlen(buffer);
        if(m_db)
            return createFileData_Internal(m_db, filename, buffer, size);
        return false;
    }
    
//    FileData WorldSQLite::readFile(const char *filename)
//    {
//        s_FileData = NULL;
//        do
//        {
//            sleepThread(1.0f/60.0f);
//        }
//        while (s_FileData == NULL);
//        
//        
//        FileData d(s_FileData, s_FileSize);
////        memcpy(d.buffer, s_FileData, s_FileSize);
//        return d;
//    }
    
    bool WorldSQLite::updateFile(const char *filename, s32 offset, s32 size, const void *buffer)
    {
        return false;
    }
    
    bool WorldSQLite::deleteFile(const char *filename)
    {
        return false;
    }
    
    void WorldSQLite::setBuffer(const void *buffer, int size)
    {
        memcpy(s_Buffer, buffer, size);
        s_FileData = s_Buffer;
        s_FileSize = size;
    }
    void WorldSQLite::createBuffer()
    {
        if(s_Buffer)
            deleteBuffer();
        
        s_Buffer = malloc(1<<16);
    }
    void WorldSQLite::deleteBuffer()
    {
        if(s_Buffer)
            free(s_Buffer);
    }
}