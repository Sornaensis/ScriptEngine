#ifndef __SCRIPT_ENGINE_INCLUDED__
#define __SCRIPT_ENGINE_INCLUDED__

#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "ScriptParser.h"
#include "ScriptTokenizer.h"
#include "ScriptEntity.h"
#include "ScriptModule.h"

using namespace std;

class ScriptParser;
class ScriptEntity;
class ScriptModule;

class ScriptEngine {
    shared_ptr<ScriptParser> Parser_;
    
    vector<shared_ptr<ScriptEntity> > CodeTable_;

    vector<shared_ptr<ScriptModule> > Builtin_;
    
    string ErrMsg_;
public:

    ScriptEngine();
    ~ScriptEngine();

    void addBuiltin(shared_ptr<ScriptModule> builtin);

    bool buildProgram();
    bool buildProgram(string filename);

    bool buildProgramRaw(string program);

    string getError(); 

    void execScript();
    void execScript(string entity);

};

#endif 
