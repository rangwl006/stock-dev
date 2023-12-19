#pragma once

#include <memory>

#include "twelvedata/ApiData.h"

namespace core
{
    template<typename EndpointType_>
    class RequestBuilder {
        using EndpointType = EndpointType_;
        using RequestString = std::string;
        using EndpointParams = typename twelvedata::EndpointSelector<EndpointType>::type;
    public:
        explicit RequestBuilder<EndpointType>() = default;

        explicit RequestBuilder<EndpointType>(twelvedata::Request<EndpointType> request)
        : _request(request)
        {

        }

        RequestString buildRequest(twelvedata::Request<EndpointType> request);

    private:
        void setEndpointPrefix();

        void setEndpoint();

        void setApiKey();

        void setRequiredParams();

        void setOptionalParams();

        twelvedata::Request<EndpointType> _request;
        RequestString _requestString;

    };
}

#include "ApiBuilder.inl"
