#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
using json = nlohmann::json;

#include "http.h"

RareUnidData get_rare_unid_fast_farming_profits() {
    httplib::Client client{"https://api.farming-community.eu"};
    httplib::Result res = client.Get("/api/v1/details/salvaging/unid-gear/piece-of-rare-unidentified-gear");

    json json_res = json::parse(res->body);
    std::unordered_map<std::string, float> profit_map;

    for (const auto& entry : json_res["list"]) {   
        std::string key = entry["Name"].get<std::string>() + " - " + entry["Price"].get<std::string>();
        profit_map[key] = entry["TPSellProfit"].get<float>();
    }

    return RareUnidData::from_unordered_map(profit_map);
}