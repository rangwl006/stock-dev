#pragma once
#include <string>
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

            void updateTickers(std::string_view exchange, std::string_view format = "csv", std::string_view delimiter = ";");
            void updateTickerData();
            static bool real_write_data(std::string data, intptr_t userdata);

        protected:
            RequestBuilder<twelvedata::StocksEndpoint> m_stockRequestBuilder;
            RequestBuilder<twelvedata::TimeSeriesEndpoint> m_timeSeriesRequestBuilder;
            std::string _apiKeyPath;
    };
}