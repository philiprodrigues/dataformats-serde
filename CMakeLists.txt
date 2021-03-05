cmake_minimum_required(VERSION 3.12)
project(dataformats-serde VERSION 1.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(dataformats REQUIRED)
find_package(serialization REQUIRED)

##############################################################################
# Main library

daq_add_library(LINK_LIBRARIES serialization::serialization dataformats::dataformats)

##############################################################################
# Unit Tests

daq_add_unit_test(FragmentSerDe_test                LINK_LIBRARIES dataformats-serde)
daq_add_unit_test(TriggerRecordHeaderSerDe_test     LINK_LIBRARIES dataformats-serde)

##############################################################################

daq_install()
