#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
    struct BasicBlockIDPass : public FunctionPass {
        static char ID ;
        BasicBlockIDPass() : FunctionPass(ID) {}
        virtual bool runOnFunction(Function &F) ;
    };

}


bool BasicBlockIDPass::runOnFunction(Function &F) {
    errs() << "I saw a function called " << F.getName() << "\n" ;
    return true;
}


char BasicBlockIDPass::ID = 0;

static void
registerBasicBlockIDPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new BasicBlockIDPass());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerBasicBlockIDPass);
