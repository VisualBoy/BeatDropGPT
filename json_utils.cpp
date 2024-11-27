#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

using json = nlohmann::json;

class JsonUtils {
public:
    static std::string ParseResponse(const std::wstring& response) {
        try {
            // Convert wstring to string
            std::string responseStr(response.begin(), response.end());
            // Parse the JSON response
            json jsonResponse = json::parse(responseStr);
            // Extract the desired field (e.g., "text" from the response)
            return jsonResponse["choices"][0]["text"].get<std::string>();
        } catch (const std::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            return "";
        }
    }
};
