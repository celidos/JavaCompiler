add_executable(
    unit_tests
    example_add.cpp
    )

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
target_link_libraries(
    unit_tests
    gtest_main
    ast
    driver
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
