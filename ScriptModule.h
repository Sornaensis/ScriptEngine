#ifndef __SCRIPT_MODULE_INCLUDED__
#define __SCRIPT_MODULE_INCLUDED__

#include <functional>
#include <string>
#include <vector>

#include "ScriptEntity.h"

using namespace std;

class ScriptEntity;

class ScriptModule {
    string ModuleName_;
    
    struct ScriptFunction { 
        function<ScriptEntity&(ScriptEntity&)> FunctionObj_;
        string FunctionName_; 
    };

    vector<ScriptFunction> ModuleFunctions_;

public:
    ScriptModule(string name);
    ~ScriptModule();

    bool bindFunction(string name, function<ScriptEntity&(ScriptEntity&)> fobj);  
    bool unbindFunction(string name);
};

#endif

