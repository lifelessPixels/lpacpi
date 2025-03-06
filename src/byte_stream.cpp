#include <format>
#include <lpacpi/byte_stream.h>

#include <utility>
#include <vector>

namespace lpacpi {

byte_stream_exception::byte_stream_exception(std::string what) : m_what(std::move(what)) {}

const char* byte_stream_exception::what() const noexcept { return m_what.c_str(); }

byte_stream::byte_stream(std::vector<u8> data) : m_data(std::move(data)) {}

byte_stream::byte_stream(const u8* data, usz size) : m_data(data, data + size) {}

usz byte_stream::size() const { return m_data.size(); }

usz byte_stream::remaining_bytes() const { return m_data.size() - m_current_position; }

u8 byte_stream::byte_at(usz index) const {
    if (index >= m_data.size())
        throw byte_stream_exception { std::format("index out of range, requested byte {} but the size is {}", index, m_data.size()) };
    return m_data[index];
}

void* byte_stream::get_internal(usz size) {
    if (size > remaining_bytes())
        throw byte_stream_exception { std::format("stream overrun, requested {} bytes, but {} were available", size, remaining_bytes()) };

    // get data and return it
    void* data = m_data.data();
    m_current_position += size;
    return data;
}

} // namespace lpacpi
