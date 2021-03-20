#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "class_loader.hpp"

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
}