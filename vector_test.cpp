#include "vector.hpp"

#include "catch_amalgamated.hpp"
// #include <catch2/matchers/catch_matchers_floating_point.hpp>

using geometry::Vector;

// for comparing floating point values
static const double EPSILON = 0.00001;  // absolute difference
static const double MARGIN = 0.001;  // 0.1% relative difference


static void require_almost_equal(const Vector& actual, const Vector& expected) {
    REQUIRE_THAT(actual.x, Catch::Matchers::WithinRel(expected.x, MARGIN) ||
                           Catch::Matchers::WithinAbs(expected.x, EPSILON));
    REQUIRE_THAT(actual.y, Catch::Matchers::WithinRel(expected.y, MARGIN) ||
                           Catch::Matchers::WithinAbs(expected.y, EPSILON));
    REQUIRE_THAT(actual.z, Catch::Matchers::WithinRel(expected.z, MARGIN) ||
                           Catch::Matchers::WithinAbs(expected.z, EPSILON));
}


TEST_CASE("Vector constructors", "[constructors]") {
  const Vector v1;
  REQUIRE(v1.x == 0.0);
  REQUIRE(v1.y == 0.0);
  REQUIRE(v1.z == 0.0);

  const Vector v2{1, -2.55, 3};
  REQUIRE_THAT(v2.x, Catch::Matchers::WithinRel(1, MARGIN) ||
                     Catch::Matchers::WithinAbs(1, EPSILON));
  REQUIRE_THAT(v2.y, Catch::Matchers::WithinRel(-2.55, MARGIN) ||
                     Catch::Matchers::WithinAbs(-2.55, EPSILON));
  REQUIRE_THAT(v2.z, Catch::Matchers::WithinRel(3, MARGIN) ||
                     Catch::Matchers::WithinAbs(3, EPSILON));
}


TEST_CASE("Vector Addition", "[addition]") {
  const Vector a{1, 2, 3};
  const Vector b{4, 5, 6};
  const Vector v1{a + b};
  const Vector expected_v1{1+4, 2+5, 3+6};
  require_almost_equal(v1, expected_v1);

  const Vector v2{Vector{7.65, -3.4, 0.9} + Vector{-7.65, 3.8, 1.7}};
  const Vector expected_v2{0.0, 0.4, 2.6};
  require_almost_equal(v2, expected_v2);
}


TEST_CASE("Vector Subtraction", "[subtraction]") {
  Vector v1{Vector {1, 2, 3} - Vector {4, 5, 6}};
  Vector expected_v1{1-4, 2-5, 3-6};
  require_almost_equal(v1, expected_v1);

  Vector v2{Vector{7.65, -3.4, 0.9} - Vector{-7.65, 3.8, 1.7}};
  Vector expected_v2{15.3, -7.2, -0.8};
  require_almost_equal(v2, expected_v2);
}


TEST_CASE("Dot Product", "[dot]") {
  const Vector a{1, 2, 3};
  const Vector b{4, 5, 6};
  double ab_expected{32.0};

  const Vector c{7.65, -3.4, 0.9};
  const Vector d{-7.65, 3.8, 1.7};
  double cd_expected {7.65 * (-7.65) + (-3.4) * 3.8 + 0.9 * 1.7};

  SECTION("dot member") {
    REQUIRE_THAT(a.dot(b), Catch::Matchers::WithinRel(ab_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(ab_expected, EPSILON));
    REQUIRE_THAT(b.dot(a), Catch::Matchers::WithinRel(ab_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(ab_expected, EPSILON));
    REQUIRE_THAT(c.dot(d), Catch::Matchers::WithinRel(cd_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(cd_expected, EPSILON));
    REQUIRE_THAT(d.dot(c), Catch::Matchers::WithinRel(cd_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(cd_expected, EPSILON));
  }

  SECTION("dot operator (operator*)") {
    REQUIRE_THAT(a * b, Catch::Matchers::WithinRel(ab_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(ab_expected, EPSILON));
    REQUIRE_THAT(b * a, Catch::Matchers::WithinRel(ab_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(ab_expected, EPSILON));
    REQUIRE_THAT(c * d, Catch::Matchers::WithinRel(cd_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(cd_expected, EPSILON));
    REQUIRE_THAT(d * c, Catch::Matchers::WithinRel(cd_expected, MARGIN) ||
                           Catch::Matchers::WithinAbs(cd_expected, EPSILON));
  }
}


TEST_CASE("Vector * scalar", "[times_scalar]") {
  Vector v1{Vector {1, 2, 3} * 2.5};
  Vector expected_v1{2.5, 5.0, 7.5};
  require_almost_equal(v1, expected_v1);

  Vector v2{Vector{7.65, -3.4, 0.9} * 2.0};
  Vector expected_v2{15.3, -6.8, 1.8};
  require_almost_equal(v2, expected_v2);
}


TEST_CASE("Scalar * vector", "[scalar_times]") {
  Vector v1{2.5 * Vector {1, 2, 3}};
  Vector expected_v1{2.5, 5.0, 7.5};
  require_almost_equal(v1, expected_v1);

  Vector v2{2.0 * Vector{7.65, -3.4, 0.9}};
  Vector expected_v2{15.3, -6.8, 1.8};
  require_almost_equal(v2, expected_v2);
}


TEST_CASE("Cross Product", "[vector]") {
  Vector v1{Vector {1, 0, 0}.cross(Vector {0, 1, 0})};
  Vector expected_v1{0, 0, 1};
  require_almost_equal(v1, expected_v1);

  Vector v2{Vector{7.65, -3.4, 0.9}.cross(Vector {1, 1, 1})};
  Vector expected_v2{-3.4 - 0.9, 0.9 -7.65, 7.65 + 3.4};
  require_almost_equal(v2, expected_v2);
}


TEST_CASE("Length and Magnitude", "[length]") {
  const Vector v1{3, 4, 0};
  const Vector v2{1, 2, 2};
  double expected_v1{5.0};
  double expected_v2{3.0};

  SECTION(".length") {
    REQUIRE_THAT(v1.length(), Catch::Matchers::WithinRel(expected_v1, MARGIN) ||
                              Catch::Matchers::WithinAbs(expected_v1, EPSILON));
    REQUIRE_THAT(v2.length(), Catch::Matchers::WithinRel(expected_v2, MARGIN) ||
                              Catch::Matchers::WithinAbs(expected_v2, EPSILON));
  }

  SECTION(".magnitude") {
    REQUIRE_THAT(v1.magnitude(),
                 Catch::Matchers::WithinRel(expected_v1, MARGIN) ||
                 Catch::Matchers::WithinAbs(expected_v1, EPSILON));
    REQUIRE_THAT(v2.magnitude(),
                 Catch::Matchers::WithinRel(expected_v2, MARGIN) ||
                 Catch::Matchers::WithinAbs(expected_v2, EPSILON));
  }
}


TEST_CASE("Output Stream Operator", "[ostream]") {
    const Vector v(1, 2.5, -3.14);
    std::stringstream ss;
    ss << v;
    REQUIRE(ss.str() == "(1, 2.5, -3.14)");
}


TEST_CASE("Zero Vector Operations", "[zero]") {
  const Vector zero;
  const Vector a(1, 2, 3);

  const Vector sum{zero + a};
  require_almost_equal(sum, a);

  const Vector diff{a - zero};
  require_almost_equal(diff, a);

  const double dot = zero * a;
  REQUIRE_THAT(dot, Catch::Matchers::WithinRel(0, MARGIN) ||
                    Catch::Matchers::WithinAbs(0, EPSILON));

  const Vector cross = zero.cross(a);
  require_almost_equal(cross, zero);

  REQUIRE_THAT(zero.magnitude(), Catch::Matchers::WithinRel(0, MARGIN) ||
                                 Catch::Matchers::WithinAbs(0, EPSILON));
}


TEST_CASE("Parallel Vectors Cross Product", "[parallel]") {
  const Vector a{1, 2, 3};
  const Vector b{a * 2.0};  // b is parallel to a

  const Vector cross{a.cross(b)};
  REQUIRE_THAT(cross.magnitude(), Catch::Matchers::WithinRel(0, MARGIN) ||
                                  Catch::Matchers::WithinAbs(0, EPSILON));
}


TEST_CASE("Large Vector Operations", "[large]") {
  const Vector a{10000, 20000, 30000};
  const Vector b{40000, 50000, 60000};

  const Vector sum{a + b};
  const Vector expected_sum{50000, 70000, 90000};
  require_almost_equal(sum, expected_sum);

  double dot{a * b};
  const double expected(3200000000);
  REQUIRE_THAT(dot, Catch::Matchers::WithinRel(expected, MARGIN) ||
                    Catch::Matchers::WithinAbs(expected, EPSILON));
}

