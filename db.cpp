#include "db.h"

CWorkDB::CWorkDB()
{
    con = mysql_init(NULL);
}

CWorkDB::~CWorkDB()
{
    mysql_close(con);
}

MYSQL *CWorkDB::GetConnection() const
{
    return con;
}

bool CWorkDB::connect(const char *host, const char *login, const char *password, const char *database) const
{
    return mysql_real_connect(con, host, login, password, database, 0, NULL, 0);
}

bool CWorkDB::query(const char *_query) const
{
    return mysql_query(con, _query);
}

#pragma region _WorkWithTable_
void CWorkDB::SetTable(const std::string &_name)
{
    tableName = _name;
}

void CWorkDB::Print(const std::string &_row)
{
    std::string sQuery = "select ";
    sQuery.append(_row);
    sQuery.append("from ");
    sQuery.append(tableName);

    query(sQuery.c_str());
    res = mysql_store_result(con);

    if (res == NULL)
    {
        std::cout << "Error PrintTable";
        return;
    }

    int countColumn = mysql_field_count(con);
    if (mysql_num_rows(res) > 0)
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

bool CWorkDB::Insert(const char *_query)
{
    std::string sQuery = _query;
    sQuery.insert(0, " values (");
    sQuery.insert(0, tableName);
    sQuery.insert(0, "insert into ");

    sQuery.append(")");

    return query(sQuery.c_str());
}

bool CWorkDB::Delete(const char *_query)
{
    std::string sQuery("delete from ");
    sQuery.append(tableName);

    if (strcmp(_query, "") != 0)
    {
        sQuery.append(" Where ");
        sQuery.append(_query);
    }

    return query(sQuery.c_str());
}

#pragma endregion