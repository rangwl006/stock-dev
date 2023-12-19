#include <filesystem>

#include <cpr/cpr.h>
#include <cpr/api.h>
#include <cpr/session.h>
#include "curl_wrapper/curl_wrapper.h"
#include "data_updater/data_updater.h"

namespace core
{

    bool DataUpdater::real_write_data(std::string data, intptr_t userdata)
    {
        std::cout << "DataUpdater::real_write_data\n";
        // NOLINTNEXTLINE (cppcoreguidelines-pro-type-reinterpret-cast)
        std::string* dst = reinterpret_cast<std::string*>(userdata);
        *dst += data;
        return true;
    }

    bool write_data(std::string data, intptr_t userdata)
    {
        std::cout << "DataUpdater::real_write_data\n";
        // NOLINTNEXTLINE (cppcoreguidelines-pro-type-reinterpret-cast)
        std::string* dst = reinterpret_cast<std::string*>(userdata);
        *dst += data;
        return true;
    }

    DataUpdater::DataUpdater(std::string_view path) : _apiKeyPath(path)
    {
        if (! std::filesystem::exists(std::filesystem::path(_apiKeyPath)))
        {
            throw std::exception("API Key path does not exist!");
        }
    }

    void DataUpdater::updateTickers(std::string_view exchange, std::string_view format, std::string_view delimiter)
    {
        twelvedata::Request<twelvedata::StocksEndpoint> req;
        req.endpointPrefix = twelvedata::EndpointPrefix("https://api.twelvedata.com");
        req.params.optionalParams["exchange"] = exchange;
        req.params.optionalParams["type"] = "common%20stock";
        req.params.optionalParams["format"] = format;
        req.params.optionalParams["delimiter"] = delimiter;

        auto request_string = m_stockRequestBuilder.buildRequest(req);
//        Curl c;
//        c.SetUrl(request_string);
        request_string.pop_back();
        std::cout <<request_string << std::endl;
        cpr::Url url{request_string};
        cpr::Session session;
        session.SetUrl(url);
        std::string strFileData;
        cpr::Response response = session.Download(cpr::WriteCallback{write_data, (intptr_t) &strFileData});
        std::cout << "status code: " << response.status_code << std::endl;
        std::cout << std::setw(2) << strFileData << std::endl;
        std::cout << "End of update\n";
    }

    void DataUpdater::updateTickerData()
    {

    }
}