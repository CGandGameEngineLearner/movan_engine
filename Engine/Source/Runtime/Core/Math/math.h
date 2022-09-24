#pragma once

#include "random.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

#define CMP(x, y) (fabsf(x - y) < FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

namespace Movan
{
    static const float Math_POS_INFINITY = std::numeric_limits<float>::infinity();
    static const float Math_NEG_INFINITY = -std::numeric_limits<float>::infinity();
    static const float Math_PI = 3.14159265358979323846264338327950288f;
    static const float Math_ONE_OVER_PI = 1.0f / Math_PI;
    static const float Math_TWO_PI = 2.0f * Math_PI;
    static const float Math_HALF_PI = 0.5f * Math_PI;
    static const float Math_fDeg2Rad = Math_PI / 180.0f;
    static const float Math_fRad2Deg = 180.0f / Math_PI;
    static const float Math_LOG2 = log(2.0f);
    static const float Math_EPSILON = 1e-6f;

    static const float Float_EPSILON = FLT_EPSILON;
    static const float Double_EPSILON = DBL_EPSILON;

    class Radian;
    class Angle;
    class Degree;

    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix3x3;
    class Matrix4x4;
    class Quaternion;

    /* 弧度
    */
    class Radian
    {
        float rad_;

    public:
        explicit Radian(float r = 0) : rad_(r) {}
        explicit Radian(const Degree& d);
        Radian& operator=(float f)
        {
            rad_ = f;
            return *this;
        }
        Radian& operator=(const Degree& d);

        float valueRadians() const { return rad_; }
        float valueDegrees() const; // see bottom of this file
        float valueAngleUnits() const;

        void setValue(float f) { rad_ = f; }

        const Radian& operator+() const { return *this; }
        Radian        operator+(const Radian& r) const { return Radian(rad_ + r.rad_); }
        Radian        operator+(const Degree& d) const;
        Radian& operator+=(const Radian& r)
        {
            rad_ += r.rad_;
            return *this;
        }
        Radian& operator+=(const Degree& d);
        Radian  operator-() const { return Radian(-rad_); }
        Radian  operator-(const Radian& r) const { return Radian(rad_ - r.rad_); }
        Radian  operator-(const Degree& d) const;
        Radian& operator-=(const Radian& r)
        {
            rad_ -= r.rad_;
            return *this;
        }
        Radian& operator-=(const Degree& d);
        Radian  operator*(float f) const { return Radian(rad_ * f); }
        Radian  operator*(const Radian& f) const { return Radian(rad_ * f.rad_); }
        Radian& operator*=(float f)
        {
            rad_ *= f;
            return *this;
        }
        Radian  operator/(float f) const { return Radian(rad_ / f); }
        Radian& operator/=(float f)
        {
            rad_ /= f;
            return *this;
        }

        bool operator<(const Radian& r) const { return rad_ < r.rad_; }
        bool operator<=(const Radian& r) const { return rad_ <= r.rad_; }
        bool operator==(const Radian& r) const { return rad_ == r.rad_; }
        bool operator!=(const Radian& r) const { return rad_ != r.rad_; }
        bool operator>=(const Radian& r) const { return rad_ >= r.rad_; }
        bool operator>(const Radian& r) const { return rad_ > r.rad_; }

        void print()
        {
            std::cout << "rad:" << rad_ << std::endl;
        }
    };

    /*角度 Wrapper class which indicates a given angle value is in Degrees.
    @remarks
        Degree values are interchangeable with Radian values, and conversions
        will be done automatically between them.
    */
    class Degree
    {
        float deg_; //如果这里报错了，请用在前面 define/typedef 'float'| if you get an error here - make sure to define/typedef 'float' first

    public:
        explicit Degree(float d = 0) : deg_(d) {}
        explicit Degree(const Radian& r) : deg_(r.valueDegrees()) {}
        Degree& operator=(float f)
        {
            deg_ = f;
            return *this;
        }
        Degree& operator=(const Degree& d) = default;
        Degree& operator=(const Radian& r)
        {
            deg_ = r.valueDegrees();
            return *this;
        }

        float valueDegrees() const { return deg_; }
        float valueRadians() const; // see bottom of this file
        float valueAngleUnits() const;

        const Degree& operator+() const { return *this; }
        Degree        operator+(const Degree& d) const { return Degree(deg_ + d.deg_); }
        Degree        operator+(const Radian& r) const { return Degree(deg_ + r.valueDegrees()); }
        Degree& operator+=(const Degree& d)
        {
            deg_ += d.deg_;
            return *this;
        }
        Degree& operator+=(const Radian& r)
        {
            deg_ += r.valueDegrees();
            return *this;
        }
        Degree  operator-() const { return Degree(-deg_); }
        Degree  operator-(const Degree& d) const { return Degree(deg_ - d.deg_); }
        Degree  operator-(const Radian& r) const { return Degree(deg_ - r.valueDegrees()); }
        Degree& operator-=(const Degree& d)
        {
            deg_ -= d.deg_;
            return *this;
        }
        Degree& operator-=(const Radian& r)
        {
            deg_ -= r.valueDegrees();
            return *this;
        }
        Degree  operator*(float f) const { return Degree(deg_ * f); }
        Degree  operator*(const Degree& f) const { return Degree(deg_ * f.deg_); }
        Degree& operator*=(float f)
        {
            deg_ *= f;
            return *this;
        }
        Degree  operator/(float f) const { return Degree(deg_ / f); }
        Degree& operator/=(float f)
        {
            deg_ /= f;
            return *this;
        }

        bool operator<(const Degree& d) const { return deg_ < d.deg_; }
        bool operator<=(const Degree& d) const { return deg_ <= d.deg_; }
        bool operator==(const Degree& d) const { return deg_ == d.deg_; }
        bool operator!=(const Degree& d) const { return deg_ != d.deg_; }
        bool operator>=(const Degree& d) const { return deg_ >= d.deg_; }
        bool operator>(const Degree& d) const { return deg_ > d.deg_; }

        void print()
        {
            std::cout << "deg:" << deg_ << std::endl;
        }
    };

    /** 角度Wrapper class which identifies a value as the currently default angle
        type, as defined by Math::setAngleUnit.
    @remarks
        Angle values will be automatically converted between m_radians and degrees,
        as appropriate.
    */
    class Angle
    {
        float ang_;

    public:
        explicit Angle(float angle) : ang_(angle) {}
        Angle() { ang_ = 0; }

        explicit operator Radian() const;
        explicit operator Degree() const;

        void print()
        {
            std::cout<<"ang:"<<ang_ << std::endl;
        }
    };

    class Math
    {
    private:
        enum class AngleUnit
        {
            AU_DEGREE,//角度制
            AU_RADIAN//弧度制
        };

        // angle units used by the api
        static AngleUnit k_AngleUnit;//用于表示当前使用的是角度制还是弧度制，如果是AU_DEGREE则为角度制度，AU_RADIAN为弧度制||Used to indicate whether the angle or radian system is currently in use, if it is AU_DEGREE the angle system, AU_RADIAN is the radian system

    public:
        Math();

        static float abs(float value) { return std::fabs(value); }
        static bool  isNan(float f) { return std::isnan(f); }
        static float sqr(float value) { return value * value; }
        static float sqrt(float fValue) { return std::sqrt(fValue); }
        static float invSqrt(float value) { return 1.f / sqrt(value); }
        static bool  realEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon());//在允许的一定范围（ tolerance）内认定a和b相等|Determining that a and b are equal within tolerance.
        static float clamp(float v, float min, float max);
        static float getMaxElement(float x, float y, float z) { return std::max({ x, y, z }); }

        static float degreesToRadians(float degrees);
        static float radiansToDegrees(float m_radians);
        static float angleUnitsToRadians(float units);
        static float radiansToAngleUnits(float m_radians);
        static float angleUnitsToDegrees(float units);
        static float degreesToAngleUnits(float degrees);

        static float  sin(const Radian& m_rad) { return std::sin(m_rad.valueRadians()); }
        static float  sin(float value) { return std::sin(value); }
        static float  cos(const Radian& m_rad) { return std::cos(m_rad.valueRadians()); }
        static float  cos(float value) { return std::cos(value); }
        static float  tan(const Radian& m_rad) { return std::tan(m_rad.valueRadians()); }
        static float  tan(float value) { return std::tan(value); }
        static Radian acos(float value);
        static Radian asin(float value);
        static Radian atan(float value) { return Radian(std::atan(value)); }
        static Radian atan2(float y_v, float x_v) { return Radian(std::atan2(y_v, x_v)); }


        template<class T>
        static constexpr T max(const T A, const T B)
        {
            return std::max(A, B);
        }

        template<class T>
        static constexpr T min(const T A, const T B)
        {
            return std::min(A, B);
        }

        template<class T>
        static constexpr T max3(const T A, const T B, const T C)
        {
            return std::max({ A, B, C });
        }

        template<class T>
        static constexpr T min3(const T A, const T B, const T C)
        {
            return std::min({ A, B, C });
        }

        static Matrix4x4
            makeViewMatrix(const Vector3& position, const Quaternion& orientation, const Matrix4x4* reflect_matrix = nullptr);

        static Matrix4x4
            makeLookAtMatrix(const Vector3& eye_position, const Vector3& target_position, const Vector3& up_dir);

        static Matrix4x4 makePerspectiveMatrix(Radian fovy, float aspect, float znear, float zfar);

        static Matrix4x4
            makeOrthographicProjectionMatrix(float left, float right, float bottom, float top, float znear, float zfar);

        
    };

    // these functions could not be defined within the class definition of class
    // Radian because they required class Degree to be defined
    inline Radian::Radian(const Degree& d) : rad_(d.valueRadians()) {}
    inline Radian& Radian::operator=(const Degree& d)
    {
        rad_ = d.valueRadians();
        return *this;
    }
    inline Radian Radian::operator+(const Degree& d) const { return Radian(rad_ + d.valueRadians()); }
    inline Radian& Radian::operator+=(const Degree& d)
    {
        rad_ += d.valueRadians();
        return *this;
    }
    inline Radian Radian::operator-(const Degree& d) const { return Radian(rad_ - d.valueRadians()); }
    inline Radian& Radian::operator-=(const Degree& d)
    {
        rad_ -= d.valueRadians();
        return *this;
    }

    inline float Radian::valueDegrees() const { return Math::radiansToDegrees(rad_); }

    inline float Radian::valueAngleUnits() const { return Math::radiansToAngleUnits(rad_); }

    inline float Degree::valueRadians() const { return Math::degreesToRadians(deg_); }

    inline float Degree::valueAngleUnits() const { return Math::degreesToAngleUnits(deg_); }

    inline Angle::operator Radian() const { return Radian(Math::angleUnitsToRadians(ang_)); }

    inline Angle::operator Degree() const { return Degree(Math::angleUnitsToDegrees(ang_)); }

    inline Radian operator*(float a, const Radian& b) { return Radian(a * b.valueRadians()); }

    inline Radian operator/(float a, const Radian& b) { return Radian(a / b.valueRadians()); }

    inline Degree operator*(float a, const Degree& b) { return Degree(a * b.valueDegrees()); }

    inline Degree operator/(float a, const Degree& b) { return Degree(a / b.valueDegrees()); }
} // namespace Movan
