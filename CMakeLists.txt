cmake_minimum_required(VERSION 3.21)
project(shared_buffers)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(shared_buffers main.cpp MyProcess.cpp MyProcess.h SharedCharBuffer.cpp SharedCharBuffer.h BufferException.cpp BufferException.h types.h types.cpp example_apps/animal_name_translator/ANGenerator.cpp example_apps/animal_name_translator/ANGenerator.h example_apps/SimpleExamples.cpp example_apps/SimpleExamples.h example_apps/animal_name_translator/ANTranslator.cpp example_apps/animal_name_translator/ANTranslator.h example_apps/animal_name_translator/ANReceiver.cpp example_apps/animal_name_translator/ANReceiver.h example_apps/animal_name_translator/AnimalNames.h)
