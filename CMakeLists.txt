cmake_minimum_required(VERSION 3.02)


project(Grawitacja)

option(SFML_STATIC "Is SFML built as a static library?" TRUE)

set(SFML_STATIC_LIBRARIES ${SFML_STATIC})

option(GRAVITY_STATIC "Do you want the final executable to be statically linked?" TRUE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

if(GRAVITY_STATIC) 
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

include_directories(${SFML_DIR}/include)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)



add_executable(Grawitacja ${PROJECT_SOURCE_DIR}/CB_selector.cpp ${PROJECT_SOURCE_DIR}/CB_gen.cpp ${PROJECT_SOURCE_DIR}/UI_state.cpp ${PROJECT_SOURCE_DIR}/UI_masterpanel.cpp ${PROJECT_SOURCE_DIR}/Button.cpp ${PROJECT_SOURCE_DIR}/Grawitacja.cpp ${PROJECT_SOURCE_DIR}/Simulator.cpp ${PROJECT_SOURCE_DIR}/Celestial_body.cpp ${PROJECT_SOURCE_DIR}/Space_objects.cpp ${PROJECT_SOURCE_DIR}/ResourceLoader.cpp ${PROJECT_SOURCE_DIR}/Textbox.cpp)



target_link_libraries(Grawitacja sfml-graphics)