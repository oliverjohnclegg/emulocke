#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

enum class TitleKind { Baseline, Hack };

struct PatchOption {
    const char* id;
    const char* label;
    const char* asset;
};

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
    const PatchOption* options;
    uint8_t optionCount;
    const char* artSlug;
    const char* version;
    const char* details;
    const char* creator;
};

inline constexpr const char* kFireRedUs10Uuid = "e8e92ba8-429b-55a0-b78d-2c269b6d2b56";
inline constexpr const char* kFireRedUs11Uuid = "7dba07d2-93e3-5b45-9030-3a579e46ab7b";
inline constexpr const char* kLeafGreenUs10Uuid = "9f374685-6339-5285-a9e9-7953afa9802b";
inline constexpr const char* kLeafGreenUs11Uuid = "ca04c1af-7d8a-55c7-9cda-3467c0acad8f";
inline constexpr const char* kRubyUsUuid = "eab4efe2-cc77-56af-88cd-4115130df6d5";
inline constexpr const char* kRubyUs11Uuid = "ca337f0e-cd8c-5957-ab6d-3d29a800a955";
inline constexpr const char* kSapphireUsUuid = "19ec4964-eae6-58ee-8cfd-60c9937b1055";
inline constexpr const char* kEmeraldUsUuid = "61144433-b5d4-5b54-8123-7121990daaad";
inline constexpr const char* kDiamondUsUuid = "2ef1748f-beca-5b08-bc8f-6a3042489f37";
inline constexpr const char* kPearlUsUuid = "0dc2d28a-075f-5950-a2b8-58d75a18bc93";
inline constexpr const char* kPlatinumUsUuid = "c29b3366-ed5f-5ad5-8b13-b51473683ac4";
inline constexpr const char* kPlatinumUs11Uuid = "5a6a6479-503a-5487-b60f-1a70f0c471a3";
inline constexpr const char* kHeartGoldUsUuid = "56ce30d3-ae67-576b-b1c7-884713a59bbb";
inline constexpr const char* kSoulSilverUsUuid = "ecb7c95e-fe23-5008-b642-2d11f9487417";
inline constexpr const char* kBlackUsUuid = "478ce287-a3c6-5f18-b1e5-4d48acccecd8";
inline constexpr const char* kWhiteUsUuid = "3149da52-59e3-524d-a587-c70586434cf5";
inline constexpr const char* kBlack2UsUuid = "8634f4f3-c0ff-57eb-894c-fc94405678f0";
inline constexpr const char* kWhite2UsUuid = "832f8a89-aeab-5bbc-bcb9-61d63e53fa90";
inline constexpr const char* kRadicalRedUuid = "b395cc4c-f482-5b62-865f-3b7e78899024";
inline constexpr const char* kUnboundUuid = "55498517-2419-5cd9-8a01-bd787a53c8dd";
inline constexpr const char* kBlazeBlackUuid = "8057987b-cc3f-5e3a-92a0-84c3427376b4";
inline constexpr const char* kVoltWhiteUuid = "5d188885-ae0f-5759-9780-80dcee31f3e1";
inline constexpr const char* kVoltWhite2ReduxUuid = "ad0141a8-975f-50b3-b231-80bf1e5d54ee";
inline constexpr const char* kFireRedOmegaUuid = "8527a185-3f81-585d-8f7c-579ae609d3c5";
inline constexpr const char* kSacredGoldUuid = "3f9719ca-e87f-5424-aa02-af7865e10deb";
inline constexpr const char* kPlatinumKaizoUuid = "d8ae6094-3a98-5ce5-8be5-fe1c4ed9c252";
inline constexpr const char* kRenegadePlatinumUuid = "be106054-eaa8-54b2-9f58-0fd1e948031e";
inline constexpr const char* kRunAndBunUuid = "06639a36-2636-5be7-a9ea-8b297df14269";
inline constexpr const char* kInclementEmeraldUuid = "18855d7c-7171-59e2-82fd-03836a5b2f1c";
inline constexpr const char* kEmeraldKaizoUuid = "7d2136c6-bcbb-5764-ac94-f43f2d87dc1d";

std::span<const CatalogTitle> catalogTitles();
std::string catalogListTitle(const CatalogTitle& title);
int catalogVersionCompare(std::string_view a, std::string_view b);
std::vector<const CatalogTitle*> catalogPickerRows();
const CatalogTitle* catalogByUuid(std::string_view uuid);
const CatalogTitle* catalogBySha1(std::string_view sha1);
const CatalogTitle* catalogBySlug(std::string_view slug);
std::string_view catalogOptionId(const CatalogTitle& title, std::string_view requested);
const char* catalogPatchAsset(const CatalogTitle& title, std::string_view requested);

}
