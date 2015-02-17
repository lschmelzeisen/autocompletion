# autocompletion

A fast top-k completion based on a compressed trie (see http://www.di.unipi.it/~ottavian/files/topk_completion_www13.pdf).

Queries can be directed via ØMQ over a sockjsproxy (https://bitbucket.org/vladev/sockjsproxy) directly from the web browser.

## Building

Autocommpletion is build with [CMake](http://www.cmake.org/). Only out-of-source-tree builds are supported, so do:

    mkdir MY_BUILD_DIR
    cd MY_BUILD_DIR
    cmake AUTOCOMPLETION_SOURCE_DIR
    make

CMake also supports creation of Eclipse or MSVC project files, so you don't have to use `make`. 
