#pragma once
#include <iostream>
#include <ostream>
#include <string>

#include <lpacpi/common.h>

namespace lpacpi {

struct [[gnu::packed]] definition_block_header {
    u32 table_signature;
    u32 table_length;
    u8 revision;
    u8 checksum;
    u8 oem_id[6];
    u8 oem_table_id[8];
    u32 oem_revision;
    u32 creator_id;
    u32 creator_revision;
    u8 table_data[1];
};

void dump(const definition_block_header& value, usz indent = 0, std::basic_ostream<c8>& stream = std::cout);

} // namespace lpacpi
