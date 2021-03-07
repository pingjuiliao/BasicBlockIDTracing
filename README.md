## BasicBlockIDPass 
This little project assigns IDs to the each basic blocks and print it  . 
It requires LLVM 10.0.1 and a compatible **clang** to build the project  

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
```

### outputs
The execution path determines the set/order of IDs of basic blocks.  

```
$ echo "aa" | ./a.out
This basic block ID is 19
This basic block ID is 16
This basic block ID is 18
This basic block ID is 0
This basic block ID is 1
hello
This basic block ID is 6
This basic block ID is 7
This basic block ID is 9
This basic block ID is 10
Alice
This basic block ID is 15

$ echo "ab" | ./a.out
This basic block ID is 19
This basic block ID is 16
This basic block ID is 18
This basic block ID is 0
This basic block ID is 1
hello
This basic block ID is 6
This basic block ID is 7
This basic block ID is 9
This basic block ID is 11
This basic block ID is 12
Bob
This basic block ID is 14
This basic block ID is 15

$ echo "ba" | ./a.out
This basic block ID is 19
This basic block ID is 16
This basic block ID is 18
This basic block ID is 0
This basic block ID is 2
This basic block ID is 3
hi
This basic block ID is 5
This basic block ID is 6
This basic block ID is 7
This basic block ID is 9
This basic block ID is 10
Alice
This basic block ID is 15
```


