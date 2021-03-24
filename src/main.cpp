#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "class_loader.hpp"
#include "memory_cleaner.hpp"
#include "class_viewer.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Invalid args." << std::endl;
    exit(1);
  }

  // Get .class file name from args
  const char *file_name = argv[1];

  ClassLoader class_loader(file_name);
  class_loader.readClassFile();
  ClassFile *class_file = class_loader.getClassFile();

  ClassViewer class_viewer(class_file);
  class_viewer.printClassFile();

  // MemoryCleaner memory_cleaner(class_file);
  // memory_cleaner.freeClassFileMemory();

  free(class_file);
}