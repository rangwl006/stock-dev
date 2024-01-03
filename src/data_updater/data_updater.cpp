#include <filesystem>
#include <fstream>
#include <chrono>
#include <string>

#include <cpr/cpr.h>
#include <cpr/api.h>
#include <cpr/session.h>
#include "curl_wrapper/curl_wrapper.h"
#include "data_updater/data_updater.h"
#include "utils/read_api_key.h"

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

    std::vector<std::string> DataUpdater::updateTickers(std::string_view exchange, std::string_view format, std::string_view delimiter)
    {
        twelvedata::Request<twelvedata::StocksEndpoint> req;
        req.endpointPrefix = twelvedata::EndpointPrefix("https://api.twelvedata.com");
        req.params.optionalParams["exchange"] = exchange;
        req.params.optionalParams["type"] = "common%20stock";
        req.params.optionalParams["format"] = format;
        req.params.optionalParams["delimiter"] = delimiter;

        auto request_string = m_stockRequestBuilder.buildRequest(req);
        request_string.pop_back();
        std::cout <<request_string << std::endl;
        cpr::Url url{request_string};
        cpr::Session session;
        session.SetUrl(url);
        std::string strFileData;
        cpr::Response response = session.Download(cpr::WriteCallback{write_data, (intptr_t) &strFileData});
        std::cout << "status code: " << response.status_code << std::endl;
        std::stringstream fileDataStream;
        fileDataStream << strFileData;
        std::string data;

        std::vector<std::string> res;

        while(std::getline(fileDataStream, data))
        {
            std::cout << "data: " << data << std::endl;
            std::string symbol;
            // Get index position of first quote in string
            size_t pos1 = data.find('\"');
            // Check if index is valid
            if(pos1 != std::string::npos)
            {
                // Get index position of second quote in string
                size_t pos2 = data.find('\"', pos1+1);
                // Check if index is valid
                if(pos2 != std::string::npos)
                {
                    // Get substring between index positions of two quotes
                    symbol = data.substr(pos1 + 1, pos2 - pos1 - 1);
                }
            }
            std::cout << "symbol: " << symbol << std::endl;
            res.push_back(symbol);
        }
        std::cout << "End of update\n";

        return res;
    }

    std::string DataUpdater::updateSymbolData(std::string_view symbol, std::string_view interval, std::string_view format, std::string_view delimiter)
    {
        const std::chrono::time_point now{std::chrono::system_clock::now()};
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

        std::stringstream ss;
        ss << ymd.year() << "-" << static_cast<unsigned>(ymd.month()) << "-" << (static_cast<unsigned>(ymd.day()) - 1);

        twelvedata::Request<twelvedata::TimeSeriesEndpoint> req;
        req.endpointPrefix = twelvedata::EndpointPrefix("https://api.twelvedata.com");
        req.params.requiredParams["symbol"] = symbol;
        req.params.requiredParams["interval"] = interval;
        req.params.optionalParams["format"] = "csv";
        req.params.optionalParams["delimiter"] = ",";
        req.params.optionalParams["start_date"] = "2023-01-03";
        req.params.optionalParams["end_date"] = ss.str();
        req.apiKey = twelvedata::ApiKey(utils::get_api_key("C:\\Users\\rangw\\Documents\\stock-dev\\resources\\api.key"));
        auto request_string = m_timeSeriesRequestBuilder.buildRequest(req);
        cpr::Url url{request_string};
        cpr::Session session;
        session.SetUrl(url);
        std::string strFileData;
        cpr::Response response = session.Download(cpr::WriteCallback{write_data, (intptr_t) &strFileData});
        std::cout << "status code: " << response.status_code << std::endl;
        return strFileData;
    }
}