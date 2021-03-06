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
/*
 * Desc: Factory for creating controllers
 * Author: Nate Koenig
 * Date: 06 May 2007
 * SVN info: $Id: ControllerFactory.hh 7037 2008-09-24 18:03:52Z natepak $
 */

#ifndef CONTROLLERFACTORY_HH
#define CONTROLLERFACTORY_HH

#include <string>
#include <map>
#include "StaticPluginRegister.hh"

namespace gazebo
{

/// \addtogroup gazebo_controller
/// \brief Factory for creating controllers
/// \{

// Forward declarations
class Controller;
class Entity;


/// Prototype for controller factory functions
typedef Controller* (*ControllerFactoryFn) (Entity *parent);


/// \brief The controller factory; the class is just for namespacing purposes.
class ControllerFactory
{
  /// \brief Register a controller class 
  /// (called by controller registration function).
  public: static void RegisterController(std::string type, std::string classname, ControllerFactoryFn factoryfn);

  /// \brief Create a new instance of a controller.  Used by the world when
  /// reading the world file.
  public: static Controller *NewController(const std::string &classname, Entity *parent);
  
  /// \brief Load a controller plugin. Used by Model and Sensor when creating controllers.
  public: static void LoadPlugin(const std::string &plugin, const std::string &classname);

  // A list of registered controller classes
  private: static std::map<std::string, ControllerFactoryFn> *controllers;

};


/// \brief Static controller registration macro
///
/// Use this macro to register controllers with the server.
/// \param name Controller type name, as it appears in the world file.
/// \param classname C++ class name for the controller.
#define GZ_REGISTER_STATIC_CONTROLLER(name, classname) \
Controller *New##classname(Entity *entity) \
{ \
  return new classname(entity); \
} \
void Register##classname() \
{\
  ControllerFactory::RegisterController("static", name, New##classname);\
}\
StaticPluginRegister Registered##classname (Register##classname);

/// \brief Dynamic controller registration macro
///
/// Use this macro to register plugin controllers with the server.
/// \param name Controller type name, as it appears in the world file.
/// \param classname C++ class name for the controller.
#define GZ_REGISTER_DYNAMIC_CONTROLLER(name, classname) \
Controller *New##classname(Entity *entity) \
{ \
  return new classname(entity); \
} \
extern "C" void RegisterPluginController(); \
void RegisterPluginController() \
{\
  ControllerFactory::RegisterController("dynamic", name, New##classname);\
}

/// \}
}

#endif
