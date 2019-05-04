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
		windows.h
		)
set(Src
		debug.c
		)
set(Deps)

ADD_LIB(${LibName} "${Interface}" "${Src}" "${Deps}")

set( Tests
		)
set( TestDeps
		)
ADD_LIB_TESTS(${LibName} "${Interface}" "${Tests}" "${TestDeps}")
