#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace vec{
	struct Vec2{
		static const Vec2 Undefined;

		float x;
		float y;

		Vec2();
		Vec2(float _x, float _y);

		double Length();

		bool isUndefined();

		Vec2 operator+(Vec2 vec);
		Vec2 operator-(Vec2 vec);
		Vec2 operator*(int S);
		Vec2 operator*(double S);
		Vec2 operator/(int S);
		Vec2 operator/(double S);
		void operator+=(Vec2 vec);
		void operator-=(Vec2 vec);
		void operator*=(Vec2 vec);
		void operator/=(Vec2 vec);
		bool operator==(Vec2 vec);
		bool operator!=(Vec2 vec);
		bool operator<(Vec2 vec);
		bool operator>(Vec2 vec);
		bool operator<=(Vec2 vec);
		bool operator>=(Vec2 vec);
	};
	struct IVec2{
		static const IVec2 Undefined;

		int x;
		int y;

		IVec2();
		IVec2(int _x, int _y);

		bool isUndefined();

		double Length();

		IVec2 operator+(IVec2 vec);
		IVec2 operator-(IVec2 vec);
		IVec2 operator*(int S);
		IVec2 operator*(double S);
		IVec2 operator/(int S);
		IVec2 operator/(double S);
		void operator+=(IVec2 vec);
		void operator-=(IVec2 vec);
		void operator*=(IVec2 vec);
		void operator/=(IVec2 vec);
		bool operator==(IVec2 vec);
		bool operator!=(IVec2 vec);
		bool operator<(IVec2 vec);
		bool operator>(IVec2 vec);
		bool operator<=(IVec2 vec);
		bool operator>=(IVec2 vec);
	};
	struct PVec2{
		static const PVec2 Undefined;

		double x;
		double y;

		PVec2();
		PVec2(double _x, double _y);

		bool isUndefined();

		double Length();

		PVec2 operator+(PVec2 vec);
		PVec2 operator-(PVec2 vec);
		PVec2 operator*(int S);
		PVec2 operator*(double S);
		PVec2 operator/(int S);
		PVec2 operator/(double S);
		void operator+=(PVec2 vec);
		void operator-=(PVec2 vec);
		void operator*=(PVec2 vec);
		void operator/=(PVec2 vec);
		bool operator==(PVec2 vec);
		bool operator!=(PVec2 vec);
		bool operator<(PVec2 vec);
		bool operator>(PVec2 vec);
		bool operator<=(PVec2 vec);
		bool operator>=(PVec2 vec);
	};
	
	struct Vec3{
		static const Vec3 Undefined;

		float x;
		float y;
		float z;

		Vec3();
		Vec3(float _x, float _y, float _z);

		bool isUndefined();

		double Length();

		Vec3 operator+(Vec3 vec);
		Vec3 operator-(Vec3 vec);
		Vec3 operator*(int S);
		Vec3 operator*(double S);
		Vec3 operator/(int S);
		Vec3 operator/(double S);
		void operator+=(Vec3 vec);
		void operator-=(Vec3 vec);
		void operator*=(Vec3 vec);
		void operator/=(Vec3 vec);
		bool operator==(Vec3 vec);
		bool operator!=(Vec3 vec);
		bool operator<(Vec3 vec);
		bool operator>(Vec3 vec);
		bool operator<=(Vec3 vec);
		bool operator>=(Vec3 vec);
	};
	struct IVec3{
		static const IVec3 Undefined;

		int x;
		int y;
		int z;

		IVec3();
		IVec3(int _x, int _y, int _z);

		bool isUndefined();

		double Length();

		IVec3 operator+(IVec3 vec);
		IVec3 operator-(IVec3 vec);
		IVec3 operator*(int S);
		IVec3 operator*(double S);
		IVec3 operator/(int S);
		IVec3 operator/(double S);
		void operator+=(IVec3 vec);
		void operator-=(IVec3 vec);
		void operator*=(IVec3 vec);
		void operator/=(IVec3 vec);
		bool operator==(IVec3 vec);
		bool operator!=(IVec3 vec);
		bool operator<(IVec3 vec);
		bool operator>(IVec3 vec);
		bool operator<=(IVec3 vec);
		bool operator>=(IVec3 vec);
	};
	struct PVec3{
		static const PVec3 Undefined;

		double x;
		double y;
		double z;

		PVec3();
		PVec3(double _x, double _y, double _z);

		bool isUndefined();

		double Length();

		PVec3 operator+(PVec3 vec);
		PVec3 operator-(PVec3 vec);
		PVec3 operator*(int S);
		PVec3 operator*(double S);
		PVec3 operator/(int S);
		PVec3 operator/(double S);
		void operator+=(PVec3 vec);
		void operator-=(PVec3 vec);
		void operator*=(PVec3 vec);
		void operator/=(PVec3 vec);
		bool operator==(PVec3 vec);
		bool operator!=(PVec3 vec);
		bool operator<(PVec3 vec);
		bool operator>(PVec3 vec);
		bool operator<=(PVec3 vec);
		bool operator>=(PVec3 vec);
	};
	
	class Convert{
		public:
			//any vec3 besides PVec3 to PVec3
			static PVec3 V2P3(Vec3 vec);
			static PVec3 V2P3(IVec3 vec);

			//any vec3 besides Vec3 to Vec3
			static Vec3 V2V3(IVec3 vec);
			static Vec3 V2V3(PVec3 vec);
			
			//any vec3 besides IVec3 to IVec3
			static IVec3 V2I3(Vec3 vec);
			static IVec3 V2I3(PVec3 vec);
			
			//any vec2 besides PVec2 to PVec2
			static PVec2 V2P2(Vec2 vec);
			static PVec2 V2P2(IVec2 vec);
			
			//any vec2 besides Vec2 to Vec2
			static Vec2 V2V2(IVec2 vec);
			static Vec2 V2V2(PVec2 vec);
			
			//any vec2 besides IVec2 to IVec2
			static IVec2 V2I2(Vec2 vec);
			static IVec2 V2I2(PVec2 vec);
	};

}

//Kill me
//
//Later

#endif
