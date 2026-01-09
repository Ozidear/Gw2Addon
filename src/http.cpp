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

    return RareUnidData{
        .tp_profit = profit_map.at("Current Price on TP - 1 Piece of Rare Unidentified Gear"),
        .tp_tax_profit = profit_map.at("Sell on TP (15% taxes) - 1 Piece of Rare Unidentified Gear"),
        .opened_salvage_profit = profit_map.at(
            "Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Opened) → 1 Rare Gear → 1 Silver Fed Salvage o Matic"
        ),
        .unopened_salvage_profit = profit_map.at("Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Unopened) →  1 Silver Fed Salvage o Matic"),
        .open_extract_salvage_profit = profit_map.at(
            "Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Opened) → 1 Rare Gear → 1 Endless Upgrade Extractor → 1 Silver Fed Salvage o Matic"
        )
    };
}