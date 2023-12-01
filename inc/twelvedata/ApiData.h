#pragma once
#include <string>

#include "../utils/strong_types.h"
#include "../utils/insertion_order_map.h"

namespace twelvedata
{
    using ApiKey = utils::NamedType<std::string, struct ApiKey_>;
    using EndpointPrefix = utils::NamedType<std::string, struct endpointPrefix>;
    using RequiredParams = utils::insertion_order_map<std::string, std::string>;
    using OptionalParams = utils::insertion_order_map<std::string, std::string>;

    struct TimeSeriesEndpoint
    {
        static constexpr char endpoint[] = "time_series";
    };

    struct TimeSeriesEndpointParams
    {
        RequiredParams requiredParams;
        OptionalParams optionalParams;
    };

    struct StocksEndpoint
    {
        static constexpr char endpoint[] = "stocks";
    };

    struct StocksEndpointParams
    {
        RequiredParams requiredParams;
        OptionalParams optionalParams;
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
        using type = StocksEndpoint;
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