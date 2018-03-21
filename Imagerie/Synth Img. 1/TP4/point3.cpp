#include "point3.h"

point3::point3(){
	x = 0.0; y = 0.0; z = 0.0;
	r = 1; g = 1; b = 1;
}

point3::point3(const double X,const double Y,const double Z){
	x = X; y = Y; z = Z;
}

point3::point3(const double X,const double Y,const double Z, const double R, const double G, const double B){
	x = X; y = Y; z = Z; r = R; g = G; b =B;
}

void point3::setRGB(const double R, const double G, const double B)
{
	r =R; g = G; b = B;
}

bool point3::operator==(const point3 &op) const {
	return( (x == op.x) && (y == op.y) && (z == op.z) ) ;
}

point3& point3::operator=(const point3 &op) {
	x = op.x; y = op.y; z = op.z;
return *this;
}

point3 point3::operator+(const point3 &op) const {
	return( point3( x + op.x, y + op.y, z + op.z) );
}

point3& point3::operator*=(const double op) {
	x *= op; y *= op; z *= op;
return *this;
}

point3 point3::operator*(const double op) const {
	return ( point3( x * op, y * op, z * op) );
}

point3& point3::operator/=(const double op) {
	x /= op; y /= op; z /= op;
return *this;
}

point3 point3::operator/(const double op) const {
	return ( point3( x / op, y / op, z / op) );
}

ostream&  operator<<(ostream& p, point3 op) {
	p << "(" << op.x <<", " << op.y << "," << op.z  << ")";
return(p);
}
