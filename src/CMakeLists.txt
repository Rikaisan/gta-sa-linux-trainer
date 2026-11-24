# target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    locations.cpp
    main.cpp
    process.cpp
    util.cpp
)