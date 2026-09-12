#pragma once

#include <cstdint>
#include <span>
#include <string_view>

namespace emulocke {

enum class TitleKind { Baseline, Hack };

struct CatalogTitle {
    const char* uuid;
    const char* slug;
    const char* title;
    const char* fullName;
    TitleKind kind;
    const char* ext;
    const char* sha1;
    const char* code;
    uint8_t revision;
    const char* prerequisiteUuid;
    const char* patchAsset;
};

inline constexpr const char* kFireRedUs10Uuid = "e8e92ba8-429b-55a0-b78d-2c269b6d2b56";
inline constexpr const char* kRadicalRedUuid = "b395cc4c-f482-5b62-865f-3b7e78899024";
inline constexpr const char* kUnboundUuid = "55498517-2419-5cd9-8a01-bd787a53c8dd";

std::span<const CatalogTitle> catalogTitles();
const CatalogTitle* catalogByUuid(std::string_view uuid);
const CatalogTitle* catalogBySha1(std::string_view sha1);
const CatalogTitle* catalogBySlug(std::string_view slug);

}