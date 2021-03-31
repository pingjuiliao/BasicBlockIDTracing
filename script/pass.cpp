
#include "pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/ADT/SmallVector.h"
using namespace llvm;

BasicBlockIDPass::BBID
BasicBlockIDPass::linearID(void) {
    static BasicBlockIDPass::BBID count = 0 ;
    const BasicBlockIDPass::BBID prefix = 0 ;
    return (prefix + count++); 
}

bool
BasicBlockIDPass::doInitialization(Module &M) {
    LLVMContext& C = M.getContext() ;
    // xor space
    IntegerType* ty = IntegerType::getInt32Ty(C); 
    Constant* zero  = ConstantInt::get(IntegerType::getInt32Ty(C), 0) ;
    xor_space = new GlobalVariable(M, ty, false, GlobalValue::CommonLinkage, zero, "__LLVM_xor_u32");
    return false; 
}

bool 
BasicBlockIDPass::runOnFunction(Function &F) {
    for ( Function::iterator it = F.begin(); it != F.end() ; ++it ) {
        if ( !it->empty() )
            runOnBasicBlock(*it) ;
    }
    return true ;

}

void
BasicBlockIDPass::runOnBasicBlock(BasicBlock &B) {
    Instruction *pi = B.getFirstNonPHI() ;
    Module* M = pi->getModule() ;
    LLVMContext& C = pi->getContext() ;
    
    
    // start building IRs
    IRBuilder<> IRB(pi) ;
    auto *voidT = IRB.getVoidTy();
    auto *int32T = IRB.getInt32Ty();
    FunctionCallee func_BB_linearID = M->getOrInsertFunction("_bbid_linear", voidT, int32T);
    BasicBlockIDPass::BBID bbid = linearID();
    Constant* const_bbid = IRB.getInt32(bbid) ;
    IRB.CreateCall(func_BB_linearID, const_bbid);
    

}


char BasicBlockIDPass::ID = 0;

static RegisterPass<BasicBlockIDPass> X("BB's ID",
                                        "basic block ID",
                                        false, false) ;

static RegisterStandardPasses Y(
        PassManagerBuilder::EP_EarlyAsPossible,
        [](const PassManagerBuilder &Builder,
            legacy::PassManagerBase &PM) {
            PM.add(new BasicBlockIDPass()) ;
        }
        );
/*
static void
registerBasicBlockIDPass(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
    PM.add(new BasicBlockIDPass());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible, registerBasicBlockIDPass);
*/
