## Purpo

[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/yangzh1998/purpo.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/yangzh1998/purpo/context:cpp)
[![Build Status](https://app.travis-ci.com/yangzh1998/purpo.svg?branch=main)](https://app.travis-ci.com/yangzh1998/purpo)

---

### 0. A Naive Example
```
import lol::wow as wow; # import a module

# declare a global variable
# make it visible in other module, by <module-name>::wordCountMap
wordCountMap;

# Init() is automatically called when this module is imported the 1st time.
# Init() can't read or write variables defined in other modules.
func Init() {
  wordCountMap = {"cat": 1}; # assign a map by literal value
  # no return in Init()
}

func Main() {
  for word, count in wordCountMap {
    # call Print function in the official library
    Print("%s: %d; ", word, count + lol::wow::num);
  }
  return 0; # Main() should return an integer
}
```


### 1. Introduction
Purpo is a dynamic and strong typed, non-object-oriented programming language. 
Currently, purc (i.e. Purpo Compiler) offers the Ahead-of-Time (AOT) compilation 
from .pur source file to machine code.

#### 1.1 Type System
The six built-in types are bool, i61, f61, str, array, map, 
and pointer is not supported.
At the logic level, bool, i61, f61 and str variables are passed by value, 
while the others by reference. 
An array or a map can hold elements of different types except that 
only hashable (bool, i61, f61, str) variables are qualified to be map keys.
The null value doesn't belongs to any types.

Users are not allowed to define other classes.

#### 1.2 Function
A function can either have a return value or not.

Init() is automatically called when this module is imported by others.
It can't reach variables defined in other modules, and it has no return. 

Main() is called as the entry of the program when running this module.

#### 1.3 Module
Each purpo source file forms a module. When importing a module, 
the search order is:
* The official library
* Third-party libraries under certain directory
* The directory specified by user in command line tools.
* The directory which the importer source file is in

Use "::" instead of '/' in the module path.

#### 1.4 Grammar
* Keywords: func, return, for, in, if, else, while, break, continue, 
  true, false, null, import

* Single line comments go after '#', and multi-line comments is not supported.

* Attention: Tab is illegal. Please use spaces to indent.

* Purpo adopts an LL(1) syntax. Read bnf.txt for more details.


### 2. Getting started
LLVM Clang++ or Apple Clang++ is recommended for this project.
After Clang is installed, make sure the command `clang++` is ready to use.
Specify Clang as the compiler by setting -DCMAKE_CXX_COMPILER if necessary.

To make
```shell
mkdir build && cd build
cmake .. -DLLVM_DIR="<LLVM-installation>/lib/cmake/llvm" -DCMAKE_INSTALL_PREFIX="<install-dir>"
make && make runtime
```

To install after making
```shell
[sudo] make install
```

To uninstall
```shell
cat install_manifest.txt | [sudo] xargs rm
```

To test
```shell
make test
```


### 3. Recommended Code Style
#### 3.1 Naming
| Type | Naming Style | Examples |
|---|---|---|
| Variable | Camel | mCount, studentList |
| Function | Pascal | GetLine, SetName |
| Module | Underscored | org_naive_utils |

#### 3.2 Space, Indent and Newline
* Indent: 2 spaces(unforced), no tab(forced!)
* 1 Space between operator and variables
* No newline before '(', '[', '{'
* 80 characters limited per line


### 4. Runtime
#### 4.1 Variables
Variables of all those types occupy 8 bytes for each, called PurObject.
In the real implementation, all PurObject are passed by value,
including those representing array and map variables.
An array PurObject invisibly holds a pointer of a length-flexible vector
to implement the reference meaning, so as a map PurObject.

#### 4.2 Memory: Stack and Heap

#### 4.3 Garbage Collection
