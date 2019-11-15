#ifndef OPERATORS_H
#define OPERATORS_H

#include <vector>
#include <map>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "tracker_ptr.h"

namespace gdf {
namespace kernel {
class Hierarchy;
class Component;
enum class GoTag;
enum class GoLayer;
}

namespace temporal {
enum class ChronoPlayStatus;
}

}

std::ostream& operator<<( std::ostream& out, sf::Time time );
std::ostream& operator<<( std::ostream &os, sf::Vector2f const &v);
std::ostream& operator<<( std::ostream &os, gdf::kernel::Hierarchy const &h);
std::ostream& operator<<( std::ostream &os, gdf::kernel::tracker_ptr< gdf::kernel::Hierarchy> const &h);
std::ostream& operator<<(std::ostream &os, gdf::kernel::GoTag const &h);
std::ostream& operator<<(std::ostream &os, gdf::kernel::GoLayer const &h);

std::ostream& operator<<(std::ostream &os, gdf::temporal::ChronoPlayStatus const &h);

#endif // OPERATORS_H
