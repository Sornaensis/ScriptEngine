#include "ScriptModule.h"

ScriptModule::ScriptModule(string name) {

}
ScriptModule::~ScriptModule() {

}

bool ScriptModule::bindFunction(string name, function<ScriptEntity&(ScriptEntity&)> fobj) {

} 
bool ScriptModule::unbindFunction(string name) {

}
