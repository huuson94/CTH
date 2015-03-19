/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO
  Type* temp = (Type*)malloc(sizeof(Type));
  temp->typeClass = type->typeClass;
  if(temp->typeClass == TP_ARRAY){
    temp->arraySize = type->arraySize;
    temp->elementType = duplicateType(type->elementType);
  }
  return temp;
}

int compareType(Type* type1, Type* type2) {
  // TODO
  if(type1->typeClass == type2->typeClass) {
    if(type1->typeClass == TP_ARRAY){
      if(type1->arraySize == type2->arraySize){
        return compareType(type1->elementType, type2->elementType);
      }
      else return 0;
    }
    else return 1;
  }
  else return 0;
}

void freeType(Type* type) {
  // TODO
  switch(type->typeClass){
    case(TP_INT):
    case(TP_CHAR):
    free(type);
    break;
    case(TP_ARRAY):
    free(type->elementType);
    free(type);
    break;
  }
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
  ConstantValue* temp = (ConstantValue*)malloc(sizeof(ConstantValue));
  temp->type = TP_INT;
  temp->intValue = i;
  return temp;
}

ConstantValue* makeCharConstant(char ch) {
  // TODO
  ConstantValue* temp = (ConstantValue*)malloc(sizeof(ConstantValue));
  temp->type = TP_CHAR;
  temp->charValue = ch;
  return temp;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
  ConstantValue* temp = (ConstantValue*)malloc(sizeof(ConstantValue));
  temp->type = v->type;
  if(v->typeClass == TP_INT){
    temp->intValue == v->intValue;
  }
  if(v->typeClass == TP_CHAR){
    temp->charValue = v->charValue;
  }
  return temp;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO
  Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_CONSTANT;
  temp->constAttrs = (ConstantAttributes*)malloc(sizeof(ConstantAttibutes));
  return temp;
}

Object* createTypeObject(char *name) {
  // TODO
  Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_TYPE;
  temp->typeAttrs = (TypeAttributes*)malloc(sizeof(TypeAttibutes));
  return temp;
}

Object* createVariableObject(char *name) {
  // TODO
  Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_VARIABLE;
  temp->varAttrs = (VarAttributes*)malloc(sizeof(VarAttibutes));
  return temp;
}

Object* createFunctionObject(char *name) {
  // TODO
  Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_FUNCTION;
  temp->funcAttrs = (FuncAttributes*)malloc(sizeof(FunctionAttibutes));
  return temp;
}

Object* createProcedureObject(char *name) {
  // TODO
} Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_PROCEDURE;
  temp->procAttrs = (ProcedureAttributes*)malloc(sizeof(ProcedureAttibutes));
  return temp;

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
  Object* temp = (Object*) malloc(sizeof(Object));
  strcpy(temp->name, name);
  temp->kind = OBJ_PARAMETER;
  temp->paramAttrs = (ParameterAttributes*)malloc(sizeof(ParameterAttibutes));
  return temp;
}

void freeObject(Object* obj) {
  // TODO
  switch (obj->kind) {
  case OBJ_CONSTANT:
    free(obj->constAttrs->value);
    free(obj->constAttrs);
    break;
  case OBJ_TYPE:
    free(obj->typeAttrs->actualType);
    free(obj->typeAttrs);
    break;
  case OBJ_VARIABLE:
    free(obj->varAttrs->type);
    free(obj->varAttrs);
    break;
  case OBJ_FUNCTION:
    freeReferenceList(obj->funcAttrs->paramList);
    freeType(obj->funcAttrs->returnType);
    freeScope(obj->funcAttrs->scope);
    free(obj->funcAttrs);
    break;
  case OBJ_PROCEDURE:
    freeReferenceList(obj->procAttrs->paramList);
    freeScope(obj->procAttrs->scope);
    free(obj->procAttrs);
    break;
  case OBJ_PROGRAM:
    freeScope(obj->progAttrs->scope);
    free(obj->progAttrs);
    break;
  case OBJ_PARAMETER:
    freeType(obj->paramAttrs->type);
    free(obj->paramAttrs);
  }
  free(obj);
}

void freeScope(Scope* scope) {
  // TODO
  freeObjectList(scope->objList);
  free(scope);
}

void freeObjectList(ObjectNode *objList) {
  // TODO
  ObjectNode* list = objList;

  while (list != NULL) {
    ObjectNode* node = list;
    list = list->next;
    freeObject(node->object);
    free(node);
  }
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  ObjectNode* list = objList;

  while (list != NULL) {
    ObjectNode* node = list;
    list = list->next;
    free(node);
  }
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
  while (objList != NULL) {
    if (strcmp(objList->object->name, name) == 0) 
      return objList->object;
    else objList = objList->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


