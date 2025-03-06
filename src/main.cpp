#include "lpacpi/byte_stream.h"
#include <cstdlib>
#include <cstring>
#include <expected>
#include <filesystem>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <system_error>
#include <vector>

#include <lpacpi/common.h>
#include <lpacpi/defblock.h>

// FIXME: proper error reporting
std::expected<std::vector<u8>, std::string> read_binary_file(const std::filesystem::path& path) {
    std::error_code code {};
    usz file_size = std::filesystem::file_size(path, code);
    if (code)
        return std::unexpected { std::format("cannot read file size `{}` - {}", path.string(), std::strerror(code.value())) };

    // create resulting vector
    std::vector<u8> result {};
    result.resize(file_size);

    // read data into the vector
    std::ifstream file { path, std::ios::binary };
    if (!file)
        return std::unexpected { std::format("cannot read file `{}` - {}", path.string(), std::strerror(code.value())) };
    file.read(reinterpret_cast<c8*>(result.data()), file_size);
    return result;
}

int main(int, char**) {
    // read data
    auto maybe_table_data = read_binary_file("samples/DSDT");
    if (!maybe_table_data.has_value()) {
        std::cerr << "error: " << maybe_table_data.error() << "\n";
        return EXIT_FAILURE;
    }

    // create a stream to ease the further processing
    auto const& raw_table_data = maybe_table_data.value();
    lpacpi::byte_stream table_data { raw_table_data.data(), raw_table_data.size() };

    try {
        // dump header
        auto& block_header = table_data.get<lpacpi::definition_block_header>();
        lpacpi::dump(block_header);
    } catch (const lpacpi::byte_stream_exception& exception) {
        std::cerr << "exception occurred: " << exception.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
