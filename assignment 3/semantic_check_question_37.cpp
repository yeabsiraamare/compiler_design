#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/* Represents a function parameter */
struct Parameter {
    string name;
    string type;
};

/* Represents a function declaration */
struct Function {
    string name;
    string returnType;
    vector<Parameter> parameters;
};

/* Semantic Analyzer */
class SemanticAnalyzer {
private:
    unordered_map<string, Function> functionTable;
    unordered_set<string> validTypes = {"int", "float", "double", "void", "bool", "char"};

public:
    // Check if a type is valid
    bool isValidType(const string& type) {
        return validTypes.count(type) > 0;
    }

    // Perform semantic checks for function declaration
    bool declareFunction(const Function& func) {

        // Rule 1: Function name must be unique
        if (functionTable.count(func.name)) {
            cout << "Semantic Error: Function '" << func.name
                 << "' is already declared." << endl;
            return false;
        }

        // Rule 2: Return type must be valid
        if (!isValidType(func.returnType)) {
            cout << "Semantic Error: Invalid return type '"
                 << func.returnType << "' in function '"
                 << func.name << "'." << endl;
            return false;
        }

        // Rule 3: Validate parameters
        unordered_set<string> parameterNames;
        for (const auto& param : func.parameters) {

            if (!isValidType(param.type)) {
                cout << "Semantic Error: Invalid parameter type '"
                     << param.type << "' in function '"
                     << func.name << "'." << endl;
                return false;
            }

            if (param.type == "void") {
                cout << "Semantic Error: Parameter '" << param.name
                     << "' in function '" << func.name
                     << "' cannot have type void." << endl;
                return false;
            }

            if (parameterNames.count(param.name)) {
                cout << "Semantic Error: Duplicate parameter name '"
                     << param.name << "' in function '"
                     << func.name << "'." << endl;
                return false;
            }

            parameterNames.insert(param.name);
        }

        // Rule 4: Store function if all checks pass
        functionTable[func.name] = func;
        cout << "Function '" << func.name
             << "' declared successfully." << endl;
        return true;
    }
};

int main() {
    SemanticAnalyzer analyzer;

    Function f1;
    f1.name = "sum";
    f1.returnType = "int";
    f1.parameters = {
        {"a", "int"},
        {"b", "int"}
    };

    Function f2;
    f2.name = "sum";   // Duplicate function name
    f2.returnType = "int";
    f2.parameters = {
        {"x", "int"},
        {"y", "int"}
    };

    analyzer.declareFunction(f1);
    analyzer.declareFunction(f2);  // Will produce semantic error

    return 0;
}
