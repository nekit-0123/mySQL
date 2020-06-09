#include <iostream>
#include <mysql.h>
#include <string>
#include <stdarg.h>

class ID
{
    int id;

public:
    ID()
    {
        static int counter = 0;
        id = counter++;
    }
    ID(const ID &root) = delete;
    ID &operator=(const ID &) = delete;
    int get_id() { return id; }
};

class CWorkDB
{
public:
    CWorkDB();
    ~CWorkDB();

    MYSQL *GetConnection() const;
    bool connect(const char *host, const char *login, const char *password, const char *database) const;
    bool query(const char *_query) const;

    void SetTable(const std::string &_name);
    // Work With Tables
    void Print(const std::string &_row = "*");
    bool Insert(const char *_query);
    bool Delete(const char *_query = "");

private:
    MYSQL *con = nullptr;
    MYSQL_RES *res = nullptr;
    MYSQL_ROW row;
    std::string tableName;
};