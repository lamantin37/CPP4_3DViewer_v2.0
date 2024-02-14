#include <gtest/gtest.h>

#include "./backend/s21_auxiliary_modules.h"

TEST(test_parser1, True) {
  std::ifstream file("models/teapot.obj");
  s21::Object object;
  s21::AuxiliaryModules auxiliary_modules;
  ASSERT_TRUE(file.is_open());
  auxiliary_modules.ParserCounter(file, object);
  auxiliary_modules.ObjectParser(file, object);
  EXPECT_EQ(object.num_of_vertices, 3644);
  EXPECT_EQ(object.num_of_polygons, 6320);
}

TEST(test_parser2, True) {
  std::ifstream file("models/capybara.obj");
  s21::Object object;
  s21::AuxiliaryModules auxiliary_modules;
  ASSERT_TRUE(file.is_open());
  auxiliary_modules.ParserCounter(file, object);
  auxiliary_modules.ObjectParser(file, object);
  EXPECT_EQ(object.num_of_vertices, 7116);
  EXPECT_EQ(object.num_of_polygons, 7114);
}

TEST(test_parser3, True) {
  std::ifstream file("models/apple.obj");
  s21::Object object;
  s21::AuxiliaryModules auxiliary_modules;
  ASSERT_TRUE(file.is_open());
  auxiliary_modules.ParserCounter(file, object);
  auxiliary_modules.ObjectParser(file, object);
  EXPECT_EQ(object.num_of_vertices, 476);
  EXPECT_EQ(object.num_of_polygons, 492);
}

TEST(test_parser4, True) {
  std::ifstream file("models/empty.obj");
  s21::Object object;
  s21::AuxiliaryModules auxiliary_modules;
  ASSERT_TRUE(file.is_open());
  auxiliary_modules.ParserCounter(file, object);
  auxiliary_modules.ObjectParser(file, object);
  EXPECT_EQ(object.num_of_vertices, 1);
  EXPECT_EQ(object.num_of_polygons, 1);
}

TEST(test_parser5, True) {
  std::ifstream file("models/minicooper.obj");
  s21::Object object;
  s21::AuxiliaryModules auxiliary_modules;
  ASSERT_TRUE(file.is_open());
  auxiliary_modules.ParserCounter(file, object);
  auxiliary_modules.ObjectParser(file, object);
  EXPECT_EQ(object.num_of_vertices, 44436);
  EXPECT_EQ(object.num_of_polygons, 79759);
}

TEST(test_move1, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::MoveStrategy move_strategy;
  auxiliary_modules.SetStrategy(&move_strategy);
  cur_point(0, 0) = 1;
  cur_point(1, 0) = 2;
  cur_point(2, 0) = 3;
  cur_point(3, 0) = 4;
  auxiliary_modules.ExecuteStrategy(0.6, -51, 75, cur_point, result);
  EXPECT_NEAR(result(0, 0), 3.4, 1e-6);
  EXPECT_EQ(result(1, 0), -202);
}

TEST(test_move2, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::MoveStrategy move_strategy;
  auxiliary_modules.SetStrategy(&move_strategy);
  cur_point(0, 0) = -1.1;
  cur_point(1, 0) = -2.2;
  cur_point(2, 0) = -3.3;
  cur_point(3, 0) = -4.4;
  auxiliary_modules.ExecuteStrategy(0, 0, 0, cur_point, result);
  EXPECT_NEAR(result(0, 0), -1.1, 1e-6);
  EXPECT_NEAR(result(1, 0), -2.2, 1e-6);
  EXPECT_NEAR(result(2, 0), -3.3, 1e-6);
  EXPECT_NEAR(result(3, 0), -4.4, 1e-6);
}

TEST(test_rotate1, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::RotateStrategy rotate_strategy;
  auxiliary_modules.SetStrategy(&rotate_strategy);
  cur_point(0, 0) = -1.1;
  cur_point(1, 0) = -2.2;
  cur_point(2, 0) = -3.3;
  cur_point(3, 0) = -4.4;
  auxiliary_modules.ExecuteStrategy(70, 0, 0, cur_point, result);
  EXPECT_NEAR(result(0, 0), -1.1, 1e-6);
  EXPECT_NEAR(result(1, 0), 1.1605352, 1e-4);
  EXPECT_NEAR(result(2, 0), -3.7925129, 1e-6);
  EXPECT_NEAR(result(3, 0), -4.4, 1e-6);
}

TEST(test_rotate2, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::RotateStrategy rotate_strategy;
  auxiliary_modules.SetStrategy(&rotate_strategy);
  cur_point(0, 0) = 1111;
  cur_point(1, 0) = 222;
  cur_point(2, 0) = 33;
  cur_point(3, 0) = 4;
  auxiliary_modules.ExecuteStrategy(0, 0.5, 0, cur_point, result);
  EXPECT_NEAR(result(0, 0), 990.815, 1e-3);
  EXPECT_NEAR(result(1, 0), 222, 1e-6);
  EXPECT_NEAR(result(2, 0), -503.682, 1e-3);
  EXPECT_EQ(result(3, 0), 4);
}

TEST(test_rotate3, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::RotateStrategy rotate_strategy;
  auxiliary_modules.SetStrategy(&rotate_strategy);
  cur_point(0, 0) = 0;
  cur_point(1, 0) = 777;
  cur_point(2, 0) = 22;
  cur_point(3, 0) = 0;
  auxiliary_modules.ExecuteStrategy(0, 0, -110, cur_point, result);
  EXPECT_NEAR(result(0, 0), -34.3766, 1e-4);
  EXPECT_NEAR(result(1, 0), -776.23854, 1e-3);
  EXPECT_NEAR(result(2, 0), 22, 1e-6);
  EXPECT_NEAR(result(3, 0), 0, 1e-6);
}

TEST(test_scale1, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::ScaleStrategy scale_strategy;
  auxiliary_modules.SetStrategy(&scale_strategy);
  cur_point(0, 0) = 345;
  cur_point(1, 0) = -532;
  cur_point(2, 0) = 0.05;
  cur_point(3, 0) = 1;
  auxiliary_modules.ExecuteStrategy(-20, -40.4, -60.06, cur_point, result);
  EXPECT_NEAR(result(0, 0), -6900, 1e-6);
  EXPECT_NEAR(result(1, 0), 21492.8, 1e-1);
  EXPECT_NEAR(result(2, 0), -3.003, 1e-6);
  EXPECT_NEAR(result(3, 0), 1, 1e-6);
}

TEST(test_scale2, True) {
  S21Matrix cur_point(4, 1), result;
  s21::AuxiliaryModules auxiliary_modules;
  s21::ScaleStrategy scale_strategy;
  auxiliary_modules.SetStrategy(&scale_strategy);
  cur_point(0, 0) = 345;
  cur_point(1, 0) = -532;
  cur_point(2, 0) = 0.05;
  cur_point(3, 0) = 1;
  auxiliary_modules.ExecuteStrategy(20, 40.4, 60.06, cur_point, result);
  EXPECT_NEAR(result(0, 0), 6900, 1e-6);
  EXPECT_NEAR(result(1, 0), -21492.8, 1e-1);
  EXPECT_NEAR(result(2, 0), 3.003, 1e-6);
  EXPECT_NEAR(result(3, 0), 1, 1e-6);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
