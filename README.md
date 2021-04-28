# About

This repository contains a simplified implementation of a Java Virtual Machine (JVM) that supports Java SE 8.

Almost all instruction set is implemented.

The entire code is based on a JVM specification by Tim Lindholm, Frank Yellin, Gilad Bracha and Alex Buckley, available in the official Oracle's documentation.

# Usage

In order to compile, link and build this project on Linux, paste the following command on a command line:

> $ make clean && make

Then, to execute the JVM, use:

> $ ./bin/jvm \<PATH\> \<VIEWER_MODE\>

## Flags:

- **\<PATH\>**: Path to .class file that will be read by the JVM.

- **\<VIEWER_MODE\>** (OPTIONAL): If desired, use the flag **"-v"** to initialize class file in viewer mode. This will display all data of class file.

# Documentation
By default, a documentation is available in /docs. If you still want to create the documentation, use the command: 

> & doxygen
