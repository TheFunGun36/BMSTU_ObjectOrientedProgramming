#include "pch.h"
#include "CppUnitTest.h"
#include "../model/jvector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Jora;

namespace Microsoft {
namespace VisualStudio {
namespace CppUnitTestFramework {
template<>
static std::wstring ToString<Vector3D>(const Vector3D& coords) {
    return coords.toWString();
}
}
}
}

namespace ModelTest {
TEST_CLASS(TestCoords3D) {
public:

    TEST_METHOD(TestInitialization) {
        auto m1 = L"Vector3D()";
        Vector3D coordsEmpty;
        Assert::AreEqual(coordsEmpty.x(), 0., m1);
        Assert::AreEqual(coordsEmpty.y(), 0., m1);
        Assert::AreEqual(coordsEmpty.z(), 0., m1);

        auto m2 = L"Vector3D(int, int, int)";
        Vector3D coordsInitialized = { 1, 2, 3 };
        Assert::AreEqual(coordsInitialized.x(), 1., m2);
        Assert::AreEqual(coordsInitialized.y(), 2., m2);
        Assert::AreEqual(coordsInitialized.z(), 3., m2);

        auto m3 = L"Vector3D(Vector3D)";
        Vector3D coordsCopied(coordsInitialized);
        Assert::AreEqual(coordsCopied.x(), 1., m3);
        Assert::AreEqual(coordsCopied.y(), 2., m3);
        Assert::AreEqual(coordsCopied.z(), 3., m3);

        auto m4 = L"operator=(Vector3D)";
        coordsInitialized = { 4, 5, 6 };
        Assert::AreEqual(coordsInitialized.x(), 4., m4);
        Assert::AreEqual(coordsInitialized.y(), 5., m4);
        Assert::AreEqual(coordsInitialized.z(), 6., m4);

        coordsCopied = coordsInitialized;
        Assert::AreEqual(coordsCopied.x(), 4., m4);
        Assert::AreEqual(coordsCopied.y(), 5., m4);
        Assert::AreEqual(coordsCopied.z(), 6., m4);

        auto m5 = L"set?(real)";
        coordsInitialized.setX(12).setY(4).setZ(-15.5);
        Assert::AreEqual(coordsInitialized.x(), 12., m5);
        Assert::AreEqual(coordsInitialized.y(), 4., m5);
        Assert::AreEqual(coordsInitialized.z(), -15.5, m5);
    }

    TEST_METHOD(TestArithmetic) {
        Assert::IsFalse(bool(Vector3D()), L"operator bool");
        Assert::IsTrue(bool(Vector3D(0, -0.1)), L"operator bool");

        Vector3D c1(1, 2.5, 3);
        Vector3D c2(-1, 4, -1);
        Assert::IsFalse(c1 == c2, L"operator==(Vector3D)");
        Assert::IsTrue(c1 != c2, L"opeartor!=(Vector3D)");
        Assert::IsTrue(c2 == Vector3D(-1, 4, -1), L"operator==(Vector3D)");
        Assert::IsFalse(c2 != Vector3D(-1, 4, -1), L"operator !=");

        Assert::AreEqual(Vector3D(0, 6.5, 2), c1 += c2, L"operator+=(Vector3D)");
        Assert::AreEqual(Vector3D(2.2, 8.7, 4.2), c1 += 2.2, L"operator+=(real)");
        Assert::AreEqual(Vector3D(3.2, 4.7, 5.2), c1 -= c2, L"operator-=(Vector3D)");
        Assert::AreEqual(Vector3D(-0.9, 0.6, 1.1), c1 -= 4.1, L"operator-=(real)");
        Assert::AreEqual(Vector3D(-1.35, 0.9, 1.65), c1 *= 1.5, L"operator*=(real)");
        Assert::AreEqual(Vector3D(-0.9, 0.6, 1.1), c1 /= 1.5, L"operator/=(real)");
        Assert::AreEqual(Vector3D(), c1 *= 0., L"operator*=(0)");

        Assert::AreEqual(Vector3D(2.5, -5, 26.5), Vector3D(1.5, -6, 10) + Vector3D(1, 1, 16.5), L"operator+(Vector3D)");
        Assert::AreEqual(Vector3D(4.5, -3, 13), Vector3D(1.5, -6, 10) + 3., L"operator+(real)");
        Assert::AreEqual(Vector3D(2.5, -5, 26.5), Vector3D(1.5, -6, 10) - Vector3D(-1, -1, -16.5), L"operator-(Vector3D)");
        Assert::AreEqual(Vector3D(-1.5, -9, 7), Vector3D(1.5, -6, 10) - 3., L"operator+(real)");
        Assert::AreEqual(Vector3D(2, -1.5, 0.5), Vector3D(1, -0.75, 0.25) * 2., L"operator+(real)");
        Assert::AreEqual(Vector3D(2, -1.5, 0.5), Vector3D(4, -3, 1) / 2., L"operator/(real)");
        Assert::AreEqual(Vector3D(2, -15, 0.5), -Vector3D(-2, 15, -0.5), L"operator-()");
    }

    TEST_METHOD(TestAccess) {
        Vector3D c(1., 2., 3.);
        auto m = L"operator[]";
        Assert::AreEqual(1., c[0], m);
        Assert::AreEqual(2., c[1], m);
        Assert::AreEqual(3., c[2], m);
        Assert::ExpectException<CoordsOutOfRange>([]() { Vector3D(1, 2, 3)[-1]; }, m);
        Assert::ExpectException<CoordsOutOfRange>([]() { Vector3D(1, 2, 3)[4]; }, m);
        Assert::ExpectException<CoordsOutOfRange>([]() { Vector3D(1, 2, 3)[2549]; }, m);

        Assert::AreEqual(1., c.x(), L"x()");
        Assert::AreEqual(2., c.y(), L"y()");
        Assert::AreEqual(3., c.z(), L"z()");

        const Vector3D cc(1., 2., 3.);
        Assert::AreEqual(1., cc.x(), L"x() const");
        Assert::AreEqual(2., cc.y(), L"y() const");
        Assert::AreEqual(3., cc.z(), L"z() const");

        size_t idx = 2;
        Assert::AreEqual(size_t(0), idx = Vector3D::indexCycleForward(idx));
        Assert::AreEqual(size_t(1), idx = Vector3D::indexCycleForward(idx));
        Assert::AreEqual(size_t(2), idx = Vector3D::indexCycleForward(idx));

        Assert::AreEqual(size_t(1), idx = Vector3D::indexCycleBackward(idx));
        Assert::AreEqual(size_t(0), idx = Vector3D::indexCycleBackward(idx));
        Assert::AreEqual(size_t(2), idx = Vector3D::indexCycleBackward(idx));
    }
};
}
