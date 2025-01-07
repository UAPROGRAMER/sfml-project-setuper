#include "lib/main.hpp"
#include "lib/interpreter.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

bool forsed = false;

std::string readsetupfile() {
  std::ifstream filestream("./setup.txt");

  if (!filestream) {
    if (forsed)
      return "";
    std::cerr << "[ ERROR ]: Failed to open a file or file not found. Add -f "
                 "to create project anyway.\n";
    exit(1);
  }

  std::stringstream buf;

  buf << filestream.rdbuf();

  return buf.str();
}

void create_project(std::unordered_map<std::string, std::string> &variables) {
  system("rm -f setup.txt");
  system("mkdir -p src");
  system("touch src/main.cpp");
  system("touch CMakeLists.txt");
  system("touch Makefile");

  {
    std::ofstream Makefile("./Makefile");
    if (!Makefile) {
      std::cerr << "[ ERROR ]: Unable to open Makefile.\n";
      exit(1);
    }
    Makefile
        << "BUILD_TYPE = Debug#Release\n"
        << "\n"
        << "SrcDir = src\n"
        << "BuildDir = build\n"
        << "DestDir = dest\n"
        << "DataDir = data\n"
        << "\n"
        << "CmakeExitName = exec\n"
        << "ProjectName = " << variables["name"] << "\n"
        << "ExitName = exit\n"
        << "\n"
        << "CmakeExit = $(BuildDir)/$(CmakeExitName)\n"
        << "Exit = $(DestDir)/$(ProjectName)/$(ExitName)\n"
        << "\n"
        << ".PHONY: all zip cmake clean\n"
        << "\n"
        << "all: $(Exit)\n"
        << "\n"
        << "zip: $(Exit)\n"
        << "\tcd $(DestDir) && zip -r $(ProjectName).zip $(ProjectName)\n"
        << "\n"
        << "$(Exit): cmake\n"
        << "\tcd $(BuildDir) && make\n"
        << "\tcp $(CmakeExit) $(Exit)\n"
        << "\ttest -d $(DataDir) && cp -R $(DataDir) "
           "$(DestDir)/$(ProjectName)/$(DataDir)\n"
        << "\n"
        << "cmake: CMakeLists.txt $(BuildDir)/\n"
        << "\tcmake -D CMAKE_BUILD_TYPE=$(BUILD_TYPE) -B $(BuildDir) -S .\n"
        << "\n"
        << "$(BuildDir)/:\n"
        << "\tmkdir -p $(BuildDir)\n"
        << "\n"
        << "$(DestDir)/:\n"
        << "\tmkdir -p $(DestDir)\n"
        << "\n"
        << "clean:\n"
        << "\trm -rf $(BuildDir) $(DestDir)";
  }

  {
    std::ofstream CMakeLists("./CMakeLists.txt");
    if (!CMakeLists) {
      std::cerr << "[ ERROR ]: Unable to open CMakeLists.txt.\n";
      exit(1);
    }
    CMakeLists << "cmake_minimum_required(VERSION 3.10)\n"
               << "\n"
               << "project(" << variables["name"] << ")\n"
               << "\n"
               << "set(CMAKE_CXX_STANDARD " << variables["cxxs"] << ")\n"
               << "set(CMAKE_CXX_STANDARD_REQUIRED " << variables["cxxsr"]
               << ")\n"
               << "\n"
               << "set(SOURCES src/main.cpp)\n"
               << "add_library(object OBJECT ${SOURCES})\n"
               << "\n"
               << "add_executable(exec $<TARGET_OBJECTS:object>)\n"
               << "\n"
               << "find_package(SFML " << variables["version"] << " COMPONENTS "
               << variables["libs"] << " REQUIRED)\n"
               << "target_link_libraries(exec " << variables["link"] << ")\n";
  }

  {
    std::ofstream Main("./src/main.cpp");
    if (!Main) {
      std::cerr << "[ ERROR ]: Unable to open main file.\n";
      exit(1);
    }
    Main << "#include <SFML/Window.hpp>\n"
         << "#include <SFML/Graphics.hpp>\n"
         << "#include <SFML/System.hpp>\n"
         << "\n"
         << "int main(void) {\n"
         << "\tsf::RenderWindow window(sf::VideoMode(400, 400), \"Hello, "
            "World!\");\n"
         << "\twhile (window.isOpen()) {\n"
         << "\t\tsf::Event event;\n"
         << "\t\twhile (window.pollEvent(event)) {\n"
         << "\t\t\tif (event.type == sf::Event::Closed) window.close();\n"
         << "\t\t}\n"
         << "\t}\n"
         << "}\n";
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    if (std::string(argv[1]) == std::string("-f")) {
      forsed = true;
    }
  }
  std::string setup = readsetupfile();

  std::vector<Token> tokens = Lexer(setup).tokenize();

  std::unordered_map<std::string, std::string> variables =
      Interpreter(tokens).run();

  // std::cout << "name = " << variables["name"] << '\n';
  // std::cout << "version = " << variables["version"] << '\n';
  // std::cout << "libs = " << variables["libs"] << '\n';
  // std::cout << "cxxs = " << variables["cxxs"] << '\n';
  // std::cout << "cxxsr = " << variables["cxxsr"] << '\n';
  // std::cout << "link = " << variables["link"] << std::endl;

  create_project(variables);

  return 0;
}
