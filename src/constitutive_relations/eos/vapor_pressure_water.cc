/* -*-  mode: c++; c-default-style: "google"; indent-tabs-mode: nil -*- */

/*
  ATS

  Saturated Vapor Pressure for vapor over water or ice, Sonntag (1990)

  Authors: Ethan Coon (ecoon@lanl.gov)
*/

#include <cmath>
#include "errors.hh"
#include "vapor_pressure_water.hh"

namespace Amanzi {
namespace Relations {

// registry of method
Utils::RegisteredFactory<VaporPressureRelation,VaporPressureWater> VaporPressureWater::factory_("water vapor over water/ice");

VaporPressureWater::VaporPressureWater(Teuchos::ParameterList& plist) :
  plist_(plist),
  ka0_(16.635764),
  ka_(-6096.9385),
  kb_(-2.7111933e-2),
  kc_(1.673952e-5),
  kd_(2.433502) {}

double VaporPressureWater::SaturatedVaporPressure(double T) {
  if (T < 100. || T > 373.0) {
    std::cout << "Invalid temperature, T = " << T << std::endl;
    Errors::Message m("Cut time step");
    Exceptions::amanzi_throw(m);
  }
  return 100.0*exp(ka0_ + ka_/T + (kb_ + kc_*T)*T + kd_*log(T));
};

double VaporPressureWater::DSaturatedVaporPressureDT(double T) {
  if (T < 100. || T > 373.0) {
    std::cout << "Invalid temperature, T = " << T << std::endl;
    Errors::Message m("Cut time step");
    Exceptions::amanzi_throw(m);
  }
  return SaturatedVaporPressure(T) * (-ka_/(T*T) + kb_ + 2.0*kc_*T + kd_/T);
};


} //namespace
} //namespace
