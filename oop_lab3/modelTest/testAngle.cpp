#include "pch.h"
#include "CppUnitTest.h"
#include "../model/jangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Jora;

namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {
template<>
static std::wstring ToString<Angle>(const Angle& angle) {
    std::wstringstream sstr;
    sstr << angle << L'\0';
    return sstr.str();
}
}
}
}

namespace ModelTest {
TEST_CLASS(TestAngle) {
public:
    TEST_METHOD(TestConversion) {
        Angle a = Angle::fromDegrees(360);
        Angle b = Angle::fromRadians(2 * M_PI);
        Assert::AreEqual(a, b);
        Assert::AreEqual(Angle::fromDegrees(180), Angle::fromRadians(M_PI));
        Assert::AreEqual(Angle::fromDegrees(45), Angle::fromRadians(M_PI_4));
        Assert::AreEqual(Angle::fromDegrees(90), Angle::fromRadians(M_PI_2));
    }

    TEST_METHOD(TestOptimization) {
        Assert::AreEqual(20., Angle::optimizeDegrees(380.), 1e-10);
        Assert::AreEqual(200., Angle::optimizeDegrees(920.), 1e-10);
        Assert::AreEqual(150., Angle::optimizeDegrees(-210.), 1e-10);
        Assert::AreEqual(350., Angle::optimizeDegrees(-370.), 1e-10);

        Assert::AreEqual(200., Angle::fromDegrees(920.).degrees(), 1e-10);

        Assert::AreEqual(M_PI, Angle::optimizeRadians(7 * M_PI), 1e-10);
        Assert::AreEqual(M_PI_2, Angle::optimizeRadians(4 * M_PI + M_PI_2), 1e-10);
    }

    TEST_METHOD(TestTrigonometrical) {
        Angle a = Angle::fromDegrees(90);
        Assert::AreEqual(std::cos(M_PI_2), a.cos(), 1e-10);
        a.setDegrees(-45);
        Assert::AreEqual(std::cos(-M_PI_4), a.cos(), 1e-10);
        a = Angle::fromDegrees(90);
        Assert::AreEqual(std::sin(M_PI_2), a.sin(), 1e-10);
        a.setDegrees(-45);
        Assert::AreEqual(std::sin(-M_PI_4), a.sin(), 1e-10);
    }
};

}