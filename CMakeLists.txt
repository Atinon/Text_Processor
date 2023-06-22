cmake_minimum_required(VERSION 3.25)
project(Text_Processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Text_Processor
        main.cpp
        classes/TextProcessor.h
        classes/TextProcessor.cpp
        classes/Config.h
        classes/Config.cpp
        classes/line/BaseLine.h
        classes/line/BaseLine.cpp
        classes/line/BaseLineDerivedClasses.h
        classes/line/BaseLineDerivedClasses.cpp
        classes/line/LineParser.h
        classes/line/LineParser.cpp
        classes/file_workers/IFileReader.h
        classes/file_workers/IFileReader.cpp
        classes/file_workers/TextFileReader.h
        classes/file_workers/TextFileReader.cpp
        classes/file_workers/IFileWriter.h
        classes/file_workers/IFileWriter.cpp
        classes/file_workers/TextFileWriter.h
        classes/file_workers/TextFileWriter.cpp
        classes/command_handlers/ICommandHandler.h
        classes/command_handlers/ICommandHandler.cpp
        classes/command_handlers/ConsoleCommandHandler.h
        classes/command_handlers/ConsoleCommandHandler.cpp
)
