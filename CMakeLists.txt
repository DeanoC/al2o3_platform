include(FetchContent)
FetchContent_Declare( al2o3 GIT_REPOSITORY https://github.com/DeanoC/al2o3 GIT_TAG master )
FetchContent_GetProperties(al2o3)
if(NOT al2o3_POPULATED)
	FetchContent_Populate(al2o3)
	add_subdirectory(${al2o3_SOURCE_DIR} ${al2o3_BINARY_DIR})
endif()

SET_MIN_VERSIONS()
set(LibName al2o3_platform)
project(${LibName})


set(Interface
		debug.h
		platform.h
		platform_android.h
		platform_linux.h
		platform_osx.h
		platform_posix.h
		platform_win.h
		visualdebug.h
		windows.h
		)
set(Src
		debug.c
		visualdebug.c
		)
set(Deps)

ADD_LIB(${LibName} "${Interface}" "${Src}" "${Deps}")

set( Tests
		)
set( TestDeps
		)
ADD_LIB_TESTS(${LibName} "${Interface}" "${Tests}" "${TestDeps}")
