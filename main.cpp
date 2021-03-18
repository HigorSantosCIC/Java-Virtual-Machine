#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "class_reader.cpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Invalid args." << std::endl;
    exit(1);
  }

  // Get .class file name from args
  const char *file_name = argv[1];

  FILE *fp = fopen(file_name, "r");

  readClassFile(fp);
}  