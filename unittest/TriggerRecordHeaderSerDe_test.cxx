/**
 * @file TriggerRecordHeader_test.cxx TriggerRecordHeader class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dataformats-serde/TriggerRecordHeaderSerDe.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerRecordHeaderSerDe_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::dataformats;

BOOST_AUTO_TEST_SUITE(TriggerRecordHeaderSerDe_test)

BOOST_AUTO_TEST_CASE(Header_SerDes_MsgPack)
{
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.apa_number = 1;
  components.back().component.link_number = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.apa_number = 5;
  components.back().component.link_number = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  auto header = new TriggerRecordHeader(components);
  header->set_run_number(9);
  header->set_trigger_number(10);
  header->set_trigger_timestamp(11);
  header->set_trigger_type(12);
  header->set_error_bit(TriggerRecordErrorBits::kMismatch, true);
  header->set_error_bit(TriggerRecordErrorBits::kUnassigned3, true);

  auto bytes = dunedaq::serialization::serialize(*header, dunedaq::serialization::kMsgPack);
  TriggerRecordHeader& header_orig = *header;
  TriggerRecordHeader header_deserialized = dunedaq::serialization::deserialize<TriggerRecordHeader>(bytes);

  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_number(), header_deserialized.get_trigger_number());
  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_timestamp(), header_deserialized.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(header_orig.get_num_requested_components(), header_deserialized.get_num_requested_components());
  BOOST_REQUIRE_EQUAL(header_orig.get_run_number(), header_deserialized.get_run_number());
  BOOST_REQUIRE_EQUAL(header_orig.get_error_bits(), header_deserialized.get_error_bits());
  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_type(), header_deserialized.get_trigger_type());
  BOOST_REQUIRE_EQUAL(header_orig.get_total_size_bytes(), header_deserialized.get_total_size_bytes());
  BOOST_REQUIRE_EQUAL(header_orig.at(0).window_begin, header_deserialized.at(0).window_begin);
  BOOST_REQUIRE_EQUAL(header_orig.at(1).window_begin, header_deserialized.at(1).window_begin);
}

/**
 * @brief Check that TriggerRecordHeader serialization via MsgPack works
 */
BOOST_AUTO_TEST_CASE(Header_SerDes_JSON)
{
  std::vector<ComponentRequest> components;
  components.emplace_back();
  components.back().component.apa_number = 1;
  components.back().component.link_number = 2;
  components.back().window_begin = 3;
  components.back().window_end = 4;
  components.emplace_back();
  components.back().component.apa_number = 5;
  components.back().component.link_number = 6;
  components.back().window_begin = 7;
  components.back().window_end = 8;

  auto header = new TriggerRecordHeader(components);
  header->set_run_number(9);
  header->set_trigger_number(10);
  header->set_trigger_timestamp(11);
  header->set_trigger_type(12);
  header->set_error_bit(TriggerRecordErrorBits::kMismatch, true);
  header->set_error_bit(TriggerRecordErrorBits::kUnassigned3, true);

  auto bytes = dunedaq::serialization::serialize(*header, dunedaq::serialization::kJSON);
  TriggerRecordHeader& header_orig = *header;
  TriggerRecordHeader header_deserialized = dunedaq::serialization::deserialize<TriggerRecordHeader>(bytes);

  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_number(), header_deserialized.get_trigger_number());
  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_timestamp(), header_deserialized.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(header_orig.get_num_requested_components(), header_deserialized.get_num_requested_components());
  BOOST_REQUIRE_EQUAL(header_orig.get_run_number(), header_deserialized.get_run_number());
  BOOST_REQUIRE_EQUAL(header_orig.get_error_bits(), header_deserialized.get_error_bits());
  BOOST_REQUIRE_EQUAL(header_orig.get_trigger_type(), header_deserialized.get_trigger_type());
  BOOST_REQUIRE_EQUAL(header_orig.get_total_size_bytes(), header_deserialized.get_total_size_bytes());
  BOOST_REQUIRE_EQUAL(header_orig.at(0).window_begin, header_deserialized.at(0).window_begin);
  BOOST_REQUIRE_EQUAL(header_orig.at(1).window_begin, header_deserialized.at(1).window_begin);
}

BOOST_AUTO_TEST_SUITE_END()
