#include "Vector.hpp"
#include <math.h>
#include <limits>

//Vec2
vec::Vec2::Vec2()								{x = 0; y = 0;}
vec::Vec2::Vec2(float _x, float _y)				{x=_x; y=_y;}

const vec::Vec2 vec::Vec2::Undefined(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
bool vec::Vec2::isUndefined() {return *this == Undefined;}

double vec::Vec2::Length()						{return sqrt(pow(x, 2)+pow(y, 2));}

vec::Vec2 vec::Vec2::operator+(vec::Vec2 vec)	{return vec::Vec2(x+vec.x, y+vec.y);}
vec::Vec2 vec::Vec2::operator-(vec::Vec2 vec)	{return vec::Vec2(x-vec.x, y-vec.y);}
vec::Vec2 vec::Vec2::operator*(int S)			{return vec::Vec2(x*S, y*S);}
vec::Vec2 vec::Vec2::operator*(double S)		{return vec::Vec2(x*S, y*S);}
vec::Vec2 vec::Vec2::operator/(int S)			{return vec::Vec2(x/S, y/S);}
vec::Vec2 vec::Vec2::operator/(double S)		{return vec::Vec2(x/S, y/S);}

void vec::Vec2::operator+=(vec::Vec2 vec)		{x+=vec.x; y+=vec.y;}
void vec::Vec2::operator-=(vec::Vec2 vec)		{x-=vec.x; y-=vec.y;}
void vec::Vec2::operator*=(vec::Vec2 vec)		{x*=vec.x; y*=vec.y;}
void vec::Vec2::operator/=(vec::Vec2 vec)		{x/=vec.x; y/=vec.y;}

bool vec::Vec2::operator==(vec::Vec2 vec)		{return (x == vec.x && y == vec.y);}
bool vec::Vec2::operator!=(vec::Vec2 vec)		{return !(x == vec.x && y == vec.y);}
bool vec::Vec2::operator<(vec::Vec2 vec)		{return (this->Length()<vec.Length());}
bool vec::Vec2::operator>(vec::Vec2 vec)		{return (this->Length()>vec.Length());}
bool vec::Vec2::operator<=(vec::Vec2 vec)		{return (this->Length()<=vec.Length());}
bool vec::Vec2::operator>=(vec::Vec2 vec)		{return (this->Length()>=vec.Length());}


//IVec2
vec::IVec2::IVec2()								{x = 0; y = 0;}
vec::IVec2::IVec2(int _x, int _y)				{x=_x; y=_y;}

const vec::IVec2 vec::IVec2::Undefined(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
bool vec::IVec2::isUndefined() {return *this == Undefined;}

double vec::IVec2::Length()						{return sqrt(pow(x, 2)+pow(y, 2));}

vec::IVec2 vec::IVec2::operator+(vec::IVec2 vec)	{return vec::IVec2(x+vec.x, y+vec.y);}
vec::IVec2 vec::IVec2::operator-(vec::IVec2 vec)	{return vec::IVec2(x-vec.x, y-vec.y);}
vec::IVec2 vec::IVec2::operator*(int S)			{return vec::IVec2(x*S, y*S);}
vec::IVec2 vec::IVec2::operator*(double S)		{return vec::IVec2(x*S, y*S);}
vec::IVec2 vec::IVec2::operator/(int S)			{return vec::IVec2(x/S, y/S);}
vec::IVec2 vec::IVec2::operator/(double S)		{return vec::IVec2(x/S, y/S);}

void vec::IVec2::operator+=(vec::IVec2 vec)		{x+=vec.x; y+=vec.y;}
void vec::IVec2::operator-=(vec::IVec2 vec)		{x-=vec.x; y-=vec.y;}
void vec::IVec2::operator*=(vec::IVec2 vec)		{x*=vec.x; y*=vec.y;}
void vec::IVec2::operator/=(vec::IVec2 vec)		{x/=vec.x; y/=vec.y;}

bool vec::IVec2::operator==(vec::IVec2 vec)		{return (x == vec.x && y == vec.y);}
bool vec::IVec2::operator!=(vec::IVec2 vec)		{return !(x == vec.x && y == vec.y);}
bool vec::IVec2::operator<(vec::IVec2 vec)		{return (this->Length()<vec.Length());}
bool vec::IVec2::operator>(vec::IVec2 vec)		{return (this->Length()>vec.Length());}
bool vec::IVec2::operator<=(vec::IVec2 vec)		{return (this->Length()<=vec.Length());}
bool vec::IVec2::operator>=(vec::IVec2 vec)		{return (this->Length()>=vec.Length());}

//PVec2
vec::PVec2::PVec2()								{x = 0; y = 0;}
vec::PVec2::PVec2(double _x, double _y)				{x=_x; y=_y;}

const vec::PVec2 vec::PVec2::Undefined(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
bool vec::PVec2::isUndefined() {return *this == Undefined;}

double vec::PVec2::Length()						{return sqrt(pow(x, 2)+pow(y, 2));}

vec::PVec2 vec::PVec2::operator+(vec::PVec2 vec)	{return vec::PVec2(x+vec.x, y+vec.y);}
vec::PVec2 vec::PVec2::operator-(vec::PVec2 vec)	{return vec::PVec2(x-vec.x, y-vec.y);}
vec::PVec2 vec::PVec2::operator*(int S)			{return vec::PVec2(x*S, y*S);}
vec::PVec2 vec::PVec2::operator*(double S)		{return vec::PVec2(x*S, y*S);}
vec::PVec2 vec::PVec2::operator/(int S)			{return vec::PVec2(x/S, y/S);}
vec::PVec2 vec::PVec2::operator/(double S)		{return vec::PVec2(x/S, y/S);}

void vec::PVec2::operator+=(vec::PVec2 vec)		{x+=vec.x; y+=vec.y;}
void vec::PVec2::operator-=(vec::PVec2 vec)		{x-=vec.x; y-=vec.y;}
void vec::PVec2::operator*=(vec::PVec2 vec)		{x*=vec.x; y*=vec.y;}
void vec::PVec2::operator/=(vec::PVec2 vec)		{x/=vec.x; y/=vec.y;}

bool vec::PVec2::operator==(vec::PVec2 vec)		{return (x == vec.x && y == vec.y);}
bool vec::PVec2::operator!=(vec::PVec2 vec)		{return !(x == vec.x && y == vec.y);}
bool vec::PVec2::operator<(vec::PVec2 vec)		{return (this->Length()<vec.Length());}
bool vec::PVec2::operator>(vec::PVec2 vec)		{return (this->Length()>vec.Length());}
bool vec::PVec2::operator<=(vec::PVec2 vec)		{return (this->Length()<=vec.Length());}
bool vec::PVec2::operator>=(vec::PVec2 vec)		{return (this->Length()>=vec.Length());}



//Vec3
vec::Vec3::Vec3()								{x = 0; y = 0; z = 0;}
vec::Vec3::Vec3(float _x, float _y, float _z)	{x=_x; y=_y; z=_z;}

const vec::Vec3 vec::Vec3::Undefined(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
bool vec::Vec3::isUndefined() {return *this == Undefined;}

double vec::Vec3::Length()						{return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));}

vec::Vec3 vec::Vec3::operator+(vec::Vec3 vec)	{return vec::Vec3(x+vec.x, y+vec.y, z+vec.z);}
vec::Vec3 vec::Vec3::operator-(vec::Vec3 vec)	{return vec::Vec3(x-vec.x, y-vec.y, z+vec.z);}
vec::Vec3 vec::Vec3::operator*(int S)			{return vec::Vec3(x*S, y*S, z*S);}
vec::Vec3 vec::Vec3::operator*(double S)		{return vec::Vec3(x*S, y*S, z*S);}
vec::Vec3 vec::Vec3::operator/(int S)			{return vec::Vec3(x/S, y/S, z*S);}
vec::Vec3 vec::Vec3::operator/(double S)		{return vec::Vec3(x/S, y/S, z*S);}

void vec::Vec3::operator+=(vec::Vec3 vec)		{x+=vec.x; y+=vec.y; z+=vec.z;}
void vec::Vec3::operator-=(vec::Vec3 vec)		{x-=vec.x; y-=vec.y; z-=vec.z;}
void vec::Vec3::operator*=(vec::Vec3 vec)		{x*=vec.x; y*=vec.y; z*=vec.z;}
void vec::Vec3::operator/=(vec::Vec3 vec)		{x/=vec.x; y/=vec.y; z/=vec.z;}

bool vec::Vec3::operator==(vec::Vec3 vec)		{return (x == vec.x && y == vec.y && z == vec.z);}
bool vec::Vec3::operator!=(vec::Vec3 vec)		{return !(x == vec.x && y == vec.y && z == vec.z);}
bool vec::Vec3::operator<(vec::Vec3 vec)		{return (this->Length()<vec.Length());}
bool vec::Vec3::operator>(vec::Vec3 vec)		{return (this->Length()>vec.Length());}
bool vec::Vec3::operator<=(vec::Vec3 vec)		{return (this->Length()<=vec.Length());}
bool vec::Vec3::operator>=(vec::Vec3 vec)		{return (this->Length()>=vec.Length());}

//IVec3
vec::IVec3::IVec3()								{x = 0; y = 0; z = 0;}
vec::IVec3::IVec3(int _x, int _y, int _z)		{x=_x; y=_y; z=_z;}

const vec::IVec3 vec::IVec3::Undefined(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
bool vec::IVec3::isUndefined() {return *this == Undefined;}

double vec::IVec3::Length()						{return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));}

vec::IVec3 vec::IVec3::operator+(vec::IVec3 vec){return vec::IVec3(x+vec.x, y+vec.y, z+vec.z);}
vec::IVec3 vec::IVec3::operator-(vec::IVec3 vec){return vec::IVec3(x-vec.x, y-vec.y, z+vec.z);}
vec::IVec3 vec::IVec3::operator*(int S)			{return vec::IVec3(x*S, y*S, z*S);}
vec::IVec3 vec::IVec3::operator*(double S)		{return vec::IVec3(x*S, y*S, z*S);}
vec::IVec3 vec::IVec3::operator/(int S)			{return vec::IVec3(x/S, y/S, z*S);}
vec::IVec3 vec::IVec3::operator/(double S)		{return vec::IVec3(x/S, y/S, z*S);}

void vec::IVec3::operator+=(vec::IVec3 vec)		{x+=vec.x; y+=vec.y; z+=vec.z;}
void vec::IVec3::operator-=(vec::IVec3 vec)		{x-=vec.x; y-=vec.y; z-=vec.z;}
void vec::IVec3::operator*=(vec::IVec3 vec)		{x*=vec.x; y*=vec.y; z*=vec.z;}
void vec::IVec3::operator/=(vec::IVec3 vec)		{x/=vec.x; y/=vec.y; z/=vec.z;}

bool vec::IVec3::operator==(vec::IVec3 vec)		{return (x == vec.x && y == vec.y && z == vec.z);}
bool vec::IVec3::operator!=(vec::IVec3 vec)		{return !(x == vec.x && y == vec.y && z == vec.z);}
bool vec::IVec3::operator<(vec::IVec3 vec)		{return (this->Length()<vec.Length());}
bool vec::IVec3::operator>(vec::IVec3 vec)		{return (this->Length()>vec.Length());}
bool vec::IVec3::operator<=(vec::IVec3 vec)		{return (this->Length()<=vec.Length());}
bool vec::IVec3::operator>=(vec::IVec3 vec)		{return (this->Length()>=vec.Length());}

//PVec3
vec::PVec3::PVec3()									{x = 0; y = 0; z = 0;}
vec::PVec3::PVec3(double _x, double _y, double _z)	{x=_x; y=_y; z=_z;}

const vec::PVec3 vec::PVec3::Undefined(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
bool vec::PVec3::isUndefined() {return *this == Undefined;}

double vec::PVec3::Length()						{return sqrt(pow(x, 2)+pow(y, 2)+pow(z, 2));}

vec::PVec3 vec::PVec3::operator+(vec::PVec3 vec){return vec::PVec3(x+vec.x, y+vec.y, z+vec.z);}
vec::PVec3 vec::PVec3::operator-(vec::PVec3 vec){return vec::PVec3(x-vec.x, y-vec.y, z+vec.z);}
vec::PVec3 vec::PVec3::operator*(int S)			{return vec::PVec3(x*S, y*S, z*S);}
vec::PVec3 vec::PVec3::operator*(double S)		{return vec::PVec3(x*S, y*S, z*S);}
vec::PVec3 vec::PVec3::operator/(int S)			{return vec::PVec3(x/S, y/S, z*S);}
vec::PVec3 vec::PVec3::operator/(double S)		{return vec::PVec3(x/S, y/S, z*S);}

void vec::PVec3::operator+=(vec::PVec3 vec)		{x+=vec.x; y+=vec.y; z+=vec.z;}
void vec::PVec3::operator-=(vec::PVec3 vec)		{x-=vec.x; y-=vec.y; z-=vec.z;}
void vec::PVec3::operator*=(vec::PVec3 vec)		{x*=vec.x; y*=vec.y; z*=vec.z;}
void vec::PVec3::operator/=(vec::PVec3 vec)		{x/=vec.x; y/=vec.y; z/=vec.z;}

bool vec::PVec3::operator==(vec::PVec3 vec)		{return (x == vec.x && y == vec.y && z == vec.z);}
bool vec::PVec3::operator!=(vec::PVec3 vec)		{return !(x == vec.x && y == vec.y && z == vec.z);}
bool vec::PVec3::operator<(vec::PVec3 vec)		{return (this->Length()<vec.Length());}
bool vec::PVec3::operator>(vec::PVec3 vec)		{return (this->Length()>vec.Length());}
bool vec::PVec3::operator<=(vec::PVec3 vec)		{return (this->Length()<=vec.Length());}
bool vec::PVec3::operator>=(vec::PVec3 vec)		{return (this->Length()>=vec.Length());}



//Converter
//vec2
vec::IVec2 vec::Convert::V2I2(Vec2 vec)			{return IVec2((int)vec.x, (int)vec.y);}
vec::IVec2 vec::Convert::V2I2(PVec2 vec)		{return IVec2((int)vec.x, (int)vec.y);}

vec::Vec2 vec::Convert::V2V2(IVec2 vec)			{return Vec2((float)vec.x, (float)vec.y);}
vec::Vec2 vec::Convert::V2V2(PVec2 vec)			{return Vec2((float)vec.x, (float)vec.y);}

vec::PVec2 vec::Convert::V2P2(IVec2 vec)		{return PVec2((double)vec.x, (double)vec.y);}
vec::PVec2 vec::Convert::V2P2(Vec2 vec)			{return PVec2((double)vec.x, (double)vec.y);}

//vec3
vec::IVec3 vec::Convert::V2I3(Vec3 vec)			{return IVec3((int)vec.x, (int)vec.y, (int)vec.z);}
vec::IVec3 vec::Convert::V2I3(PVec3 vec)		{return IVec3((int)vec.x, (int)vec.y, (int)vec.z);}

vec::Vec3 vec::Convert::V2V3(IVec3 vec)			{return Vec3((float)vec.x, (float)vec.y, (float)vec.z);}
vec::Vec3 vec::Convert::V2V3(PVec3 vec)			{return Vec3((float)vec.x, (float)vec.y, (float)vec.z);}

vec::PVec3 vec::Convert::V2P3(IVec3 vec)		{return PVec3((double)vec.x, (double)vec.y, (double)vec.z);}
vec::PVec3 vec::Convert::V2P3(Vec3 vec)			{return PVec3((double)vec.x, (double)vec.y, (double)vec.z);}
