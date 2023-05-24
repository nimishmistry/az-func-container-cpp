find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)

# set the project name
set(PROJECT_NAME ExampleService)

project(${PROJECT_NAME})

file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${Sources})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${oatpp_INCLUDE_DIRS}
    ${oatpp-swagger_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PUBLIC
    ${oatpp_LIBRARIES_DIRS}
    ${oatpp-swagger_LIBRARIES_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    oatpp::oatpp
    oatpp::oatpp-swagger
)

add_definitions(-DOATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/external/oatpp/res")

file(COPY ${OATPP_BASE_DIR}/bin/oatpp-swagger/res DESTINATION ${CMAKE_BINARY_DIR}/external/oatpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../Dockerfile DESTINATION ${CMAKE_BINARY_DIR})

