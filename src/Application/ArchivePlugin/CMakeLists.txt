
macro (configure_zziplib)
    if ("${ZZIPLIB_ROOT}" STREQUAL "")
        file (TO_CMAKE_PATH "$ENV{ZZIPLIB_ROOT}" ZZIPLIB_ROOT)
    endif()
    if ("${ZZIPLIB_ROOT}" STREQUAL "")
        SET(ZZIPLIB_ROOT ${ENV_TUNDRA_DEP_PATH}/zziplib)
    endif()
    
    message("${ZZIPLIB_ROOT}")
    sagase_configure_package(ZZIPLIB
        NAMES zziplib zzip # zzip find headers. Important in NAMES so it will pick up /include instead of /include/zzip
        COMPONENTS zziplib zzip
        PREFIXES ${ZZIPLIB_ROOT} ${ENV_TUNDRA_DEP_PATH})
    
    sagase_configure_report (ZZIPLIB)
endmacro (configure_zziplib)

configure_zziplib ()

#################################################################################

# Define target name and output directory
init_target (ArchivePlugin OUTPUT plugins)

# Define source files
file (GLOB CPP_FILES *.cpp)
file (GLOB H_FILES *.h)

MocFolder ()
UiFolder ()

QT4_WRAP_CPP (MOC_SRCS ${H_FILES})

set (SOURCE_FILES ${CPP_FILES} ${H_FILES} ${MOC_SRCS})

use_package (ZZIPLIB)
use_core_modules (Framework Asset)

build_library (${TARGET_NAME} SHARED ${SOURCE_FILES})

link_modules (Framework Asset)
link_package (ZZIPLIB)

SetupCompileFlags()

final_target ()
