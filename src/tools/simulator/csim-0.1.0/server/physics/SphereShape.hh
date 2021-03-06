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
/* Desc: Sphere shape
 * Author: Nate Keonig
 * Date: 14 Oct 2009
 * SVN: $Id:$
 *
 * Modified by: Eurico Pedrosa <efp@ua.p>
 * Date: 10 Fev 2010
 *
 * Modification Notes
 *
 *  The modifications presented by me, have the purpose of
 *  removing the 'rendering' and 'gui' modules from the code base.
 *  The reasons behind this decision are simple, allow gazebo to run
 *  on computers with less gpu capabilities and lessen the the coupling
 *  between simulation and visualization.
 *
 */

#ifndef SPHERESHAPE_HH
#define SPHERESHAPE_HH

#include "Param.hh"
#include "Shape.hh"

namespace gazebo
{

  /// \addtogroup gazebo_physics_geom
  /// \{
  /** \defgroup gazebo_sphere_geom Sphere geom
      \brief Sphere geom

      \par Attributes
      The following attributes are supported.

      \htmlinclude default_geom_attr_include.html

      - size (float, meters)
        - Radius of the sphere
        - Default: 0

      \par Example
      \verbatim
      <geom:sphere name="geom_name">
        <xyz>1 2 3</xyz>
        <rpy>0 0 30</rpy>
        <size>0.1</size>
        <mass>0.5</mass>
        <laserFiducialId>1</laserFiducialId>
        <laserRetro>0.5</laserRetro>

        <visual>
          <mesh>default</mesh>
          <size>0.1 0.1 0.1</size>
          <material>Gazebo/Red</material>
        </visual>
      </geom:sphere>
      \endverbatim
    */
  /// \}
  /// \addtogroup gazebo_sphere_geom 
  /// \{

  /// \brief Sphere geom
  class SphereShape : public Shape
  {
    /// \brief Constructor
    public: SphereShape(Geom *parent);

    /// \brief Destructor
    public: virtual ~SphereShape();

    /// \brief Load the sphere
    public: virtual void Load(XMLConfigNode *node);

    /// \brief Save shape parameters
    public: virtual void Save(std::string &prefix, std::ostream &stream);

    /// \brief Set the size
    public: virtual void SetSize(const double &radius);
    
    /// \brief Get the size
    public: virtual const double GetSize();

    private: ParamT<double> *radiusP;
  };

  /// \}
}

#endif
