module;

#include <httplib.h>
#include <iostream>

export module http;

export void https() {
    httplib::Client client{"https://api.farming-community.eu"};

    auto res = client.Get("/api/v1/details/salvaging/unid-gear/piece-of-rare-unidentified-gear");
    
    // Check result and print raw response
    if (res) {
        std::cout << "HTTP " << res->status << "\n";
        std::cout << res->body << "\n";
    } else {
        std::cerr << "Request failed\n";
    }
}