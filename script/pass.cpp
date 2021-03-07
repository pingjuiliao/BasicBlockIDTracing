
#include "pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
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
BasicBlockIDPass::runOnFunction(Function &F) {
    for ( Function::iterator it = F.begin(); it != F.end() ; ++it ) {
        runOnBasicBlock(*it) ;
    }
    return true ;

}

void
BasicBlockIDPass::runOnBasicBlock(BasicBlock &B) {
    Instruction *pi = B.getFirstNonPHI() ;
    Module* M = pi->getModule() ;
    LLVMContext& C = pi->getContext() ;
    FunctionCallee func_printf = M->getFunction("printf");
    
    // start building IRs
    IRBuilder<> IRB(pi) ;
    
    // alloca %x
    unsigned addr = 0 ;
    AllocaInst* alloc = IRB.CreateAlloca(Type::getInt64Ty(C), addr);

    // store Constant, %x
    BasicBlockIDPass::BBID bbid = linearID() ;
    Constant* id = IRB.getInt64(bbid) ;
    IRB.CreateStore(id, alloc);

    // %y = load %x
    LoadInst* load_id = IRB.CreateLoad(alloc) ;
     

    // call printf(".." , y)
    Value* fmt_str = IRB.CreateGlobalStringPtr("This basic block ID is %lld\n") ;
    SmallVector<Value *, 2> args_printf({fmt_str, load_id});
    CallInst* call_printf = IRB.CreateCall(func_printf, args_printf) ;
    

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
