//
//  CSVReader.h
//  arrival_times_limitorder
//
//  Created by Jarvis on 15/3/2017.
//  Copyright © 2017 Jarvis. All rights reserved.
//


#ifndef CSVReader_h
#define CSVReader_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace Zhuang {
    
    // See more on CSV at https://en.wikipedia.org/wiki/Comma-separated_values
    
    class CSVReader
    {
    public:
        CSVReader(std::string fileName) :fileName_(fileName),
        filestream_(fileName) {};
        
        enum class CSVType {
            Unquoted,
            Quoted,
            QuotedQuote
        };
        
        // Under some situations we have to deal with quotes
        // copes well with complex situations. E.g.
        // spam eggs,"foo,bar","my ""fizz buzz"""
        // 1.23,4.567,-8.00E+09
        inline std::vector<std::string> rowReader(const std::string &row);
        
        inline std::vector<std::vector<std::string> > readCSV();
        inline std::vector<std::vector<std::string> > readCSVPart(int n);
        inline void printCSV();
        
        std::ifstream filestream_;
    private:
        CSVType type_ = CSVType::Unquoted;
        std::string fileName_;
        
    };
    
    
    inline std::vector<std::string> CSVReader::rowReader(const std::string &row) {
        std::vector<std::string> fields{ "" };
        size_t i = 0;
        for (char c : row) {
            switch (type_) {
                case CSVType::Unquoted:
                    switch (c) {
                        case ',': fields.push_back(""); i++;
                            break;
                        case '"': type_ = CSVType::Quoted;
                            break;
                        default: fields[i].push_back(c);
                            break;
                    }
                    break;
                case CSVType::Quoted:
                    switch (c) {
                        case '"': type_ = CSVType::QuotedQuote;
                            break;
                        default: fields[i].push_back(c);
                            break;
                    }
                    break;
                case CSVType::QuotedQuote:
                    switch (c) {
                        case ',': fields.push_back(""); i++;
                            type_ = CSVType::Unquoted;
                            break;
                        case '"': fields[i].push_back('"');
                            type_ = CSVType::Quoted;
                            break;
                        default: type_ = CSVType::Unquoted;
                            break;
                    }
            }
        }
        return fields;
    }
    
    inline std::vector<std::vector<std::string> > CSVReader::readCSV() {
        std::vector<std::vector<std::string> > table;
        std::string row;
        if (filestream_.is_open()) {
            while (std::getline(filestream_, row)) {
                auto fields = rowReader(row);
                table.push_back(fields);
            }
            filestream_.close();
        }
        return table;
        // Don't use eof()
        // eof() reports whether the last read included bytes past the end of the file.
        // If eof() is true, you've already made a mistake.
    }
    
    inline std::vector<std::vector<std::string> > CSVReader::readCSVPart(int n) {
        // first n lines
        std::vector<std::vector<std::string> > table;
        std::string row;
        int count = 1;
        if (filestream_.is_open()) {
            while (std::getline(filestream_, row) && count<=n) {
                auto fields = rowReader(row);
                table.push_back(fields);
                count++;
            }
            filestream_.close();
        }
        return table;
        // Don't use eof()
        // eof() reports whether the last read included bytes past the end of the file.
        // If eof() is true, you've already made a mistake.
    }
    
    inline void CSVReader::printCSV() {
        std::vector<std::vector<std::string> > result;
        if (filestream_.is_open()) {
            result = readCSV();
        }
        else { std::cout << "Error!!" << std::endl; }
        
        for (auto row : result) {
            for (auto data : row) {
                std::cout << data << " , ";
            }
            std::cout << std::endl;
        }
    }
    
}



#endif /* CSVReader_h */
