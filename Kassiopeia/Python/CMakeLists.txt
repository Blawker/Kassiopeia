# $Id$

set( KASSIOPEIA_PYTHON_SOURCES
	KassiopeiaReader.py
)

install(FILES ${KASSIOPEIA_PYTHON_SOURCES} DESTINATION ${${PROJECT_NAME}_LIB_INSTALL_DIR}/python)
