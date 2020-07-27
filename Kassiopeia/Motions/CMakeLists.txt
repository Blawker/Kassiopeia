# header files
set( MOTION_HEADER_BASENAMES
    KSMotionsMessage.h

    KSMotionSurfaceTranslation.h
)
set( MOTION_HEADER_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/Include
)
foreach( BASENAME ${MOTION_HEADER_BASENAMES} )
	list( APPEND MOTION_HEADER_FILENAMES ${MOTION_HEADER_PATH}/${BASENAME} )
endforeach( BASENAME )

# source files
set( MOTION_SOURCE_BASENAMES
    KSMotionsMessage.cxx

    KSMotionSurfaceTranslation.cxx
)
set( MOTION_SOURCE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/Source
)
foreach( BASENAME ${MOTION_SOURCE_BASENAMES} )
	list( APPEND MOTION_SOURCE_FILENAMES ${MOTION_SOURCE_PATH}/${BASENAME} )
endforeach( BASENAME )

# library
kasper_internal_include_directories( ${MOTION_HEADER_PATH} )
add_library( KassiopeiaMotions SHARED ${MOTION_SOURCE_FILENAMES} )
set_target_properties( KassiopeiaMotions PROPERTIES COMPILE_FLAGS -Wno-overloaded-virtual )
target_link_libraries( KassiopeiaMotions
    ${Kommon_LIBRARIES}
    ${KGeoBag_LIBRARIES}
    KassiopeiaUtility
    KassiopeiaObjects
    KassiopeiaOperators
)

# install
kasper_install_headers( ${MOTION_HEADER_FILENAMES} )
kasper_install_data( ${MOTION_DATA_FILENAMES} )
kasper_install_libraries( KassiopeiaMotions )
