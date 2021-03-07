#!/usr/bin/python3
import os
pwd = "."
def error(msg) :
    print("Error: " + msg)
    quit()

def build_llvm() :
    llvm_root = "./llvm-project-10.0.1"
    llvm_build= llvm_root + "/build"
    if not os.path.exists(llvm_root) :
        error("Please change directory to the root of repo")
    if not os.path.exists(llvm_build) :
        os.mkdir(llvm_build)
    pwd = os.path.abspath(os.getcwd())
    os.chdir(llvm_build)
    # cmake
    os.system('cmake -DLLVM_ENABLE_PROJECTS=clang -G "Unix Makefiles" ../llvm')

    # make
    os.system('make')
    os.chdir(pwd)

def build_pass() :
    build_dir = "./build"
    if not os.path.exists(build_dir) :
        os.mkdir(build_dir)
    os.chdir(build_dir)
    # cmake
    os.system('cmake ..')

    # make
    os.system('make')

def main() :
    build_llvm()
    build_pass()
    print("Done !")

if __name__ == '__main__' :
    main()
