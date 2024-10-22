#include <iostream>
#include <json.hpp>

using json = nlohmann::json;

// 解析JSON字符串并读取参数：
// 使用nlohmann/json库解析你的字符串并读取里面的参数：

// cpp

int main() {
    // JSON字符串
    std::string json_string = R"([2,"4489e72f-edaa-48e8-bd99-89e653270412","StartTransaction",{"connectorId":1,"idTag":"123456","meterStart":5302,"timestamp":"2024-09-24T01:03:36.320Z"}])";

    // 解析JSON字符串
    auto json_data = json::parse(json_string);

    // 读取参数
    int cmdNum = json_data[0];
    std::string uuid = json_data[1];
    std::string actionName = json_data[2];
    int connectorId = json_data[3]["connectorId"];
    std::string idTtag = json_data[3]["idTag"];
    int meterStart = json_data[3]["meterStart"];
    std::string timestamp = json_data[3]["timestamp"];

    // 输出读取的参数
    std::cout << "Command: " << cmdNum << std::endl;
    std::cout << "uu ID: " << uuid << std::endl;
    std::cout << "Action: " << actionName << std::endl;
    std::cout << "Connector ID: " << connectorId << std::endl;
    std::cout << "ID Tag: " << idTtag << std::endl;
    std::cout << "Meter Start: " << meterStart << std::endl;
    std::cout << "Timestamp: " << timestamp << std::endl;

    return 0;
}