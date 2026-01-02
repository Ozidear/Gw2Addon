#include <httplib.h>
#include <iostream>

#include "http.h"

void https() {
    httplib::Client client{"https://api.farming-community.eu"};

    httplib::Result res = client.Get("/api/v1/details/salvaging/unid-gear/piece-of-rare-unidentified-gear");
    
    // Check result and print raw response
    if (res) {
        std::cout << "HTTP " << res->status << "\n";
        std::cout << res->body << "\n";
    } else {
        std::cerr << "Request failed\n";
    }
}