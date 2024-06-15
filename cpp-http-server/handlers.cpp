#include <fstream>
#include <vector>
#include "httplib.h"
#include "spdlog/spdlog.h"

/**
 * 1. sets up a file ifstream
 * 2. gets the file size
 * 3. reads chars = file size from into a buffer
 * 4. sends data from buffer start to end 
 *
 * 
 */
void GET_root(const httplib::Request& req, httplib::Response& res) {
    // Construct the file path based on the request path
    std::string file_path = "../index.html";
    spdlog::info("Requested file: {}", file_path);
		// ifstream setup to read the file
    std::ifstream file(file_path, std::ios::in | std::ios::binary | std::ios::ate);

    // Check if the file opened successfully
    if (!file.is_open()) {
        spdlog::error("Failed to open file: {}", file_path);
        res.status = 404;
        res.set_content("Not Found", "text/plain");
        return;
    }

		// get the size by last read ptr, set at the end of using std::ios::ate
    std::streamsize file_size = file.tellg();
		// move the file read ptr back to the beg 
    file.seekg(0, std::ios::beg);

    // create a array of chars to hold the file
    std::vector<char> buffer(file_size);
		// file.read into buffer.data (equal to the file size calculated earlier)
    if (!file.read(buffer.data(), file_size)) {
        spdlog::error("Failed to read file: {}", file_path);
        res.status = 500;
        res.set_content("Internal Server Error", "text/plain");
        return;
    }
    // send data starting from buffer.data and = size of buffer
    res.status = 200;
    res.set_content(buffer.data(), buffer.size(), "text/html");
    // Log success message and return
    spdlog::info("Successfully served file: {} ({} bytes)", file_path, file_size);
}



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
