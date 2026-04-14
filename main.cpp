#include<iostream>
#include<string_view>
#include<string>
#include<stdexcept>
#include<vector>
struct RequestLine {
    std::string_view method;
    std::string_view uri;
    std::string_view version;
};
using Header = std::pair<std::string_view, std::string_view>;

RequestLine parseRequestLine(std::string_view line) {
    RequestLine rl;
    size_t n = line.size();
    size_t i = 0;

    while(i<n && line[i] == ' ') i++;
    size_t methodEnd = line.find(' ', i);
    if (methodEnd == std::string_view::npos) throw std::invalid_argument("Invalid request line");
    rl.method = line.substr(i, methodEnd - i);
    for (char c : rl.method) {
        if (c < 'A' || c > 'Z') throw std::invalid_argument("Method must be uppercase");
    }
    i = methodEnd + 1;

    while(i<n && line[i] == ' ') i++;
    size_t uriEnd = line.find(' ', i);
    if (uriEnd == std::string_view::npos) throw std::invalid_argument("Invalid request line");
    rl.uri = line.substr(i, uriEnd - i);
    i = uriEnd + 1;

    while(i<n && line[i] == ' ') i++;
    if (i == n) throw std::invalid_argument("Version not found");
    rl.version = line.substr(i);
    if (rl.version.substr(0, 5) != "HTTP/") throw std::invalid_argument("Version is not HTTP");
    return rl;
};




std::vector<Header> parseHeaders(std::string_view headers) {

}

int main() {
    std::vector<std::string> reqs = {
        "GET / HTTP/1.1",
        "POST /api/users   HTTP/1.1",
        "DELETE    /users/42    HTTP/1.0"
    };

    for (auto req : reqs) {
        std::cout<<std::endl;
        std::cout << req << std::endl;
        RequestLine rl = parseRequestLine(req);
        std::cout << "method: " << rl.method << std::endl;
        std::cout << "uri: " << rl.uri << std::endl;
        std::cout << "version: " << rl.version << std::endl;
    }
    
}