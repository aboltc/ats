/* -*-  mode: c++; c-default-style: "google"; indent-tabs-mode: nil -*- */
//! PresElevEvaluator: evaluates h + z

/*
  ATS is released under the three-clause BSD License. 
  The terms of use and "as is" disclaimer for this license are 
  provided in the top-level COPYRIGHT file.

  Authors: Ethan Coon (ecoon@lanl.gov)
*/

/*!
Evaluator type: ""

.. math::
  h + z

* `"my key`" ``[string]`` **pres_elev** Names the surface water potential variable, h + z [m]
* `"height key`" ``[string]`` **ponded_depth** Names the height variable. [m]
* `"elevation key`" ``[string]`` **elevation** Names the elevation variable. [m]


NOTE: This is a legacy evaluator, and is not in the factory, so need not be in
the input spec.  However, we include it here because this could easily be
abstracted for new potential surfaces, kinematic wave, etc, at which point it
would need to be added to the factory and the input spec.

NOTE: This could easily be replaced by a generic AdditiveEvaluator_

*/

#ifndef AMANZI_FLOWRELATIONS_FRACTIONAL_CONDUCTANCE_EVALUATOR_
#define AMANZI_FLOWRELATIONS_FRACTIONAL_CONDUCTANCE_EVALUATOR_

#include "factory.hh"
#include "secondary_variable_field_evaluator.hh"

namespace Amanzi {
namespace Flow {
namespace FlowRelations {

class FractionalConductanceEvaluator : public SecondaryVariableFieldEvaluator {

 public:
  explicit
  FractionalConductanceEvaluator(Teuchos::ParameterList& plist);

  FractionalConductanceEvaluator(const FractionalConductanceEvaluator& other);

  Teuchos::RCP<FieldEvaluator> Clone() const;
  
  // Required methods from SecondaryVariableFieldEvaluator
  virtual void EvaluateField_(const Teuchos::Ptr<State>& S,
          const Teuchos::Ptr<CompositeVector>& result);
  virtual void EvaluateFieldPartialDerivative_(const Teuchos::Ptr<State>& S,
          Key wrt_key, const Teuchos::Ptr<CompositeVector>& result);

 private:
  double maxpd_depth_, depr_depth_, delta_ex_, delta_max_;
  Key pdd_key_, pd_key_, vpd_key_;
  Key depr_depth_key_, delta_ex_key_, delta_max_key_;

 private:
  static Utils::RegisteredFactory<FieldEvaluator,FractionalConductanceEvaluator> factory_;
};

} //namespace
} //namespace
} //namespace

#endif
