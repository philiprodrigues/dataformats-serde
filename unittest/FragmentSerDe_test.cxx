/**
 * @file Fragment_test.cxx Fragment class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dataformats-serde/FragmentSerDe.hpp"
#include "serialization/Serialization.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE FragmentSerDe_test // NOLINT

#include "boost/test/unit_test.hpp"
#include "boost/test/data/test_case.hpp"

#include <string>
#include <utility>
#include <vector>

using namespace dunedaq::dataformats;

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)


BOOST_DATA_TEST_CASE(SerDe, boost::unit_test::data::make({dunedaq::serialization::kMsgPack, dunedaq::serialization::kJSON}))
{
  FragmentHeader header;
  header.size = sizeof(FragmentHeader) + 4;
  header.trigger_number = 1;
  header.trigger_timestamp = 2;
  header.run_number = 3;

  auto frag = malloc(sizeof(FragmentHeader) + 4);
  memcpy(frag, &header, sizeof(FragmentHeader));

  uint8_t one = 1, two = 2, three = 3, four = 4;                               // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader), &one, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 1, &two, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 2, &three, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 3, &four, 1);  // NOLINT(build/unsigned)

  Fragment test_frag(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto bytes = dunedaq::serialization::serialize(test_frag, sample);

  Fragment frag_deserialized = dunedaq::serialization::deserialize<Fragment>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_number(), test_frag.get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_run_number(), test_frag.get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_trigger_timestamp(), test_frag.get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_begin(), test_frag.get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_window_end(), test_frag.get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().link_number, test_frag.get_link_id().link_number);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_link_id().apa_number, test_frag.get_link_id().apa_number);
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_error_bits(), test_frag.get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_fragment_type_code(), test_frag.get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized.get_size(), test_frag.get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 0),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 0));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 1),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 1));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized.get_data()) + 2),
                      *(static_cast<uint8_t*>(test_frag.get_data()) + 2));
}

BOOST_DATA_TEST_CASE(SerDe_UniquePtr, boost::unit_test::data::make({dunedaq::serialization::kMsgPack, dunedaq::serialization::kJSON}))
{
  FragmentHeader header;
  header.size = sizeof(FragmentHeader) + 4;
  header.trigger_number = 1;
  header.trigger_timestamp = 2;
  header.run_number = 3;

  auto frag = malloc(sizeof(FragmentHeader) + 4);
  memcpy(frag, &header, sizeof(FragmentHeader));

  uint8_t one = 1, two = 2, three = 3, four = 4;                               // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader), &one, 1);       // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 1, &two, 1);   // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 2, &three, 1); // NOLINT(build/unsigned)
  memcpy(static_cast<uint8_t*>(frag) + sizeof(FragmentHeader) + 3, &four, 1);  // NOLINT(build/unsigned)

  auto test_frag_ptr=std::make_unique<Fragment>(frag, Fragment::BufferAdoptionMode::kTakeOverBuffer);
  auto bytes = dunedaq::serialization::serialize(test_frag_ptr, sample);

  std::unique_ptr<Fragment> frag_deserialized_ptr = dunedaq::serialization::deserialize<std::unique_ptr<Fragment>>(bytes);

  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_trigger_number(),      test_frag_ptr->get_trigger_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_run_number(),          test_frag_ptr->get_run_number());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_trigger_timestamp(),   test_frag_ptr->get_trigger_timestamp());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_window_begin(),        test_frag_ptr->get_window_begin());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_window_end(),          test_frag_ptr->get_window_end());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_link_id().link_number, test_frag_ptr->get_link_id().link_number);
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_link_id().apa_number,  test_frag_ptr->get_link_id().apa_number);
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_error_bits(),          test_frag_ptr->get_error_bits());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_fragment_type_code(),  test_frag_ptr->get_fragment_type_code());
  BOOST_REQUIRE_EQUAL(frag_deserialized_ptr->get_size(),                test_frag_ptr->get_size());

  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized_ptr->get_data()) + 0),
                      *(static_cast<uint8_t*>(test_frag_ptr->get_data()) + 0));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized_ptr->get_data()) + 1),
                      *(static_cast<uint8_t*>(test_frag_ptr->get_data()) + 1));
  BOOST_REQUIRE_EQUAL(*(static_cast<uint8_t*>(frag_deserialized_ptr->get_data()) + 2),
                      *(static_cast<uint8_t*>(test_frag_ptr->get_data()) + 2));
}

BOOST_AUTO_TEST_SUITE_END()
