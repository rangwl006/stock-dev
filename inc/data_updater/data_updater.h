#pragma once
#include <string>
#include <vector>
#include "request_builder/ApiBuilder.h"
#include "twelvedata/ApiData.h"

namespace core
{
    class DataUpdater
    {
        public:
            DataUpdater() = default;
            DataUpdater(std::string_view path);
            ~DataUpdater() = default;

            std::vector<std::string> updateTickers(std::string_view exchange, std::string_view format = "csv", std::string_view delimiter = ",");
            std::string updateSymbolData(std::string_view symbol, std::string_view interval = twelvedata::INTERVALS::ONE_DAY , std::string_view format = "csv", std::string_view delimiter = ",");
            static bool real_write_data(std::string data, intptr_t userdata);

        protected:
            RequestBuilder<twelvedata::StocksEndpoint> m_stockRequestBuilder;
            RequestBuilder<twelvedata::TimeSeriesEndpoint> m_timeSeriesRequestBuilder;
            std::string _apiKeyPath;
    };
}