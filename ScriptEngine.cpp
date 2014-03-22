#include "ScriptEngine.h"


ScriptEngine::ScriptEngine() {

}

ScriptEngine::~ScriptEngine() {

}

void ScriptEngine::addBuiltin(shared_ptr<ScriptModule> builtin) {

}

bool ScriptEngine::buildProgram() {

}
bool ScriptEngine::buildProgram(string filename) {

}
bool ScriptEngine::buildProgramRaw(string program) {

}

string ScriptEngine::getError() {

}

void ScriptEngine::execScript() {

}
void ScriptEngine::execScript(string entity) {

}
