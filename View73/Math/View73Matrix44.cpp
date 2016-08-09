#include "View73Matrix44.h"
#include "View73Quaternion.h"

namespace
{
	inline static float MINOR(const View73::Matrix44& _m, short _r0, short _r1, short _r2, 
								short _c0, short _c1, short _c2)
    {
        return	_m[_r0][_c0] * ( _m[_r1][_c1] * _m[_r2][_c2] - _m[_r2][_c1] * _m[_r1][_c2] ) -
				_m[_r0][_c1] * ( _m[_r1][_c0] * _m[_r2][_c2] - _m[_r2][_c0] * _m[_r1][_c2] ) +
				_m[_r0][_c2] * ( _m[_r1][_c0] * _m[_r2][_c1] - _m[_r2][_c0] * _m[_r1][_c1] );
    }
}

namespace View73
{
    const Matrix44 Matrix44::ZERO(
									0, 0, 0, 0,
									0, 0, 0, 0,
									0, 0, 0, 0,
									0, 0, 0, 0 
								);

    const Matrix44 Matrix44::IDENTITY(
									1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									0, 0, 0, 1 
									);

    //-----------------------------------------------------------------------
    Matrix44 Matrix44::Adjoint() const
    {
        return Matrix44(	 MINOR(*this, 1, 2, 3, 1, 2, 3),
						-MINOR(*this, 0, 2, 3, 1, 2, 3),
						 MINOR(*this, 0, 1, 3, 1, 2, 3),
						-MINOR(*this, 0, 1, 2, 1, 2, 3),

						-MINOR(*this, 1, 2, 3, 0, 2, 3),
						 MINOR(*this, 0, 2, 3, 0, 2, 3),
						-MINOR(*this, 0, 1, 3, 0, 2, 3),
						 MINOR(*this, 0, 1, 2, 0, 2, 3),

						 MINOR(*this, 1, 2, 3, 0, 1, 3),
						-MINOR(*this, 0, 2, 3, 0, 1, 3),
						 MINOR(*this, 0, 1, 3, 0, 1, 3),
						-MINOR(*this, 0, 1, 2, 0, 1, 3),

						-MINOR(*this, 1, 2, 3, 0, 1, 2),
						 MINOR(*this, 0, 2, 3, 0, 1, 2),
						-MINOR(*this, 0, 1, 3, 0, 1, 2),
						 MINOR(*this, 0, 1, 2, 0, 1, 2));
    }
    //-----------------------------------------------------------------------
    float Matrix44::Determinant() const
    {
        return		m[0][0] * MINOR(*this, 1, 2, 3, 1, 2, 3) -
					m[0][1] * MINOR(*this, 1, 2, 3, 0, 2, 3) +
					m[0][2] * MINOR(*this, 1, 2, 3, 0, 1, 3) -
					m[0][3] * MINOR(*this, 1, 2, 3, 0, 1, 2);
    }

    //-----------------------------------------------------------------------

    Matrix44 Matrix44::GetInverse() const
    {
        Matrix44 mat(*this);
		mat.Inverse();
		return mat;
    }

	//-----------------------------------------------------------------------

	void Matrix44::Inverse()
	{
		float m00 = m[0][0],		m01 = m[0][1],		m02 = m[0][2],		m03 = m[0][3];
        float m10 = m[1][0],		m11 = m[1][1],		m12 = m[1][2],		m13 = m[1][3];
        float m20 = m[2][0],		m21 = m[2][1],		m22 = m[2][2],		m23 = m[2][3];
        float m30 = m[3][0],		m31 = m[3][1],		m32 = m[3][2],		m33 = m[3][3];

        float v0 = m20 * m31 - m21 * m30;
        float v1 = m20 * m32 - m22 * m30;
        float v2 = m20 * m33 - m23 * m30;
        float v3 = m21 * m32 - m22 * m31;
        float v4 = m21 * m33 - m23 * m31;
        float v5 = m22 * m33 - m23 * m32;

        float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
        float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
        float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
        float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

        float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

        float d00 = t00 * invDet;
        float d10 = t10 * invDet;
        float d20 = t20 * invDet;
        float d30 = t30 * invDet;

        float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;

        float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;

        float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		Set(d00, d01, d02, d03, d10, d11, d12, d13, d20, d21, d22, d23, d30, d31, d32, d33);
	}

    //-----------------------------------------------------------------------

    void Matrix44::MakeTransform(const Vector3& _position, const Quaternion& _orientation)
    {
        _orientation.ToRotationMatrix(*this);

        m[0][3] = _position.x;
        m[1][3] = _position.y;
        m[2][3] = _position.z;
    }

    //-----------------------------------------------------------------------

    void Matrix44::MakeInverseTransform(const Vector3& _position, const Quaternion& _orientation)
    {
        Vector3 invTranslate = -_position;
        Quaternion invRot = _orientation.Inverse();

        invTranslate = invRot * invTranslate; 

        Matrix44 rot;
        invRot.ToRotationMatrix(rot);

       m[0][3] = invTranslate.x;
       m[1][3] = invTranslate.y;
       m[2][3] = invTranslate.z;
    }

}
