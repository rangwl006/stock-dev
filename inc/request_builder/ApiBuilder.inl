#include "utils/debug_log.h"

namespace core
{
    template<typename EndpointType_>
    std::string RequestBuilder<EndpointType_>::buildRequest(twelvedata::Request<EndpointType> request)
    {
        _requestString.clear();
        _request = request;
        setEndpointPrefix();
        setEndpoint();
        setRequiredParams();
        setOptionalParams();
        setApiKey();
        return _requestString;
    }

    template<typename EndpointType_>
    void RequestBuilder<EndpointType_>::setEndpointPrefix()
    {
        _requestString += _request.endpointPrefix.get() + "/";
    }

    template<typename EndpointType_>
    void RequestBuilder<EndpointType_>::setEndpoint()
    {
        _requestString += std::string(EndpointType_::endpoint) + "?";
    }

    template<typename EndpointType_>
    void RequestBuilder<EndpointType_>::setApiKey()
    {
        _requestString += "apikey=" + _request.apiKey.get();
    }

    template<typename EndpointType_>
    void RequestBuilder<EndpointType_>::setRequiredParams()
    {
        for (const auto &key: _request.params.requiredParams)
        {
            if (_request.params.requiredParams[key] != "")
                _requestString += key + "=" + _request.params.requiredParams[key] + "&";
            else {
                std::cout << "[\033[31m" << "ERROR" << "\033[0m] " << "Missing required parameter: " << key
                          << std::endl;
            }
        }
    }

    template<typename EndpointType_>
    void RequestBuilder<EndpointType_>::setOptionalParams()
    {
        for (const auto &key: _request.params.optionalParams)
        {
            if (_request.params.optionalParams[key] != "")
                _requestString += key + "=" + _request.params.optionalParams[key] + "&";
        }
    }
}