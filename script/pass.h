#ifndef PASS_H
#define PASS_H

#include "llvm/Pass.h"

class BasicBlockIDPass : public llvm::FunctionPass {
public :
    typedef unsigned long long BBID;
    static char ID ;
    BasicBlockIDPass() : llvm::FunctionPass(ID) {}
    virtual bool doInitialization(llvm::Module &M);
    virtual bool runOnFunction(llvm::Function &F) ;
private :
    void runOnBasicBlock(llvm::BasicBlock &B) ;
    BBID linearID(void) ;
}; 

#endif
