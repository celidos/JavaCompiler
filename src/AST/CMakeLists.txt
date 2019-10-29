add_library(AST STATIC Expression/ExpressionBase.h Expression/ExpressionBase.cpp Expression/ExpressionBinaryOp.h Expression/ExpressionBinaryOp.cpp Expression/ExpressionInt.h Expression/ExpressionInt.cpp)

target_include_directories(AST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::AST ALIAS AST)
