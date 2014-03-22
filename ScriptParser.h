#ifndef __SCRIPT_PARSER_INCLUDED__
#define __SCRIPT_PARSER_INCLUDED__

#include <memory>
#include <string>

#include "ScriptEngine.h"
#include "ScriptTokenizer.h"

using namespace std;

class ScriptEngine;
class ScriptTokenizer;

class ScriptParser {
    friend class ScriptEngine;

    shared_ptr<ScriptTokenizer> Tokenizer_;
    
public:

    ScriptParser();
    ~ScriptParser();

    string parseProgram(string program, ScriptEngine* engine);

};

#endif

