#include "db.h"
#include <sstream>

int main(void)
{
    CWorkDB workDB;
    if (workDB.GetConnection() == nullptr)
        return 0;

    std::string host, login, password, database;

    std::cout << "Host: ";
    std::getline(std::cin, host);

    std::cout << "login: ";
    std::getline(std::cin, login);

    std::cout << "password: ";
    std::getline(std::cin, password);

    std::cout << "database: ";
    std::getline(std::cin, database);

    if (!workDB.connect((char *)"localhost", (char *)"root", (char *)"", (char *)"testdb"))
    {
        std::cout << "Error Connect";
        return -1;
    }

    workDB.SetTable("user");

    ID formId;
    // Сформированный запрос вставки через запятую
    if (workDB.Insert((char *)"5, 'FIO'") == false)
    {
        std::cout << "Error InsertToTable";
        return -1;
    }

    if (workDB.Delete("id = 5") == false)
    {
        std::cout << "Error DeleteFromtable";
    }

    workDB.Print();

    return 0;
}