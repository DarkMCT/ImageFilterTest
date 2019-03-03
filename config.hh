#ifndef __CONFIG__
#define __CONFIG__

// standard include
#include <fstream>
#include <vector>
#include <iostream> // test proposes

// third part include

// user include
#include "./data_handler.hh"

class Config{
public:
    Config(std::string filename);
    ~Config();

    void set_filename(std::string filename);
    std::string get_filename() const;
    void update_configurations(bool update_data_handler = true);
    // void update(); obsolete -> delegated to class data_handler 

    std::string get_image_filename() const;
    std::string get_map_filename() const;
    std::vector<std::string> get_filters_filename() const;

protected:
    // void process_expression(std::string expression); obsolete -> delegated to class data_handler
    DataHandler data_handler;

private:
    std::string m_filename;
    std::string m_image_filename;
    std::string m_map_filename;
    std::vector<std::string> m_filters_filename;


    std::string prepare_error_message(
        int img_cnf_found,
        int map_cnf_found,
        int flt_cnf_found);
};

#endif