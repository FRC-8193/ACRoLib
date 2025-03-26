add_library(acrolib
	${CMAKE_CURRENT_SOURCE_DIR}/cpp/impl/harness.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cpp/impl/motor.cpp
)

target_link_libraries(acrolib PUBLIC wpilibc)
target_include_directories(acrolib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/cpp/include)
