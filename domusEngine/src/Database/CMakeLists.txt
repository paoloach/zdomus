cmake_minimum_required(VERSION 3.7)

project(domus_engine)

find_package(PostgreSQL)

SET(SRC_DATABASE
        Exceptions/DBException.h
        Exceptions/DBExceptionInvalidDataType.cpp Exceptions/DBExceptionInvalidDataType.h
        Exceptions/DBExceptionNoServer.cpp Exceptions/DBExceptionNoServer.h
        Exceptions/DBExceptionNoTable.cpp Exceptions/DBExceptionNoTable.h
        Exceptions/DBExceptionQueryError.cpp Exceptions/DBExceptionQueryError.h
        Exceptions/DBExceptionResultNotSet.cpp Exceptions/DBExceptionResultNotSet.h
        DBDataConverter.cpp DBDataConverter.h
        DBRow.cpp DBRow.h
        DBTable.cpp DBTable.h
        DBTableFactory.cpp DBTableFactory.h
        ResultSet.cpp ResultSet.h)


add_library(database_lib STATIC ${SRC_DATABASE} )
target_include_directories(database_lib PUBLIC ${PostgreSQL_INCLUDE_DIRS} )
target_link_libraries(database_lib PUBLIC ${PostgreSQL_LIBRARY})
