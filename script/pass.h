#ifndef PASS_H
#define PASS_H

#include "llvm/Pass.h"
#include "llvm/IR/GlobalVariable.h"

class BasicBlockIDPass : public llvm::FunctionPass {
public :
    typedef unsigned long BBID;
    static char ID ;
    BasicBlockIDPass() : llvm::FunctionPass(ID) {}
    virtual bool doInitialization(llvm::Module &M);
    virtual bool runOnFunction(llvm::Function &F) ;
private :
    llvm::GlobalVariable* xor_space ;
    void runOnBasicBlock(llvm::BasicBlock &B) ;
    BBID linearID(void) ;
}; 

#endif
