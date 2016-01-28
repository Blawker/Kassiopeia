# attention:
# i spent some time making this file neat and organized.
# this is important as it allows changes to be performed quickly.
# please be considerate and make additions as neatly as you can.
# thank you! -dan.

cmake_minimum_required( VERSION 2.8.6 )

project( Kassiopeia )
include( KasperDefaults )

if(POLICY CMP0053)
    cmake_policy(SET CMP0053 OLD)
endif()

# module version
set( MODULE_VERSION_MAJOR 3 )
set( MODULE_VERSION_MINOR 1 )
set( MODULE_VERSION_PATCH 0 )
set( MODULE_VERSION "${MODULE_VERSION_MAJOR}.${MODULE_VERSION_MINOR}.${MODULE_VERSION_PATCH}" )

# module options
option( Kassiopeia_USE_ROOT "build in root functionality [writers, visualization]" ON )
option( Kassiopeia_USE_VTK "build in vtk functionality [visualization]" OFF )

# module paths
kasper_module_paths( Kassiopeia )

# module debugging
kasper_module_debug()
if( Kassiopeia_ENABLE_DEBUG )
	add_cflag( Kassiopeia_ENABLE_DEBUG )
endif()


# external dependencies: root
if( Kassiopeia_USE_ROOT )
	set( Kommon_USE_ROOT ON CACHE BOOL "(Required)" FORCE )
	find_package( ROOT 5.24.0 REQUIRED )
	kasper_external_include_directories( ${ROOT_INCLUDE_DIRS} )
	add_cflag( Kassiopeia_USE_ROOT )
endif( Kassiopeia_USE_ROOT )

# external dependencies: vtk
if( Kassiopeia_USE_VTK )
	kasper_find_vtk()
	add_cflag( Kassiopeia_USE_VTK )
endif( Kassiopeia_USE_VTK )


# internal dependencies: kommon
kasper_find_module( Kommon )
foreach( FLAG ${Kommon_CFLAGS} )
	add_definitions( -D${FLAG} )
endforeach( FLAG )

# internal dependencies: kgeobag
kasper_find_module( KGeoBag )
foreach( FLAG ${KGeoBag_CFLAGS} )
	add_definitions( -D${FLAG} )
endforeach( FLAG )

# # internal dependencies: kemfield
kasper_find_module( KEMField )
foreach( FLAG ${KEMField_CFLAGS} )
   add_definitions( -D${FLAG} )
   if( ${FLAG} STREQUAL KEMFIELD_USE_MPI )
        find_package(MPI)
        if (MPI_FOUND)
            include_directories(${MPI_INCLUDE_PATH})
        endif (MPI_FOUND)
    endif( ${FLAG} STREQUAL KEMFIELD_USE_MPI )
 endforeach( FLAG )

if (KEMField_USE_MPI)
  find_package(MPI)
  if (MPI_FOUND)
    if (MPI_COMPILER)  # MPICH2 style
      set (CMAKE_C_COMPILER ${MPI_COMPILER})
      set (CMAKE_CXX_COMPILER ${MPI_COMPILER})
    else (MPI_COMPILER)  # OpenMPI style
      set (CMAKE_C_COMPILER ${MPI_C_COMPILER})
      set (CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
    endif (MPI_COMPILER)
  else (MPI_FOUND)
    set (CMAKE_C_COMPILER mpicc)
    set (CMAKE_CXX_COMPILER mpicxx)
  endif (MPI_FOUND)
  set (STATIC_LIBRARY_SUFFIX _mpi)
  set (SHARED_LIBRARY_SUFFIX _mpi)
  set (CMAKE_STATIC_LIBRARY_SUFFIX ${STATIC_LIBRARY_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
  set (CMAKE_SHARED_LIBRARY_SUFFIX ${SHARED_LIBRARY_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX})
  set (CMAKE_EXECUTABLE_SUFFIX ${SHARED_LIBRARY_SUFFIX}${CMAKE_EXECUTABLE_SUFFIX})
  set (CMAKE_EXECUTABLE_SUFFIX ${CMAKE_EXECUTABLE_SUFFIX} PARENT_SCOPE)
endif (KEMField_USE_MPI)


# subdirectories
add_subdirectory( Documentation )
add_subdirectory( Utility )
add_subdirectory( Math )
add_subdirectory( Objects )
add_subdirectory( Operators )
add_subdirectory( Fields )
add_subdirectory( Geometry )
add_subdirectory( Generators )
add_subdirectory( Trajectories )
add_subdirectory( Navigators )
add_subdirectory( Interactions )
add_subdirectory( Terminators )
add_subdirectory( Modifiers )
add_subdirectory( Writers )
add_subdirectory( Simulation )
add_subdirectory( Readers )
add_subdirectory( XML )
add_subdirectory( Visualization )
add_subdirectory( Bindings )
add_subdirectory( Applications/Simulation )


add_subdirectory( Applications/Validation )
if( Kassiopeia_USE_ROOT )
	add_subdirectory( Applications/Examples )
	add_subdirectory( Applications/Other )
endif( Kassiopeia_USE_ROOT )

kasper_install_module()