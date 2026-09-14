#include "poke/SpriteIndex.hpp"
#include "test/Check.hpp"

#include <string>
#include <string_view>

namespace {

bool onlySlugBytes(std::string_view slug) {
    for (const char c : slug) {
        const bool letter = (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
        if (!letter && c != '-') {
            return false;
        }
    }
    return true;
}

}  // namespace

void testSlugAllowlist() {
    using emulocke::normalizeSlug;
    REQUIRE(normalizeSlug("MR. MIME") == "mr-mime");
    REQUIRE(normalizeSlug("FARFETCH'D") == "farfetchd");
    REQUIRE(normalizeSlug("muk-alola") == "muk-alola");
    REQUIRE(normalizeSlug("Walking_Wake") == "walking-wake");
    REQUIRE(normalizeSlug("a--b  c") == "a-b-c");
    REQUIRE(normalizeSlug("-----").empty());
    REQUIRE(normalizeSlug("../../etc/passwd") == "etcpasswd");
    REQUIRE(normalizeSlug("..\\..\\windows") == "windows");
    REQUIRE(normalizeSlug("pikachu/../../x") == "pikachux");
    REQUIRE(normalizeSlug(std::string_view("nul:\0evil", 9)) == "nulevil");
    REQUIRE(normalizeSlug("Flab\xC3\xA9" "b\xC3\xA9") == "flabb");
    REQUIRE(normalizeSlug("%2e%2e%2f") == "2e2e2f");
    const std::string hostile = "\x7f\x80\xff ~`!@#$%^&*()+={}[]|;:\"<>,?/";
    REQUIRE(normalizeSlug(hostile).empty());
    REQUIRE(onlySlugBytes(normalizeSlug("Z\xE2\x80\x8Bombie Cat")));
    REQUIRE(emulocke::speciesSlug("???").empty());
    REQUIRE(emulocke::speciesSlug("-----").empty());
}
