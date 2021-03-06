#ifndef MULTIRAYGEOM_HH
#define MULTIRAYGEOM_HH

#include <vector>

#include "GazeboError.hh"
#include "GazeboMessage.hh"
#include "Vector3.hh"
#include "Angle.hh"
#include "Geom.hh"
#include "Shape.hh"
#include "RayShape.hh"

namespace gazebo
{
  class XMLConfigNode;

  /// \brief Laser geom contains a set of ray-geoms, structured to simulate
  ///        a laser range scanner
  class MultiRayShape : public Shape
  {
    /// \brief Constructor
    public: MultiRayShape(Geom *parent);
  
    /// \brief Destructor
    public: virtual ~MultiRayShape();

    /// \brief Load a multi-ray shape from xml file
    public: void Load(XMLConfigNode *node);

    /// \brief Save child parameters
    public: virtual void Save(std::string &prefix, std::ostream &stream);

    /*public: void Load(unsigned int vertRayCount, unsigned int rayCount,
                      Vector3 origin, double minRange, double maxRange,
                      Angle minVertAngle, Angle maxVertAngle,
                      Angle minAngle, Angle maxAngle );
                      */
            
  
    /// \brief Get detected range for a ray.
    /// \returns Returns DBL_MAX for no detection.
    public: double GetRange(int index);
  
    /// \brief Get detected retro (intensity) value for a ray.
    public: double GetRetro(int index);
  
    /// \brief Get detected fiducial value for a ray.
    public: int GetFiducial(int index);

    /// \brief Get the minimum angle
    public: Angle GetMinAngle() const;
            
    /// \brief Get the maximum angle
    public: Angle GetMaxAngle() const;

    /// \brief Get the minimum range
    public: double GetMinRange() const;

    /// \brief Get the maximum range
    public: double GetMaxRange() const;

    /// \brief Get the range resolution
    public: double GetResRange() const;

    /// \brief Get the ray count
    public: int GetRayCount() const;

    /// \brief Get the range count
    public: int GetRangeCount() const;

    /// \brief Get the vertical scan line count
    public: int GetVerticalRayCount() const;

    /// \brief Get the vertical scan line count
    public: int GetVerticalRangeCount() const;

    /// \brief Get the vertical min angle
    public: Angle GetVerticalMinAngle() const;

    /// \brief Get the vertical max angle
    public: Angle GetVerticalMaxAngle() const;

    /// \brief Update the geom
    public: void Update();
  
     /// \brief Physics engine specific method for updating the rays
    protected: virtual void UpdateRays() = 0;
  
    /// \brief Add a ray to the geom
    protected: virtual void AddRay(const Vector3 &start, const Vector3 &end );
  
    /// Ray data
    protected: std::vector< RayShape* > rays;

    protected: double maxRange;

    protected: ParamT<Angle> *minAngleP, *maxAngleP;
    protected: ParamT<double> *minRangeP, *maxRangeP, *resRangeP;
    protected: ParamT<Vector3> *originP;
    protected: ParamT<int> *rayCountP;
    protected: ParamT<int> *rangeCountP;

  
    // For ray blocks such as Velodyne
    protected: ParamT<int> *verticalRayCountP;
    protected: ParamT<int> *verticalRangeCountP;
    protected: ParamT<Angle> *verticalMinAngleP;
    protected: ParamT<Angle> *verticalMaxAngleP;
  };

}

#endif
