#include <lpacpi/defblock.h>

#include <format>

namespace lpacpi {

static void print_indent(usz indent, std::basic_ostream<c8>& stream);
static void print_indented(usz indent, const std::string& message, std::basic_ostream<c8>& stream);
static std::string char_array_to_string(const u8* array, usz length);

static void print_indent(usz indent, std::basic_ostream<c8>& stream) {
    stream << std::string(indent, ' ');
}

static void print_indented(usz indent, const std::string& message, std::basic_ostream<c8>& stream) {
    print_indent(indent, stream);
    stream << message;
}

static std::string char_array_to_string(const u8* array, usz length) {
    return std::string { reinterpret_cast<const c8*>(array), length };
}

void dump(const definition_block_header& value, usz indent, std::basic_ostream<c8>& stream) {
    print_indented(indent, "definition block header { \n", stream);
    usz next_indent = indent + 2;
    auto* signature_characters = reinterpret_cast<const u8*>(&value.table_signature);
    print_indented(next_indent, std::format("table signature: {}\n", char_array_to_string(signature_characters, 4)), stream);
    print_indented(next_indent, std::format("table length: 0x{:08x}\n", value.table_length), stream);
    print_indented(next_indent, std::format("revision: {}\n", value.revision), stream);
    print_indented(next_indent, std::format("checksum: 0x{:02x}\n", value.checksum), stream);
    print_indented(next_indent, std::format("oem id: {}\n", char_array_to_string(value.oem_id, 6)), stream);
    print_indented(next_indent, std::format("oem table id: {}\n", char_array_to_string(value.oem_table_id, 8)), stream);
    print_indented(next_indent, std::format("oem revision: 0x{:08x}\n", value.oem_revision), stream);
    print_indented(next_indent, std::format("creator id: 0x{:08x}\n", value.creator_id), stream);
    print_indented(next_indent, std::format("creator revision: 0x{:08x}\n", value.creator_revision), stream);
    print_indented(indent, "} \n", stream);
}

} // namespace lpacpi
