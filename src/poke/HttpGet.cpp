#include "poke/HttpGet.hpp"

#include "emu/FileLimits.hpp"

#include <algorithm>
#include <curl/curl.h>
#include <memory>
#include <mutex>

namespace emulocke {
namespace {

constexpr long kMaxRedirects = 5;

size_t writeTo(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* out = static_cast<std::vector<uint8_t>*>(userdata);
    const size_t n = size * nmemb;
    if (n > kMaxImageFile - out->size()) {
        return 0;
    }
    out->insert(out->end(), ptr, ptr + n);
    return n;
}

void ensureCurl() {
    static std::once_flag once;
    std::call_once(once, [] { curl_global_init(CURL_GLOBAL_DEFAULT); });
}

bool isPng(const std::vector<uint8_t>& bytes) {
    static const uint8_t sig[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    return bytes.size() >= 8 && std::equal(std::begin(sig), std::end(sig), bytes.begin());
}

}  // namespace

std::optional<std::vector<uint8_t>> httpGetPng(const std::string& url) {
    ensureCurl();
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(curl_easy_init(), curl_easy_cleanup);
    if (!curl) {
        return std::nullopt;
    }
    std::vector<uint8_t> body;
    long code = 0;
    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_PROTOCOLS_STR, "https");
    curl_easy_setopt(curl.get(), CURLOPT_REDIR_PROTOCOLS_STR, "https");
    curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl.get(), CURLOPT_MAXREDIRS, kMaxRedirects);
    curl_easy_setopt(curl.get(), CURLOPT_MAXFILESIZE_LARGE, static_cast<curl_off_t>(kMaxImageFile));
    curl_easy_setopt(curl.get(), CURLOPT_CONNECTTIMEOUT, 5L);
    curl_easy_setopt(curl.get(), CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl.get(), CURLOPT_USERAGENT, "emulocke-sprite-cache/1");
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, writeTo);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYHOST, 2L);
    if (curl_easy_perform(curl.get()) != CURLE_OK) {
        return std::nullopt;
    }
    curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &code);
    if (code != 200 || !isPng(body)) {
        return std::nullopt;
    }
    return body;
}

}  // namespace emulocke
