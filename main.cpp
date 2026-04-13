#include<iostream>
#include<string_view>
#include<string>

int main() {
    std::string req = "GET /index.html HTTP/1.1";

    std::string_view method = std::string_view(req.data(), 3);
    std::cout << method << std::endl;

    req[0] = 'S';
    std::cout << method << std::endl;

    std::cout << (void*)method.data() << std::endl;
    std::cout << (void*)req.data() << std::endl;
    
}