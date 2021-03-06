#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "class_loader.hpp"
#include "memory_cleaner.hpp"
#include "class_viewer.hpp"
#include "runtime_data_area.hpp"
#include "interpreter.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Invalid args." << std::endl;
    exit(1);
  }

  // Get .class file name from args
  const char *file_name = argv[1];

  // Mode 1: Interpreter, Mode 2: Viewer
  int mode = 1;

  if (argc == 3)
  {
    if (strcmp(argv[2], "-v") == 0)
    {
      mode = 2;
    }
  }

  ClassLoader class_loader(file_name);
  class_loader.readClassFile();

  ClassFile *class_file = class_loader.getClassFile();
  std::string class_name = class_file->getClassName();

  if (mode == 1)
  {
    Frame *main_frame = new Frame(class_file, "main", "([Ljava/lang/String;)V");

    RuntimeDataArea *runtime_data_area = new RuntimeDataArea();
    runtime_data_area->method_area->addClass(class_name, class_file);

    // Initialize frame stack with main and (TODO) init (if exists) methods
    runtime_data_area->frame_stack->push(main_frame);

    Interpreter interpreter(runtime_data_area);
    interpreter.run();
  }
  else if (mode == 2)
  {
    ClassViewer class_viewer(class_file);
    class_viewer.printClassFile();
  }

  // MemoryCleaner memory_cleaner(class_file);
  // memory_cleaner.freeClassFileMemory();

  free(class_file);
}