#include "View73Quaternion.h"
#include "View73Matrix44.h"

namespace View73
{
    const Quaternion Quaternion::ZERO(0.0,0.0,0.0,0.0);
    const Quaternion Quaternion::IDENTITY(1.0,0.0,0.0,0.0);

	//-----------------------------------------------------------------------
    Vector3 Quaternion::operator * (const Vector3& _right) const
    {
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = qvec.Cross(_right);
		uuv = qvec.Cross(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return _right + uv + uuv;

    }

    //-----------------------------------------------------------------------
    void Quaternion::FromAngleAxis (float _angle, const Vector3& _axis)
    {
        // The quaternion representing the rotation is
        // q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

        float halfAngle ( 0.5f * _angle );
        float fSin = sin(halfAngle);
        w = cos(halfAngle);
        x = fSin * _axis.x;
        y = fSin * _axis.y;
        z = fSin * _axis.z;
    }
 
    //-----------------------------------------------------------------------
    Quaternion Quaternion::Inverse () const
    {
        float sqrdLen = w * w + x * x + y * y + z * z;

        if ( sqrdLen > (std::numeric_limits<float>::epsilon() ) )
        {
            float invSqrdLen = 1.0f/sqrdLen;
            return Quaternion( w * invSqrdLen , - x * invSqrdLen , -y * invSqrdLen , -z * invSqrdLen);
        }
        else
        {
            return ZERO;
        }
	}

	//-----------------------------------------------------------------------
	void Quaternion::ToRotationMatrix(Matrix44& _oRot) const
    {
        float fTx  = x+x;
        float fTy  = y+y;
        float fTz  = z+z;
        float fTwx = fTx*w;
        float fTwy = fTy*w;
        float fTwz = fTz*w;
        float fTxx = fTx*x;
        float fTxy = fTy*x;
        float fTxz = fTz*x;
        float fTyy = fTy*y;
        float fTyz = fTz*y;
        float fTzz = fTz*z;

        _oRot[0][0] = 1.0f-(fTyy+fTzz);
        _oRot[0][1] = fTxy-fTwz;
        _oRot[0][2] = fTxz+fTwy;
		_oRot[0][3] = 0;
        _oRot[1][0] = fTxy+fTwz;
        _oRot[1][1] = 1.0f-(fTxx+fTzz);
        _oRot[1][2] = fTyz-fTwx;
		_oRot[1][3] = 0;
        _oRot[2][0] = fTxz-fTwy;
        _oRot[2][1] = fTyz+fTwx;
        _oRot[2][2] = 1.0f-(fTxx+fTyy);
		_oRot[2][3] = 0;

		_oRot[3][0] = 0;
        _oRot[3][1] = 0;
        _oRot[3][2] = 0;
		_oRot[3][3] = 1.0f;
    }
}
