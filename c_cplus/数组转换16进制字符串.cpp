#include <iostream>
#include <sstream>
#include <iomanip>

// 将字节数组转换为十六进制字符串
std::string bytesToHexString(const uint8_t *data, size_t size) {
    std::stringstream ss;
    // 设置为十六进制输出，并且使用填充0来保持一致性
    ss << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < size; ++i) {
        // 对每个字节进行格式化输出，每个字节两个十六进制数字
        ss << std::setw(2) << static_cast<int>(data[i]);
    }

    return ss.str();
}

int main() {
    uint8_t myArray[] = {0xde, 0xad, 0xbe, 0xef};
    size_t size = sizeof(myArray) / sizeof(myArray[0]);
    std::string hexString = bytesToHexString(myArray, size);

    std::cout << hexString << std::endl; // 输出 "deadbeef"
    return 0;
}