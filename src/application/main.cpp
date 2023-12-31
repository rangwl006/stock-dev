#include <filesystem>
#include <vector>
#include <string>
#include <fstream>

#include "utils/thread_pool.h"
#include "request_builder/ApiBuilder.h"
//#include "utils/read_api_key.h"
#include <cpr/cpr.h>
#include <cpr/api.h>
#include <cpr/session.h>
#include "data_updater/data_updater.h"
#include <curl/curl.h>
//void createBuilder()
//{
//    twelvedata::Request<twelvedata::TimeSeriesEndpoint> req;
//    req.endpointPrefix = twelvedata::EndpointPrefix("https://api.twelvedata.com");
//    req.params.requiredParams["symbol"] = "AAPL";
//    req.params.requiredParams["interval"] = twelvedata::INTERVALS::ONE_DAY;
//    req.params.optionalParams["start_date"] = "2020-07-10";
//    req.params.optionalParams["end_date"] = "2021-01-10";
//    req.apiKey = twelvedata::ApiKey(utils::get_api_key("C:\\Users\\rangw\\Documents\\stock-dev\\resources\\api.key"));
//    CURL* curlptr = curl_easy_init();
//    core::RequestBuilder<twelvedata::TimeSeriesEndpoint> s(req);
////    twelvedata::TimeSeriesEndpointParams epd;
////    std::cout << s.buildRequest(epd);
//    cpr::Url url{s.buildRequest(req)};
//    cpr::Session session;
//    session.SetUrl(url);
//    std::string strFileData;
//    cpr::Response response = session.Download(cpr::WriteCallback{real_write_data, (intptr_t) &strFileData});
//    std::cout << std::setw(2) << strFileData << std::endl;
//}

void print()
{
    std::cout << "printing something\n";
}

bool real_write_data(std::string data, intptr_t userdata)
{
    // NOLINTNEXTLINE (cppcoreguidelines-pro-type-reinterpret-cast)
    std::string* dst = reinterpret_cast<std::string*>(userdata);
    *dst += data;
    return true;
}
int main()
{
//    createBuilder();
//
    core::DataUpdater d;

    auto nyse = d.updateTickers("NYSE");
    std::ofstream nyseSymbols("C:\\Users\\rangw\\Documents\\stock-dev\\generated\\nyse.txt");
    for (const auto& symbol : nyse)
    {
        if (!symbol.empty())
        {
            nyseSymbols << symbol << "\n";

        }
    }

    auto nasdaq = d.updateTickers("NASDAQ");
    std::ofstream nasdaqSymbols("C:\\Users\\rangw\\Documents\\stock-dev\\generated\\nasdaq.txt");

    for (const auto& symbol : nasdaq)
    {
        if (!symbol.empty())
            nasdaqSymbols << symbol << "\n";
    }

    auto ret = d.updateSymbolData("AAPL");
    std::ofstream outfile("C:\\Users\\rangw\\Documents\\stock-dev\\generated\\stocks\\AAPL.csv");
    outfile << ret;
    std::cout << ret << std::endl;
//    twelvedata::Request<twelvedata::TimeSeriesEndpoint> req;
//    req.endpointPrefix = twelvedata::EndpointPrefix("https://api.twelvedata.com");
//    req.params.requiredParams["symbol"] = "AAPL";
//    req.params.requiredParams["interval"] = twelvedata::INTERVALS::ONE_DAY;
//    req.params.optionalParams["start_date"] = "2020-07-10";
//    req.params.optionalParams["end_date"] = "2021-01-10";
//    req.apiKey = twelvedata::ApiKey(utils::get_api_key("C:\\Users\\rangw\\Documents\\stock-dev\\resources\\api.key"));
//
//    core::RequestBuilder<twelvedata::TimeSeriesEndpoint> s(req);
//    cpr::Url url{s.buildRequest(req)};
//    cpr::Session session;
//    session.SetUrl(url);
//    std::string strFileData;
//    cpr::Response response = session.Download(cpr::WriteCallback{real_write_data, (intptr_t) &strFileData});
//    std::cout << std::setw(2) << strFileData << std::endl;


    return 0;
}