#ifndef __DATA_HANDLER__
#define __DATA_HANDLER__

// standard includes
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <exception>

// TODO: change MapType to std::unordered_map

class DataHandler{
public:
    using MapType = std::unordered_map<std::string, std::vector<std::string>>;

    DataHandler(
        std::string filename  = "",
        std::string assign    = "->",
        std::string separator = "," ,
        std::string end       = ";" ,
        bool duplication_allowed = false
    );


    ~DataHandler();

    void update();

    void set_filename(std::string filename);
    std::string get_filename() const;

    std::vector<std::string> get_expressions() const;
    MapType get_variables() const;
    
    void set_assign_operator(std::string oprt);
    std::string get_assign_operator() const;

    void set_end_expression_operator(std::string oprt);
    std::string get_end_expression_operator() const;

    void set_values_separators_operator(std::string oprt);
    std::string get_values_separators_operator() const;

protected:
    void process_expression(std::string expression);
    void process_variables(std::string expression);

    std::string remove_character(std::string source, std::string chrs);


private:
    std::string m_filename;
    std::string m_assign_operator;
    std::string m_end_expression;
    std::string m_values_separator;
    bool m_duplication_allowed;

    std::vector<std::string> m_expressions;
    MapType m_variables;
    // std::unordered_map<std::string, std::vector<std::string>> m_variables; --> TODO
};

template <typename T, typename U> T parse(U);
template <> int parse<int>(std::vector<std::string>);
template <> float parse<float>(std::vector<std::string>);
#endif