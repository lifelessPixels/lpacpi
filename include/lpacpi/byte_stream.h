#pragma once
#include <exception>
#include <span>
#include <string>
#include <vector>

#include <lpacpi/common.h>

namespace lpacpi {

class byte_stream_exception : std::exception {
public:
    explicit byte_stream_exception(std::string what);
    virtual const char* what() const noexcept override;

private:
    std::string m_what {};
};

class byte_stream {
public:
    explicit byte_stream(std::vector<u8> data);
    byte_stream(const u8* data, usz size);

    usz size() const;
    usz remaining_bytes() const;
    u8 byte_at(usz index) const;

    template <typename T>
    const T& get() {
        return *reinterpret_cast<T*>(get_internal(sizeof(T)));
    }

    template <typename T>
    std::span<const T> get_span(usz count) {
        return std::span<T> { reinterpret_cast<const T*>(get_internal(sizeof(T) * count)), count };
    }

private:
    void* get_internal(usz size);

    std::vector<u8> m_data {};
    usz m_current_position { 0 };
};

} // namespace lpacpi
