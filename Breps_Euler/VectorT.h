/*---------------------------------------------------------------------------------------------------------------------
*  _               _  _             _   *
*   \             /  | \           / |  *     VolumeMesh : The Open Data Structure for Tetrahedral and Hexahedral Mesh
*    \           /   |  \         /  |  *     
*  	  \         /    |   \       /   |  *     Copyright(C) 2010 by Computer Aided Designed Group
*	   \       /     |    \     /    |  *     State Key Lab. of CAD & CG, Zhejiang University
*	    \     /      |     \   /     |  *
*	     \   /       |      \_/      |  *
*		  \_/        |               |_ * 
*                                       *
*-----------------------------------------------------------------------------------------------------------------------
* License
*
*    This file is part of VolumeMesh.
*
*    VolumeMesh is free software: you can redistribute it and/or modify       
*	it under the terms of the GNU Lesser General Public License as          
*	published by the Free Software Foundation, either version 3 of          
*	the License, or (at your option) any later version. 
*	
*	VolumeMesh distributed in the hope that it will be useful,            
*   but WITHOUT ANY WARRANTY; without even the implied warranty of      
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
*	GNU Lesser General Public License for more details.
*   This project is created by Chuhua Xian
*   Developers : Chuhua Xian,   chuhuaxian@gmail.com 
*                Xiaoshen Chen, chinimei@163.com
*
/---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*
*                                                                                                                     *
*                               VolumeMesh                                                                            *
*      Copyright (C) 2010 by Computer Aided Designed Group                                                            *
*        State Key Lab. of CAD & CG, Zhejiang University                                                              *
*         This project is created by Chuhua Xian, 2010.2                                                              *
*                     Email: chuhuaxian@gmail.com                                                                     *
*---------------------------------------------------------------------------------------------------------------------*/ 

/**********************************************************************************************************************
* this file defines the vector template                                                                              *
* $ written by xianc $                                                                                               *
* $ Version 0.1 $                                                                                                    *
* $ Date: 2010-02-08 $                                                                                               *
**********************************************************************************************************************/


#ifndef _VOLUME_MESH_VECTOR_H_
#define _VOLUME_MESH_VECTOR_H_
//---------------------------------------------------------------------------------------------------------------------


#include <math.h>
#include <iostream>


#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

/// namespace VolumeMesh
namespace BRep
{
	//---------------------------------------------------------------------------------------------------------------------
	template <typename Scalar,int N> 
	class VectorT
	{
	public:
		/// the type of the Scalar used in this template
		typedef Scalar Scalar;
		/// the type of the scalar used in this template
		typedef Scalar value_type;

		/// type of this vector
		typedef VectorT<Scalar, N>  vector_type;

	public:
		explicit VectorT(const Scalar & s = 0)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] = 0;
			}	
		}
		explicit VectorT(Scalar s[])
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] = s[i];
			}			
		}

		// special constructor for 2D vector
		VectorT(const Scalar & v0, const Scalar & v1)
		{
			assert(Dim() == 2);
			values_[0] = v0;
			values_[1] = v1;
		}

		// special constructor for 3D vector
		VectorT(const Scalar & v0, const Scalar & v1, const Scalar & v2)
		{
			assert(Dim() == 3);
			values_[0] = v0;
			values_[1] = v1;
			values_[2] = v2;
		}

		// special constructor for 4D vector
		VectorT(const Scalar & v0, const Scalar & v1, const Scalar & v2, const Scalar & v3)
		{
			assert(Dim() == 4);
			values_[0] = v0;
			values_[1] = v1;
			values_[2] = v2;
			values_[3] = v3;
		}

		// special constructor for 5D vector
		VectorT(const Scalar & v0, const Scalar & v1, const Scalar & v2, const Scalar & v3, const Scalar v4)
		{
			assert(Dim() == 5);
			values_[0] = v0;
			values_[1] = v1;
			values_[2] = v2;
			values_[3] = v3;
			values_[4] = v4;
		}

		// special constructor for 6D vector
		VectorT(const Scalar & v0, const Scalar & v1, const Scalar & v2, const Scalar & v3, const Scalar & v4, const Scalar & v5)
		{
			assert(Dim() == 6);
			values_[0] = v0;
			values_[1] = v1;
			values_[2] = v2;
			values_[3] = v3;
			values_[4] = v4;
			values_[5] = v5;
		}
		//-----------------------------------------------------------------------------------------------------------------
	public:
		// override the operator
		Scalar & operator [] (const int & i)
		{
			assert((i > -1) && (i < N));
			return values_[i];
		}
		// override the operator
		Scalar operator [] (const int & i) const
		{
			assert((i > -1) && (i < N));
			return values_[i];
		}

		bool operator == (const VectorT<Scalar, N> & v) const
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				if (values_[i] != v[i])
				{
					return false;
				}
			}

			return true;
		}
		bool operator != (const VectorT<Scalar, N> & v) const
		{			
			return !(*this == v);
		}

		bool operator != (const VectorT<Scalar, N> & v)
		{			
			return !(*this == v);
		}

		bool operator < (const VectorT<Scalar, N> & v) const
		{
			unsigned int i;
			for (i = 0; i < N; i ++)
			{
				if (values_[i] != v[i])
				{
					break;
				}				
			}

			if (i == N)
			{
				return false;
			}			

			if (values_[i] < v[i])
			{
				return true;
			}
			return false;
		}
		VectorT<Scalar, N>  operator * (const Scalar & s)
		{
			VectorT<Scalar, N> v;
			for (unsigned int i = 0; i < N; i ++)
			{
				v[i] = values_[i] * s;	
			}

			return v;
		}

		VectorT<Scalar, N>  operator *= (const Scalar & s)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] *= s;	
			}

			return *this;
		}
		VectorT<Scalar, N>  operator / (const Scalar & s)
		{
			VectorT<Scalar, N> v;
			for (unsigned int i = 0; i < N; i ++)
			{
				v[i] = values_[i] / s;	
			}

			return v;
		}

		VectorT<Scalar, N>  operator /= (const Scalar & s)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] /= s;	
			}

			return *this;
		}

		VectorT<Scalar, N>  operator - (const VectorT<Scalar, N> & v)
		{
			VectorT<Scalar, N> vv;
			for (unsigned int i = 0; i < N; i ++)
			{
				vv[i] = values_[i] - v[i];	
			}

			return vv;
		}

		VectorT<Scalar, N>  operator + (const VectorT<Scalar, N> & v)
		{
			VectorT<Scalar, N> vv;
			for (unsigned int i = 0; i < N; i ++)
			{
				vv[i] = values_[i] + v[i];	
			}

			return vv;
		}

		VectorT<Scalar, N>  operator -= (const VectorT<Scalar, N> & v)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] -=  v[i];	
			}

			return *this;
		}

		VectorT<Scalar, N>  operator += (const VectorT<Scalar, N> & v)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] +=  v[i];	
			}

			return *this;
		}




		static unsigned int Dim()
		{
			return N;
		}


		Scalar * data()
		{
			return values_;
		}

		Scalar * data() const
		{
			return values_;
		}

		VectorT<Scalar, N>  zero ()
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				values_[i] =  0;	
			}

			return *this;
		}

	public:
		// override the operator
		Scalar operator | (VectorT<Scalar, N> & v)
		{
			Scalar s;
			s = 0;
			for (unsigned int i = 0; i < N; i ++)
			{
				s += values_[i] * v[i];
			}
			return s;
		}

		// the dot product
		friend Scalar dotProduct(VectorT<Scalar, N> & v0, VectorT<Scalar, N> & v1)
		{
			return v0 | v1;
		}
		// the cross product
		friend VectorT<Scalar, 3> crossProduct(VectorT<Scalar, 3> & v0, VectorT<Scalar, 3> & v1)
		{
			return v0 % v1;
		}

		// override the operator
		VectorT<Scalar, 3> operator % (VectorT<Scalar, 3> & v)
		{
			return VectorT<Scalar, 3>(values_[1] * v[2] - values_[2] * v[1], 
				values_[2] * v[0] - values_[0] * v[2],
				values_[0] * v[1] - values_[1] * v[0]);
		}

		Scalar norm()
		{
			return sqrt((*this) | (*this));
		}

		Scalar sqr_norm()
		{
			return ((*this) | (*this));
		}

		VectorT<Scalar, N> normalize()
		{
			return (*this) /= norm();			
		}

		VectorT<Scalar, N> maximize (const VectorT<Scalar, N> & v)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				if (values_[i] < v[i])
				{
					values_[i] = v[i];
				}	
			}

			return *this;
		}

		VectorT<Scalar, N> minimize (const VectorT<Scalar, N> & v)
		{
			for (unsigned int i = 0; i < N; i ++)
			{
				if (values_[i] > v[i])
				{
					values_[i] = v[i];
				}	
			}

			return *this;
		}






		//----------------------------------------------------------------------------------------------------------------
	private:
		Scalar values_[N];
	};	

	//-----------------------------------------------------------------------------------------------------------------
	/** 1-byte signed vector */
	typedef VectorT<signed char,1> Vec1c;
	/** 1-byte unsigned vector */
	typedef VectorT<unsigned char,1> Vec1uc;
	/** 1-short signed vector */
	typedef VectorT<signed short int,1> Vec1s;
	/** 1-short unsigned vector */
	typedef VectorT<unsigned short int,1> Vec1us;
	/** 1-int signed vector */
	typedef VectorT<signed int,1> Vec1i;
	/** 1-int unsigned vector */
	typedef VectorT<unsigned int,1> Vec1ui;
	/** 1-float vector */
	typedef VectorT<float,1> Vec1f;
	/** 1-double vector */
	typedef VectorT<double,1> Vec1d;

	/** 2-byte signed vector */
	typedef VectorT<signed char,2> Vec2c;
	/** 2-byte unsigned vector */
	typedef VectorT<unsigned char,2> Vec2uc;
	/** 2-short signed vector */
	typedef VectorT<signed short int,2> Vec2s;
	/** 2-short unsigned vector */
	typedef VectorT<unsigned short int,2> Vec2us;
	/** 2-int signed vector */
	typedef VectorT<signed int,2> Vec2i;
	/** 2-int unsigned vector */
	typedef VectorT<unsigned int,2> Vec2ui;
	/** 2-float vector */
	typedef VectorT<float,2> Vec2f;
	/** 2-double vector */
	typedef VectorT<double,2> Vec2d;

	/** 3-byte signed vector */
	typedef VectorT<signed char,3> Vec3c;
	/** 3-byte unsigned vector */
	typedef VectorT<unsigned char,3> Vec3uc;
	/** 3-short signed vector */
	typedef VectorT<signed short int,3> Vec3s;
	/** 3-short unsigned vector */
	typedef VectorT<unsigned short int,3> Vec3us;
	/** 3-int signed vector */
	typedef VectorT<signed int,3> Vec3i;
	/** 3-int unsigned vector */
	typedef VectorT<unsigned int,3> Vec3ui;
	/** 3-float vector */
	typedef VectorT<float,3> Vec3f;
	/** 3-double vector */
	typedef VectorT<double,3> Vec3d;

	/** 4-byte signed vector */
	typedef VectorT<signed char,4> Vec4c;
	/** 4-byte unsigned vector */
	typedef VectorT<unsigned char,4> Vec4uc;
	/** 4-short signed vector */
	typedef VectorT<signed short int,4> Vec4s;
	/** 4-short unsigned vector */
	typedef VectorT<unsigned short int,4> Vec4us;
	/** 4-int signed vector */
	typedef VectorT<signed int,4> Vec4i;
	/** 4-int unsigned vector */
	typedef VectorT<unsigned int,4> Vec4ui;
	/** 4-float vector */
	typedef VectorT<float,4> Vec4f;
	/** 4-double vector */
	typedef VectorT<double,4> Vec4d;

	/** 6-byte signed vector */
	typedef VectorT<signed char,6> Vec6c;
	/** 6-byte unsigned vector */
	typedef VectorT<unsigned char,6> Vec6uc;
	/** 6-short signed vector */
	typedef VectorT<signed short int,6> Vec6s;
	/** 6-short unsigned vector */
	typedef VectorT<unsigned short int,6> Vec6us;
	/** 6-int signed vector */
	typedef VectorT<signed int,6> Vec6i;
	/** 6-int unsigned vector */
	typedef VectorT<unsigned int,6> Vec6ui;
	/** 6-float vector */
	typedef VectorT<float,6> Vec6f;
	/** 6-double vector */
	typedef VectorT<double,6> Vec6d;

	typedef Vec3d Point;



	//---------------------------------------------------------------------------------------------------------------------
} // namespace VolumeMesh
//---------------------------------------------------------------------------------------------------------------------
#endif // _VOLUME_MESH_VECTOR_H_ defined
