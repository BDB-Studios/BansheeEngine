# Source files and their filters
include(CMakeSources.cmake)

source_group("Header Files\\Generated" FILES ${BS_GENERATED_EDITOR_H_FILES})
source_group("Source Files\\Generated" FILES ${BS_GENERATED_EDITOR_CPP_FILES})

# Includes
set(SBansheeEditor_INC 
	"./"
	"../BansheeUtility" 
	"../BansheeCore"
	"../BansheeEngine"
	"../BansheeEditor"
	"../BansheeMono"
	"../SBansheeEngine"
	"${PROJECT_BINARY_DIR}/Generated/Engine/Include"
	"${PROJECT_BINARY_DIR}/Generated/Editor/Include")

include_directories(${SBansheeEditor_INC})	

# Target
add_library(SBansheeEditor SHARED 
	${BS_SBANSHEEEDITOR_SRC} 
	${BS_GENERATED_EDITOR_H_FILES} 
	${BS_GENERATED_EDITOR_CPP_FILES})

# Defines
target_compile_definitions(SBansheeEditor PRIVATE -DBS_SCR_BED_EXPORTS)

# Libraries
## Local libs
target_link_libraries(SBansheeEditor SBansheeEngine BansheeMono BansheeEditor BansheeEngine BansheeUtility BansheeCore)

# IDE specific
set_property(TARGET SBansheeEditor PROPERTY FOLDER Script)