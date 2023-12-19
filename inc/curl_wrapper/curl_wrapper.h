#pragma once

#include <memory>
#include <string>
#include <curl/curl.h>

class Curl
{
public:
    Curl(): m_curlPtr(std::move(std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>(curl_easy_init(), curl_easy_cleanup)))
    {
    }

    void SetUrl(const std::string& url) {
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_URL, url.c_str());
    }

    void SetUserAgent(const std::string& user_agent) {
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_USERAGENT, user_agent.c_str());
    }

    void SetTimeout(int timeout_secs) {
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_TIMEOUT, timeout_secs);
    }

    void SetFollowLocation(bool follow) {
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_FOLLOWLOCATION, follow ? 1L : 0L);
    }

    std::string Execute() {
        std::string response;
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_WRITEFUNCTION, &WriteResponse);
        curl_easy_setopt(m_curlPtr.get(), CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(m_curlPtr.get());
        return response;
    }
private:
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> m_curlPtr;

    static size_t WriteResponse(void* ptr, size_t size, size_t nmemb, void* userdata) {
        size_t real_size = size * nmemb;
        std::string* response = static_cast<std::string*>(userdata);
        response->append(static_cast<char*>(ptr), real_size);
        return real_size;
    }
};