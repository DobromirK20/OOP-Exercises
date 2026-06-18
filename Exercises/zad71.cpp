#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class DatabaseException : public runtime_error
{
public:
    DatabaseException(const string& message) : runtime_error(message) {}
};

class DatabaseConnection
{
public:
    DatabaseConnection() {
        cout << "Connected to database" << endl;
    }

    void executeQuery(const string& query) {
        try
        {
            if(query.empty()) {
                throw invalid_argument("Empty query");
            }

            if(query == "BAD_QUERY") {
                throw runtime_error("Syntax error");
            }

            if(query == "DISCONNECTED") {
                throw logic_error("Database connection lost");
            }

            cout << "Query executed successfully" << endl;
        }
        catch(const exception& e)
        {
            throw DatabaseException(string("Database error: ") + e.what());
        }        
    }
};

int main() {
    try
    {
        DatabaseConnection con;

        con.executeQuery("SELECT");
        con.executeQuery("BAD_QUERY");
    }
    catch(const DatabaseException& e)
    {
        cout << e.what() << '\n';
    }
    
    return 0;
}

