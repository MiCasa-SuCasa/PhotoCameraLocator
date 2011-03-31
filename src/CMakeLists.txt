SUBDIRS( ui )

IF (WIN32)
  IF (MSVC)
    ADD_DEFINITIONS("-DMS_DLL_SPEC=__declspec(dllexport)")
	ADD_DEFINITIONS("-D_USE_MATH_DEFINES")
  ELSE (MSVC)
    ADD_DEFINITIONS("-UMS_DLL_SPEC \"-DMS_DLL_SPEC=__declspec(dllexport)\"")
  ENDIF (MSVC)
ENDIF (WIN32)

SET( PCL_INSTALL_HDRS
     app/pclapplication.h

     core/pclcalculationengine.h
   )

SET( PCL_CORE_SRCS
     core/pclcalculationengine.cpp
   )

SET( PCL_CORE_MOC_HDRS
   )

SET( PCL_APP_SRCS
    app/pclapplication.cpp
    app/pclmainwindow.cpp
    app/pclflagitem.cpp
    app/pclphotoscene.cpp

   )

SET( PCL_APP_MOC_HDRS
    app/pclapplication.h
    app/pclmainwindow.h
    app/pclphotoscene.h
   )



SET (PCL_APP_RCCS app/app.qrc)

QT4_AUTOMOC( ${PCL_CORE_SRCS} ${PCL_APP_SRCS} )

QT4_WRAP_CPP( PCL_APP_MOC_SRCS ${PCL_APP_MOC_HDRS} )
QT4_WRAP_CPP( PCL_CORE_MOC_SRCS ${PCL_CORE_MOC_HDRS} )
QT4_WRAP_CPP( PCL_PYTHON_MOC_SRCS ${PCL_PYTHON_MOC_HDRS} )

QT4_ADD_RESOURCES( PCL_APP_RCCS_SRCS ${PCL_APP_RCCS} )


ADD_LIBRARY ( photocl SHARED ${PCL_CORE_SRCS} ${PCL_CORE_MOC_SRCS} ${PCL_APP_SRCS} ${PCL_APP_MOC_SRCS} ${PCL_APP_RCCS_SRCS} )

ADD_DEPENDENCIES( photocl photocl_ui )

TARGET_LINK_LIBRARIES( photocl
  ${QT_LIBRARIES}
  )

INSTALL( FILES ${PCL_INSTALL_HDRS} DESTINATION ${PHOTOCL_INCLUDE_SUBDIR})
INSTALL( TARGETS photocl DESTINATION ${PHOTOCL_LIB_SUBDIR} )
