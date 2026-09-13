#include "run/Catalog.hpp"

namespace emulocke {
namespace {

constexpr CatalogTitle kTitles[] = {
    {"eab4efe2-cc77-56af-88cd-4115130df6d5", "ruby-us", "RUBY", "Pokemon Ruby", TitleKind::Baseline,
        ".gba", "5b64eacf892920518db4ec664e62a086dd5f5bc8", "AXVE", 2, "", "", "ruby", "Rev 2", "US"},
    {"19ec4964-eae6-58ee-8cfd-60c9937b1055", "sapphire-us", "SAPPHIRE", "Pokemon Sapphire",
        TitleKind::Baseline, ".gba", "89b45fb172e6b55d51fc0e61989775187f6fe63c", "AXPE", 2, "", "",
        "sapphire", "Rev 2", "US"},
    {"61144433-b5d4-5b54-8123-7121990daaad", "emerald-us", "EMERALD", "Pokemon Emerald", TitleKind::Baseline,
        ".gba", "f3ae088181bf583e55daf962a92bb46f4f1d07b7", "BPEE", 0, "", "", "emerald", "", "US"},
    {kFireRedUs10Uuid, "firered-us-1.0", "FIRE RED", "Pokemon Fire Red", TitleKind::Baseline, ".gba",
        "41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc", "BPRE", 0, "", "", "firered", "1.0", "US"},
    {"7dba07d2-93e3-5b45-9030-3a579e46ab7b", "firered-us-1.1", "FIRE RED", "Pokemon Fire Red 1.1",
        TitleKind::Baseline, ".gba", "dd5945db9b930750cb39d00c84da8571feebf417", "BPRE", 1, "", "",
        "firered", "1.1", "US"},
    {"9f374685-6339-5285-a9e9-7953afa9802b", "leafgreen-us-1.0", "LEAF GREEN", "Pokemon Leaf Green",
        TitleKind::Baseline, ".gba", "574fa542ffebb14be69902d1d36f1ec0a4afd71e", "BPGE", 0, "", "",
        "leafgreen", "1.0", "US"},
    {"ca04c1af-7d8a-55c7-9cda-3467c0acad8f", "leafgreen-us-1.1", "LEAF GREEN", "Pokemon Leaf Green 1.1",
        TitleKind::Baseline, ".gba", "7862c67bdecbe21d1d69ce082ce34327e1c6ed5e", "BPGE", 1, "", "",
        "leafgreen", "1.1", "US"},
    {"2ef1748f-beca-5b08-bc8f-6a3042489f37", "diamond-us", "DIAMOND", "Pokemon Diamond", TitleKind::Baseline,
        ".nds", "a46233d8b79a69ea87aa295a0efad5237d02841e", "ADAE", 0, "", "", "diamond", "", "US"},
    {"0dc2d28a-075f-5950-a2b8-58d75a18bc93", "pearl-us", "PEARL", "Pokemon Pearl", TitleKind::Baseline, ".nds",
        "99083bf15ec7c6b81b4ba241ee10abd9e80999ac", "APAE", 0, "", "", "pearl", "", "US"},
    {"c29b3366-ed5f-5ad5-8b13-b51473683ac4", "platinum-us", "PLATINUM", "Pokemon Platinum", TitleKind::Baseline,
        ".nds", "ce81046eda7d232513069519cb2085349896dec7", "CPUE", 0, "", "", "platinum", "", "US"},
    {"56ce30d3-ae67-576b-b1c7-884713a59bbb", "heartgold-us", "HEART GOLD", "Pokemon Heart Gold",
        TitleKind::Baseline, ".nds", "4fcded0e2713dc03929845de631d0932ea2b5a37", "IPKE", 0, "", "",
        "heartgold", "", "US"},
    {"ecb7c95e-fe23-5008-b642-2d11f9487417", "soulsilver-us", "SOUL SILVER", "Pokemon Soul Silver",
        TitleKind::Baseline, ".nds", "f8dc38ea20c17541a43b58c5e6d18c1732c7e582", "IPGE", 0, "", "",
        "soulsilver", "", "US"},
    {"478ce287-a3c6-5f18-b1e5-4d48acccecd8", "black-us", "BLACK", "Pokemon Black", TitleKind::Baseline, ".nds",
        "26ad0b9967aa279c4a266ee69f52b9b2332399a5", "IRAO", 0, "", "", "black", "", "US"},
    {"3149da52-59e3-524d-a587-c70586434cf5", "white-us", "WHITE", "Pokemon White", TitleKind::Baseline, ".nds",
        "bc696a0dfb448c7b3a8a206f0f8214411a039208", "IRBO", 0, "", "", "white", "", "US"},
    {"8634f4f3-c0ff-57eb-894c-fc94405678f0", "black2-us", "BLACK 2", "Pokemon Black 2", TitleKind::Baseline,
        ".nds", "e51e6dfb8678a3d19dcd2a10691b96a569ca0abb", "IREO", 0, "", "", "black-2", "", "US"},
    {"832f8a89-aeab-5bbc-bcb9-61d63e53fa90", "white2-us", "WHITE 2", "Pokemon White 2", TitleKind::Baseline,
        ".nds", "b5d7490be7b415b8f1e672a53e978a9cc667e56a", "IRDO", 0, "", "", "white-2", "", "US"},
    {kRadicalRedUuid, "radical-red-4.1", "RADICAL RED", "Pokemon Radical Red", TitleKind::Hack, ".gba", "",
        "", 0, kFireRedUs10Uuid, "patches/b395cc4c-f482-5b62-865f-3b7e78899024.ups", "radical-red", "4.1",
        "US"},
    {kUnboundUuid, "unbound-2.1.1.1", "UNBOUND", "Pokemon Unbound", TitleKind::Hack, ".gba", "", "", 0,
        kFireRedUs10Uuid, "patches/55498517-2419-5cd9-8a01-bd787a53c8dd.ups", "unbound", "2.1.1.1", "US"},
};

}  // namespace

std::span<const CatalogTitle> catalogTitles() {
    return kTitles;
}

}
