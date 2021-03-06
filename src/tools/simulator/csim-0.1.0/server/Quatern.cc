/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/* Desc: External interfaces for Gazebo
 * Author: Nate Koenig
 * Date: 03 Apr 2007
 * SVN: $Id: Quatern.cc 8471 2009-12-17 02:53:42Z natepak $
 */
#include <math.h>
#include "Quatern.hh"

using namespace gazebo;

////////////////////////////////////////////////////////////////////////////////
// Default Constructor
Quatern::Quatern()
    : u(1), x(0), y(0), z(0)
{
  if ( u == 0 && x == 0 && y == 0 && z == 0 )
  {
    /// @todo: give user warning
    this->SetToIdentity();
  }
  this->Normalize();
}

////////////////////////////////////////////////////////////////////////////////
// Constructor
Quatern::Quatern( const double &u, const double &x, const double &y, const double &z)
    : u(u), x(x), y(y), z(z)
{
}

////////////////////////////////////////////////////////////////////////////////
// Copy Constructor
Quatern::Quatern( const Quatern &qt )
{
  this->u = qt.u;
  this->x = qt.x;
  this->y = qt.y;
  this->z = qt.z;
}

////////////////////////////////////////////////////////////////////////////////
// Destructor
Quatern::~Quatern()
{
}

////////////////////////////////////////////////////////////////////////////////
// Equal operator
const Quatern &Quatern::operator=(const Quatern &qt)
{
  this->u = qt.u;
  this->x = qt.x;
  this->y = qt.y;
  this->z = qt.z;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Set quatern to identity
void Quatern::SetToIdentity()
{
  this->u = 1.0;
  this->x = 0.0;
  this->y = 0.0;
  this->z = 0.0;
}


////////////////////////////////////////////////////////////////////////////////
// Invert the quaternion
void Quatern::Invert()
{
  double norm = this->u*this->u+this->x*this->x+this->y*this->y+this->z*this->z;
  this->u = this->u/norm;
  this->x = -this->x/norm;
  this->y = -this->y/norm;
  this->z = -this->z/norm;
}

////////////////////////////////////////////////////////////////////////////////
// Get the inverse of this quaternion
Quatern Quatern::GetInverse() const 
{
  Quatern q;

  double norm = this->u*this->u+this->x*this->x+this->y*this->y+this->z*this->z;

  if (norm > 0.0)
  {
    q.u = this->u / norm;
    q.x = -this->x / norm;
    q.y = -this->y / norm;
    q.z = -this->z / norm;
  }

  return q;
}


////////////////////////////////////////////////////////////////////////////////
// Normalize the quaternion
void Quatern::Normalize()
{
  double s;

  s = sqrt(this->u * this->u + this->x * this->x + this->y * this->y + this->z * this->z);

  this->u /= s;
  this->x /= s;
  this->y /= s;
  this->z /= s;
}

////////////////////////////////////////////////////////////////////////////////
// Set the quaternion from an axis and angle
void Quatern::SetFromAxis(double ax, double ay, double az, double aa)
{
  double l;

  l = ax * ax + ay * ay + az * az;

  if (l > 0.0)
  {
    aa *= 0.5;
    l = sin(aa) / sqrt(l);
    this->u = cos(aa);
    this->x = ax * l;
    this->y = ay * l;
    this->z = az * l;
  }
  else
  {
    this->u = 1;
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }

  this->Normalize();
}

////////////////////////////////////////////////////////////////////////////////
/// Set this quaternion from another
void Quatern::Set(double u, double x, double y, double z)
{
  this->u = u;
  this->x = x;
  this->y = y;
  this->z = z;
}

////////////////////////////////////////////////////////////////////////////////
// Set the quaternion from Euler angles
void Quatern::SetFromEuler(const Vector3 &vec)
{
  double phi, the, psi;

  phi = vec.x / 2.0;
  the = vec.y / 2.0;
  psi = vec.z / 2.0;

  this->u = cos(phi) * cos(the) * cos(psi) + sin(phi) * sin(the) * sin(psi);
  this->x = sin(phi) * cos(the) * cos(psi) - cos(phi) * sin(the) * sin(psi);
  this->y = cos(phi) * sin(the) * cos(psi) + sin(phi) * cos(the) * sin(psi);
  this->z = cos(phi) * cos(the) * sin(psi) - sin(phi) * sin(the) * cos(psi);

  this->Normalize();
}

////////////////////////////////////////////////////////////////////////////////
// Return the rotation in Euler angles
Vector3 Quatern::GetAsEuler()
{
  Vector3 vec;

  double squ;
  double sqx;
  double sqy;
  double sqz;

  this->Normalize();

  squ = this->u * this->u;
  sqx = this->x * this->x;
  sqy = this->y * this->y;
  sqz = this->z * this->z;

  this->Normalize();

  // Roll
  vec.x = atan2(2 * (this->y*this->z + this->u*this->x), squ - sqx - sqy + sqz);

  // Pitch
  vec.y = asin(-2 * (this->x*this->z - this->u * this->y));

  // Yaw
  vec.z = atan2(2 * (this->x*this->y + this->u*this->z), squ + sqx - sqy - sqz);

  return vec;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the Euler roll angle in radians
double Quatern::GetRoll()
{
  return this->GetAsEuler().x;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the Euler pitch angle in radians
double Quatern::GetPitch()
{
  return this->GetAsEuler().y;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Get the Euler yaw angle in radians
double Quatern::GetYaw()
{
  return this->GetAsEuler().z;
}

////////////////////////////////////////////////////////////////////////////////
// Return rotation as axis and angle (x, y, y, rotation)
Quatern Quatern::GetAsAxis()
{
  return Quatern(acos(this->u)*2, this->x, this->y, this->z);
}

////////////////////////////////////////////////////////////////////////////////
// Scale a Quaternion
void Quatern::Scale(double scale)
{
  Quatern b;

  // Convert to axis-and-angle
  b = this->GetAsAxis();
  b.u *= scale;

  this->SetFromAxis(b.x, b.y, b.z, b.u);
}

////////////////////////////////////////////////////////////////////////////////
/// Addition operator
Quatern Quatern::operator+( const Quatern &qt ) const
{
  Quatern result(this->u + qt.u, this->x + qt.x, 
                 this->y + qt.y, this->z + qt.z);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
/// Addition operator
Quatern Quatern::operator+=( const Quatern &qt ) 
{
  *this = *this + qt;

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Subtraction operator
Quatern Quatern::operator-=( const Quatern &qt )
{
  *this = *this - qt;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Substraction operator
Quatern Quatern::operator-( const Quatern &qt ) const
{
  Quatern result(this->u - qt.u, this->x - qt.x, 
                 this->y - qt.y, this->z - qt.z);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// Multiplication operator
Quatern Quatern::operator*( const Quatern &qt ) const
{
  Quatern c;

  c.x = this->u * qt.x + this->x * qt.u + this->y * qt.z - this->z * qt.y;
  c.y = this->u * qt.y - this->x * qt.z + this->y * qt.u + this->z * qt.x;
  c.z = this->u * qt.z + this->x * qt.y - this->y * qt.x + this->z * qt.u;
  c.u = this->u * qt.u - this->x * qt.x - this->y * qt.y - this->z * qt.z;

  return c;
}

////////////////////////////////////////////////////////////////////////////////
// Multiplication operator
Quatern Quatern::operator*=( const Quatern &qt )
{
  *this = *this * qt;
  return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// Rotate a vector 
Vector3 Quatern::operator*( const Vector3 &v ) const
{
  Quatern tmp(0.0, v.x, v.y, v.z);
  
  tmp = (*this) * (tmp * this->GetInverse());

  return Vector3(tmp.x, tmp.y, tmp.z);
}

////////////////////////////////////////////////////////////////////////////////
/// Rotate a vector using the quaternion
Vector3 Quatern::RotateVector(Vector3 vec) const
{
  Quatern tmp;
  Vector3 result;

  tmp.u = 0.0;
  tmp.x = vec.x;
  tmp.y = vec.y;
  tmp.z = vec.z;

  tmp = (*this) * (tmp * this->GetInverse());

  result.x = tmp.x;
  result.y = tmp.y;
  result.z = tmp.z;

  return result;
}


////////////////////////////////////////////////////////////////////////////////
// See if a quatern is finite (e.g., not nan)
bool Quatern::IsFinite() const
{
  return finite(this->u) && finite(this->x) && finite(this->y) && finite(this->z);
}

