/* -*-  mode: c++; indent-tabs-mode: nil -*- */

/*
  Specifies a value on the surface from the value in the cell just below the
  surface.

  Authors: Ethan Coon (ecoon@lanl.gov)
*/

#include "boost/algorithm/string/predicate.hpp"


#include "surface_top_cells_evaluator.hh"

namespace Amanzi {
namespace Relations {


SurfaceTopCellsEvaluator::SurfaceTopCellsEvaluator(Teuchos::ParameterList& plist) :
    SecondaryVariableFieldEvaluator(plist) {
  if (boost::starts_with(my_key_, "surface"))
    dependency_key_ = plist_.get<std::string>("subsurface key", my_key_.substr(8,my_key_.size()));
  else
    dependency_key_ = plist_.get<std::string>("subsurface key");
  dependencies_.insert(dependency_key_);
}

SurfaceTopCellsEvaluator::SurfaceTopCellsEvaluator(const SurfaceTopCellsEvaluator& other) :
    SecondaryVariableFieldEvaluator(other),
    dependency_key_(other.dependency_key_) {}

Teuchos::RCP<FieldEvaluator>
SurfaceTopCellsEvaluator::Clone() const {
  return Teuchos::rcp(new SurfaceTopCellsEvaluator(*this));
}

// Required methods from SecondaryVariableFieldEvaluator
void
SurfaceTopCellsEvaluator::EvaluateField_(const Teuchos::Ptr<State>& S,
        const Teuchos::Ptr<CompositeVector>& result) {
  Teuchos::RCP<const CompositeVector> sub_vector = S->GetFieldData(dependency_key_);
  const Epetra_MultiVector& sub_vector_cells = *sub_vector->ViewComponent("cell",false);
  Epetra_MultiVector& result_cells = *result->ViewComponent("cell",false);


  int ncells_surf = result->Mesh()->num_entities(AmanziMesh::CELL,
          AmanziMesh::OWNED);
  for (unsigned int c=0; c!=ncells_surf; ++c) {
    // get the face on the subsurface mesh
    AmanziMesh::Entity_ID f = result->Mesh()->entity_get_parent(AmanziMesh::CELL, c);

    // get the cell interior to the face
    AmanziMesh::Entity_ID_List cells;
    sub_vector->Mesh()->face_get_cells(f, AmanziMesh::USED, &cells);
    ASSERT(cells.size() == 1);

    result_cells[0][c] = sub_vector_cells[0][cells[0]];
  }
}


void
SurfaceTopCellsEvaluator::EnsureCompatibility(const Teuchos::Ptr<State>& S) {
  // Ensure my field exists.  Requirements should be already set.  Claim ownership.
  ASSERT(!my_key_.empty());
  Teuchos::RCP<CompositeVectorSpace> my_fac = S->RequireField(my_key_, my_key_);

  // check plist for vis or checkpointing control
  bool io_my_key = plist_.get<bool>(std::string("visualize ")+my_key_, true);
  S->GetField(my_key_, my_key_)->set_io_vis(io_my_key);
  bool checkpoint_my_key = plist_.get<bool>(std::string("checkpoint ")+my_key_, false);
  S->GetField(my_key_, my_key_)->set_io_checkpoint(checkpoint_my_key);
}



} //namespace
} //namespace

