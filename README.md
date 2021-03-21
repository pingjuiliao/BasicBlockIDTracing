## X86BasicBlockIDPass 

This little project assigns IDs to the each basic blocks.   
The MachineFunctionPass is built within the **clang**.  
Binaries compiled with clang are instrumented by default.  

### setup
The following command build LLVM framework, clang, and the pass.  
THIS TAKES HOURS !
```
# in the root of repo
./setup.py # 
```

### compile a program with instrumentation
```
# this script compile the sample/sample.c
./run.py
# and we will get a compiled binary ./a.out in this directory
./llvm-project-10.0.1/bin/build/clang ./sample/sample.c
#
```

### scripts
[X86BasicBlockID.cpp](llvm-project-10.0.1/llvm/lib/Target/X86/X86BasicBlockID.cpp)  
[X86TargetMachine.cpp](llvm-project-10.0.1/llvm/lib/Target/X86/X86TargetMachine.cpp)  
[X86.h](llvm-project-10.0.1/llvm/lib/Target/X86/X86.h)  
[CMakeLists.txt](llvm-project-10.0.1/llvm/lib/Target/X86/CMakeLists.txt)  


