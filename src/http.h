#pragma once

#include <string>
#include <unordered_map>

struct RareUnidData {
    float tp_profit;
    float tp_tax_profit;
    float opened_salvage_profit;
    float unopened_salvage_profit;
    float open_extract_salvage_profit;

    static RareUnidData from_unordered_map(const std::unordered_map<std::string, float>& map) {
        return RareUnidData{
            .tp_profit = map.at("Current Price on TP - 1 Piece of Rare Unidentified Gear"),
            .tp_tax_profit = map.at("Sell on TP (15% taxes) - 1 Piece of Rare Unidentified Gear"),
            .opened_salvage_profit = map.at(
                "Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Opened) → 1 Rare Gear → 1 Silver Fed Salvage o Matic"
            ),
            .unopened_salvage_profit = map.at("Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Unopened) →  1 Silver Fed Salvage o Matic"),
            .open_extract_salvage_profit = map.at(
                "Piece of Rare Unidentified Gear - 1 Piece of Rare Unidentified Gear (Opened) → 1 Rare Gear → 1 Endless Upgrade Extractor → 1 Silver Fed Salvage o Matic"
            )
        };
    }
};

RareUnidData get_rare_unid_fast_farming_profits();