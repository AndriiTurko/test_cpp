#ifndef TEST_CPP_HELPERS_H
#define TEST_CPP_HELPERS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <chrono>
#include <algorithm>



const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


std::vector<std::vector<std::string>> read_file(const std::string& filename, char delim) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> row;
    std::string temp_row, word;

    std::fstream file (filename, std::ios::in);

    if (file.is_open()) {
        while (getline(file, temp_row)) {
            row.clear();

            std::stringstream str(temp_row);

            while (getline(str, word, delim)) {
                row.push_back(word);
            }
            result.push_back(row);
        }
    } else {
        std::cerr << "Could not open input file: " << filename << std::endl;
        exit(-1);
    }

    result.erase(result.begin());
    return result;
}


std::map<std::string, std::map<std::string, int>> count_hours(const std::vector<std::vector<std::string>>& csv_info) {
    std::map<std::string, std::map<std::string, int>> result;

    for (const auto& row : csv_info) {
        std::string name = row[0];
        if (std::any_of(name.begin(), name.end(), ::isdigit)) {
            std::cerr << "Name: " << name << " is incorrect" << std::endl;
            continue;
        }
        std::string get_date = row[row.size()-2];
        result[name][get_date.substr(0, get_date.size()-3)] += std::stoi(row[row.size()-1]);
    }
    return result;
}


void write_result(const std::string& filename, const std::map<std::string, std::map<std::string, int>>& counted_hours) {
    std::fstream file (filename, std::ios::out);

    if (file.is_open()) {
        file << "Name;Month;Total hours\n";
        for (const auto& name_info : counted_hours) {
            for (const auto& month_hours : name_info.second) {
                int month = std::stoi(month_hours.first.substr(5));
                std::string month_year = std::string(months[month]) + " " + month_hours.first.substr(0,4);
                file << name_info.first << ";" << month_year << ";" << month_hours.second << "\n";
            }
        }
    }
}


#endif //TEST_CPP_HELPERS_H
