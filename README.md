# About

This repository contains an implementation of a Java Virtual Machine (JVM) that supports Java SE 8.

The entire code is based on a JVM specification by Tim Lindholm, Frank Yellin, Gilad Bracha and Alex Buckley, available in the official Oracle's documentation.

# Usage

In order to compile, link and build this project on Linux, paste the following command on a command line:

> $ make clean && make

Then, to execute the JVM, use:

> $ ./bin/jvm \<PATH\>

## Flags:

- **\<PATH\>**: Path to .class file that will be read by the JVM.
