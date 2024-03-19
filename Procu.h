
#pragma once
#include <iostream>
#include <string>
#include <windows.h>


#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

int newnodrug;

void checkpoint()
{
    system("cls");
    Sleep(1000);

    cout << "\t\t\t\t\t\t\n\n\n\n Welcome Procument!!";
    cout << "\t\t\n\nThe system will now load the drugs from the database. Please be patient...";
    system("cls");

    Driver* driver;
    Connection* con;
    driver = get_driver_instance();
    // here change your username and password as intended
    con = driver->connect("tcp://127.0.0.1:3306", "root", "LastDance23!");

    con->setSchema("Drug_Inventory");

    Statement* stmt;
    stmt = con->createStatement();

    ResultSet* res;
    res = stmt->executeQuery("SELECT * FROM drug_table");

    while (res->next()) {
        int ID = res->getInt(1);
        int Quantity = res->getInt(2);
        string Drugname = res->getString(3);
        string Brand = res->getString(4);
        cout << "\t\t " << ID << "\t\t" << Quantity << " \t\t" << Drugname << " \t\t " << Brand << endl;

    }
    cout << "What would you like to perform?\n\n\t 1.Restock on drugs\n\n\t 2. Remove specific drug\n\n\t\t";

    int procchoice;
    cin >> procchoice;
    switch (procchoice)
    {
    case 1:
        system("cls");
        Sleep(1000);
       

        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM drug_table WHERE ID = " + std::to_string(newnodrug));
        if (!res->next()) {
            cout << "Drug not found." << endl;
            delete res;
            break;
        }

        cout << "\t\t\n\n How many are you adding?: ";
        int newnumber;
        cin >> newnumber;

        // Prepare a statement to update the quantity column in the table
        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE drug_table SET Quantity = Quantity + ? WHERE ID = ?");
        pstmt->setInt(1, newnumber);
        pstmt->setInt(2, newnodrug);

        // Execute the statement and update the table
        int rowsAffected = pstmt->executeUpdate();
        cout << rowsAffected << " row(s) updated." << endl;

        // Close the prepared statement
        delete pstmt;

        Sleep(1000);

        break;
  

    }
}