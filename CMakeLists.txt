cmake_minimum_required(VERSION 3.25)
project(Text_Processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Text_Processor
        main.cpp
        classes/TextProcessor.h
        classes/TextProcessor.cpp
        classes/line/BaseLine.h
        classes/line/BaseLine.cpp
        classes/line/LineFactory.h
        classes/line/LineFactory.cpp
        classes/file_workers/IFileReader.h
        classes/file_workers/IFileReader.cpp
        classes/file_workers/IFileWriter.h
        classes/file_workers/IFileWriter.cpp
)
