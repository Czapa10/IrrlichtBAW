
include(common RESULT_VARIABLE RES)
if(NOT RES)
	message(FATAL_ERROR "common.cmake not found. Should be in {repo_root}/cmake directory")
endif()

set(RAY_TRACED_AO_EXAMPLE_LIBS
	${IRR_EXT_MITSUBA_LOADER_LIB}
	${MITSUBA_LOADER_DEPENDENT_LIBS}
	${IRR_EXT_RADEON_RAYS_LIB}
	${RADEON_RAYS_DEPENDENT_LIBS}
)

set(RAY_TRACED_AO_EXAMPLE_INCLUDE_DIRS
	${IRR_EXT_MITSUBA_LOADER_INCLUDE_DIRS}
	${IRR_EXT_RADEON_RAYS_INCLUDE_DIRS}
)

set(EXTRA_SOURCES
	../../ext/DebugDraw/CDraw3DLine.cpp
	./dirty_source/ExtraCrap.cpp
)

irr_create_executable_project(
	"${EXTRA_SOURCES}"
	""
	"${RAY_TRACED_AO_EXAMPLE_INCLUDE_DIRS}"
	"${RAY_TRACED_AO_EXAMPLE_LIBS}"
)