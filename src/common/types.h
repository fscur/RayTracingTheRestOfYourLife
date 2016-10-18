#pragma once
#define GLM_FORCE_RADIANS

#include <vector>
#include <string>
#include <codecvt>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using ivec3 = glm::ivec3;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using ulong = unsigned long;
using uint = unsigned int;
using byte = unsigned char;

const float π = glm::pi<float>();
const float π_times_2 = glm::two_pi<float>();
const float π_over_2 = glm::half_pi<float>();
const float π_over_4 = glm::quarter_pi<float>();
const float π¯¹ = glm::one_over_pi<float>();

#undef max
#undef min

const float MAX_FLOAT = std::numeric_limits<float>().max();
const float MIN_FLOAT = std::numeric_limits<float>().lowest();

template<typename T>
bool contains(std::vector<T> vector, T value)
{
    auto it = std::find(vector.begin(), vector.end(), value);

    return it != vector.end();
}

inline std::wstring s2ws(const std::string& str)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

inline std::string ws2s(const std::wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}