#pragma once
#include <string>

#include "../utils/strong_types.h"
#include "../utils/insertion_order_map.h"

namespace twelvedata
{
    using ApiKey = utils::NamedType<std::string, struct ApiKey_>;
    using EndpointPrefix = utils::NamedType<std::string, struct endpointPrefix_>;
    using RequiredParams = utils::insertion_order_map<std::string, std::string>;
    using OptionalParams = utils::insertion_order_map<std::string, std::string>;

    struct TimeSeriesEndpoint
    {
        static constexpr char endpoint[] = "time_series";
    };

    struct TimeSeriesEndpointParams
    {
        RequiredParams requiredParams =
        {
            {"symbol", ""},
            {"interval", ""}
        };
        OptionalParams optionalParams
        {
            {"format", ""},
            {"start_date", ""},
            {"end_date", ""},
            {"date", ""}
        };
    };

    struct INTERVALS
    {
        static constexpr char ONE_MIN[] = "1min";
        static constexpr char FIVE_MIN[] = "5min";
        static constexpr char FIFTEEN_MIN[] = "15min";
        static constexpr char THIRTY_MIN[] = "30min";
        static constexpr char FORTYFIVE_MIN[] = "45min";
        static constexpr char ONE_HR[] = "1h";
        static constexpr char TWO_HR[] = "2h";
        static constexpr char FOUR_HR[] = "4h";
        static constexpr char ONE_DAY[] = "1day";
        static constexpr char ONE_WEEK[] = "1week";
        static constexpr char ONE_MONTH[] = "1month";
    };

    struct StocksEndpoint
    {
        static constexpr char endpoint[] = "stocks";
    };

    struct StocksEndpointParams
    {
        RequiredParams requiredParams =
        {
        };

        OptionalParams optionalParams
        {
            {"exchange", ""},
            {"type", ""},
            {"format", ""},
            {"delimiter", ""}
        };
    };

    template<typename EndpointType>
    struct EndpointSelector;

    template<>
    struct EndpointSelector<TimeSeriesEndpoint>
    {
        using type = TimeSeriesEndpointParams;
    };

    template<>
    struct EndpointSelector<StocksEndpoint>
    {
        using type = StocksEndpointParams;
    };

    template<typename EndpointType>
    struct Request
    {
        ApiKey apiKey;
        EndpointPrefix endpointPrefix;
        EndpointType endpoint;
        using EndpointParam = typename EndpointSelector<EndpointType>::type;
        EndpointParam params;
    };
}