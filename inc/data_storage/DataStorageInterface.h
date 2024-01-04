#pragma once

/*
 * Requirements:
 * The data storage component is an abstraction of some sort of storage media
 * such as a folder containing files or a database etc.
 * This component needs to support saving to files or to databases such as Postgres or Mongo.
 *
 * Approach 1: Use inheritance to provide a common interface for both saving to folder/files and databases
 * Approach 2:
 */

class IDataStorage
{
public:
    virtual ~IDataStorage() = default;

    virtual void save() = 0;
    virtual void load() = 0;
};

class IDatabaseStorage
{
public:
    virtual ~IDatabaseStorage() = default;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
protected:

};

class IPostgresqlDataBase
{
public:
    virtual ~IPostgresqlDataBase() = default;

    virtual void specificFunction() = 0;
};

