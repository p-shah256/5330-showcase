#include <fstream>
#include <vector>
#include "httplib.h"
#include "spdlog/spdlog.h"

/**
 * 1. sets up a IFSTREAM
 * 2. reads the file into stringSTREAM
 * 3. sends the file
 */
void GET_handler(const httplib::Request& req, httplib::Response& res) {
    std::string file_path = req.path;

    std::ifstream file("../" + file_path, std::ios::binary);
    if (!file.is_open()) {
        res.status = 404;
        res.set_content("Not Found", "text/plain");
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string content = buffer.str();
    if (file_path.find(".css") != std::string::npos) {
        res.set_content(content, "text/css");
    } else if (file_path.find(".html") != std::string::npos) {
        res.set_content(content, "text/html");
    } else {
        res.set_content(content, "text/plain");
    }
}
