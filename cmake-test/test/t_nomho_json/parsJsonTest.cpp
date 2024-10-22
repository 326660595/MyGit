

// {
//     "energyMeterCurrent": 1000,
//     "energyMeterVoltage": 7500,
//     "socLevel": 64,
//     "timeStamp": 1729493451556,
//     "totalEnergyKwh": 85000
// }

#include <json.hpp>
#include <iostream>
#include <string>

// 假设DBMeterValues是一个结构体，用于存储解析后的JSON数据
struct DBMeterValues
{
    int energyMeterCurrent_ = 0;
    int energyMeterVoltage_ = 0;
    int socLevel_ = 0;
    long long timeStamp_ = 0;
    int totalEnergyKwh_ = 0;
};

// 解析JSON字符串并填充DBMeterValues结构体
void parseJson(const std::string &jsonString, DBMeterValues &values)
{
    try
    {
        // 使用nlohmann::json库解析JSON字符串
        nlohmann::json j = nlohmann::json::parse(jsonString);

        // 从JSON对象中提取值并赋给结构体成员变量
        // values.energyMeterCurrent_ = j.at("energyMeterCurrent").get<int>();
        // values.energyMeterVoltage_ = j.at("energyMeterVoltage").get<int>();
        // values.socLevel_ = j.at("socLevel").get<int>();
        // values.timeStamp_ = j.at("timeStamp").get<long long>();
        // values.totalEnergyKwh_ = j.at("totalEnergyKwh").get<int>();

        values.energyMeterVoltage_ = j["energyMeterVoltage"];
        values.energyMeterCurrent_ = j["energyMeterCurrent"];
        values.totalEnergyKwh_ = j["totalEnergyKwh"];
        values.socLevel_ = j["socLevel"];
        values.timeStamp_ = j["timeStamp"];
    }
    catch (const nlohmann::json::exception &e)
    {
        // 捕获并处理JSON解析异常
        std::cerr << "JSON解析错误: " << e.what() << std::endl;
    }
}

int main()
{
    // JSON字符串
    std::string jsonString =
     R"({
        "energyMeterCurrent": 1000,
        "energyMeterVoltage": 7500,
        "socLevel": 64,
        "timeStamp": 1729493451556,
        "totalEnergyKwh": 85000
    })";

    // 创建DBMeterValues结构体实例
    DBMeterValues values;

    // 解析JSON字符串并填充结构体
    parseJson(jsonString, values);

    // 打印解析后的值
    std::cout << "Energy Meter Current: " << values.energyMeterCurrent_ << std::endl;
    std::cout << "Energy Meter Voltage: " << values.energyMeterVoltage_ << std::endl;
    std::cout << "SOC Level: " << values.socLevel_ << std::endl;
    std::cout << "Time Stamp: " << values.timeStamp_ << std::endl;
    std::cout << "Total Energy KWh: " << values.totalEnergyKwh_ << std::endl;

    return 0;
}