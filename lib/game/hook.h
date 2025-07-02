
/////////////////////////////////////
//       Some_Terminal_Game        //
//        lib/game/hook.h          //
//                                 //
/////////////////////////////////////
#ifndef _HOOK_API
#define _HOOK_API

#include <stdio.h>
#include <stdlib.h>
#include "resources.h"
#include "../handle/debug/c_handle.h"
#include "../handle/debug/etc/error.h"
#define MAX_FUNCTIONS_PER_HOOK 55

typedef void (*FunctionHook_t)(void);
typedef struct HookRoot{
    bool isActive;
    bool isSignaled;
    bool manualReset;
    FunctionHook_t Functions[MAX_FUNCTIONS_PER_HOOK];
    int FunctionCount;
    // "self" functions -- will be defined upon creation
    bool (*AddFunction)(struct HookRoot* self, FunctionHook_t func);
    void (*Fire)(struct HookRoot* self); //args can be NULL
    void (*Reset)(struct HookRoot* self);
}HookRoot,*pHookRoot;

bool __hookInternal_AddFunction(pHookRoot self,FunctionHook_t func){
    _stack_;
    _check_bp;
    if(self->FunctionCount >= MAX_FUNCTIONS_PER_HOOK){
        return false;
    }
    self->Functions[self->FunctionCount] = func;
    self->FunctionCount++;
    return true;
}

void __hookInternal_Reset(pHookRoot self){
    _stack_;
    _check_bp;
    self->isSignaled = false;
}

void __hookInternal_Fire(pHookRoot self){
    _stack_;
    _check_bp;
    for(int i = 0; i < self->FunctionCount; i++){
        self->Functions[i]();
    }
    //reset
    self->Reset(self);
}

bool CreateHookRoot(pHookRoot root,bool isActive,bool ManualReset){
    _stack_;
    _check_bp;
    root->manualReset = ManualReset;
    root->isActive = isActive;
    root->FunctionCount = 0;
    root->Fire = __hookInternal_Fire;
    root->AddFunction = __hookInternal_AddFunction;
    return true;
}


#endif