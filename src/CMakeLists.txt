# creates a new subproject for the visual studio solution "Schuelerpraktikum_SS18"
project(MedicalVisualization)

message(STATUS "Building ${PROJECT_NAME}")

# A list of header (.h) files to be included into the project
set(Includes
	CTImageExample.h
	LoopsAndConditions.h
	PointerAndReferences.h
	SphereSourceExample.h
	DynamicImage.h
	userinput.h
	visualization3D.h
	spine.h
	Labels.h
	)

# A list of source (.cpp) files to be included into the project
set(Sources
	src/CTImageExample.cpp
	src/DynamicImage.cpp
	src/LoopsAndConditions.cpp
	src/main.cpp
	src/PointerAndReferences.cpp
	src/SphereSourceExample.cpp
	src/userinput.cpp
	src/visualization3D.cpp
	src/spine.cpp
	src/labels.cpp
	)

# creates a new application with the same name as the current subproject "MedicalVisualization"
# and the files we listed above
add_executable(${PROJECT_NAME}
	${Includes}
	${Sources}
	)

# this sets internal configurations and is required for VTK
include(${VTK_USE_FILE})

# define the libraries this project depends on
target_link_libraries(${PROJECT_NAME}
	${VTK_LIBRARIES}
	)

# order the files in the solution explorer appropriately
source_group("Header Files" FILES
	${Includes}
	)
source_group("Sources" FILES
	${Sources}
	)

message (STATUS "${CMAKE_BINARY_DIR}/bin/")
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")