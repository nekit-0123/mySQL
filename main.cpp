#include <iostream>
#include <mysql.h>
#include <string>
#include <stdarg.h>

class ID
{
    int id;
public:
    ID() {
        static int counter = 0;
        id = counter++;
    }
    ID(const ID& root) = delete;
    ID& operator=(const ID&) = delete;
    int get_id() { return id; }
};

class MyClass
{
    static ID id;
public:
    static int get_id() 
    {
        return id.get_id();
    }
};

class CWorkDB
{
public:
    CWorkDB()
    {
        con = mysql_init(NULL);
    }

    ~CWorkDB()
    {
        mysql_close(con);
    }

    MYSQL *GetConnection() const
    {
        return con;
    }

    bool connect(const char *host, const char *login, const char *password, const char *database) const
    {
        return mysql_real_connect(con, host, login, password, database, 0, NULL, 0);
    }

    bool query(const char *_query) const
    {
        return mysql_query(con, _query);
    }

    void PrintfTable(const char *_tableName, const std::string &_row = "*")
    {
        std::string sQuery = "select ";
        sQuery.append(_row);
        sQuery.append("from ");
        sQuery.append(_tableName);

        query(sQuery.c_str());
        res = mysql_store_result(con);

        if (res == NULL)
        {
            std::cout << "Error PrintTable";
            return;
        }

        int countColumn = mysql_field_count(con);
        if(mysql_num_rows(res) > 0)
        {
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                for (long i = 0; i < countColumn; ++i)
                    fprintf(stdout, "%s ", row[i]);

                fprintf(stdout, "\n");
            }
        }

        mysql_free_result(res);
    }

    bool InsertToTable(const char *_tableName, const char *_query )
    {
        std::string sQuery = _query;
        sQuery.insert(0, " values (");
        sQuery.insert(0, _tableName);
        sQuery.insert(0, "insert into ");

        sQuery.append(")");

        return query(sQuery.c_str());
    }

private:
    MYSQL *con = nullptr;
    MYSQL_RES *res = nullptr;
    MYSQL_ROW row;
};

int main(void)
{
    CWorkDB workDB;
    if (workDB.GetConnection() == nullptr)
        return 0;


    if (!workDB.connect((char *)"localhost", (char *)"root", (char *)"", (char *)"testdb"))
    {
        std::cout << "Error Connect";
        return -1;
    }


    //ID formId;
    // Сформированный запрос вставки через запятую
    if (workDB.InsertToTable((char *)"user", (char*)"2, 'Smirnov'") == false)
    {
       std::cout << "Error InsertToTable";
       return -1; 
    }


    workDB.PrintfTable((char *)"user");
    return 0;
}