#include "helpers.h"



int main() {
    std::string filename = "test.csv";
    char delim = ';';
    std::string output_file = "result.csv";

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::vector<std::vector<std::string>> csv_info = read_file(filename, delim);
    if (csv_info.empty()) {
        std::cerr << "CSV file is empty" << std::endl;
        return -2;
    }

    std::map<std::string, std::map<std::string, int>> counted_hours = count_hours(csv_info);

    write_result(output_file, counted_hours);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto parse_time = end - begin;
    std::cout << "Parse time = " << parse_time.count() << " µs" << std::endl;
    return 0;
}
