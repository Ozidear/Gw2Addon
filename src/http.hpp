#pragma once

struct RareUnidData {
    float tp_profit;
    float tp_tax_profit;
    float opened_salvage_profit;
    float unopened_salvage_profit;
    float open_extract_salvage_profit;
};

RareUnidData get_rare_unid_fast_farming_profits();
