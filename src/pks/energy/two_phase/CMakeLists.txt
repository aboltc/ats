# -*- mode: cmake -*-
include_directories(${ATS_SOURCE_DIR}/src/pks)
include_directories(${ATS_SOURCE_DIR}/src/constitutive_relations/eos)
include_directories(${ATS_SOURCE_DIR}/src/factory)
include_directories(${ATS_SOURCE_DIR}/src/pks/bc_factory)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/bc_factory)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/base)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/constitutive_relations/thermal_conductivity)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/constitutive_relations/enthalpy)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/constitutive_relations/internal_energy)
include_directories(${ATS_SOURCE_DIR}/src/pks/energy/constitutive_relations/energy)
include_directories(${ATS_SOURCE_DIR}/src/operators/advection)
include_directories(${ATS_SOURCE_DIR}/src/operators/divgrad)
include_directories(${ATS_SOURCE_DIR}/src/operators/divgrad/upwind_scheme)

add_library(pk_energy_two_phase
  two_phase.cc)

install(TARGETS pk_energy_two_phase DESTINATION lib)

# if ( BUILD_TESTS )
#   set(pk_factory -Wl,--whole-archive pk_factory -Wl,--no-whole-archive)

#   include_directories(${Amanzi_TPL_UnitTest_INCLUDE_DIRS})

#   include_directories(${ATS_SOURCE_DIR}/src/pks/energy/two_phase)

#   # Test: miscaleneous transport routines
#   add_executable(two_phase_test test/Main.cc test/energy_test_class.cc test/two_phase_advance_simple.cc)
#   target_link_libraries(two_phase_test ${pk_factory} amanzi_data_structures pk_energy_two_phase energy_bc_factory ${energy_relations_thermal_conductivity} energy_relations_internal_energy advection divgrad amanzi_solvers amanzi_time_integration amanzi_whetstone amanzi_mesh amanzi_geometry amanzi_mesh_functions amanzi_mesh_factory amanzi_input amanzi_output amanzi_data_structures amanzi_state ${Amanzi_TPL_UnitTest_LIBRARIES})

# endif()

