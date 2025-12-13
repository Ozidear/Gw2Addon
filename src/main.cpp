#include <httplib.h>
#include <iostream>

int main() {
    // Create a client for the host
    httplib::Client cli("https://api.farming-community.eu");

    // Fire a GET request
    auto res = cli.Get("/api/v1/details/salvaging/unid-gear/piece-of-rare-unidentified-gear");

    // Check result and print raw response
    if (res) {
        std::cout << "HTTP " << res->status << "\n";
        std::cout << res->body << "\n";
    } else {
        std::cerr << "Request failed\n";
    }

    return 0;
}