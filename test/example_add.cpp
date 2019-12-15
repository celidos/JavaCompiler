#include "gtest/gtest.h"
#include <src/mc_driver.hpp>

TEST(return_five, return_five)
{
    MC::MC_Driver driver;
    ASSERT_NEAR(driver.__return_five(), 5.0, 1.0e-11);
}
