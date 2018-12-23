



#include "CrossSection.hpp"




void CrossSectionBase::Clear() {
   pts.clear();
}



CrossSectionBase::CrossSectionBase(const SpatialInfo& spatial_info) :
      info(spatial_info),
      pts()
{}


