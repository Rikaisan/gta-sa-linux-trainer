# target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE
    main.cpp
    process.cpp
    util.cpp
)

add_subdirectory(cheats)