#ifndef __FILTER_FACTORY__
#define __FILTER_FACTORY__

// user include
#include "./filter.hh"
#include "./data_handler.hh"

// standard include
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


// third part include



class FilterFactory{
public:
    FilterFactory(std::vector<std::string> filters_filenames);
    ~FilterFactory();

    void add_filename(std::string filter_filename);
    void remove_filename(std::string filter_filename);

// TODO: implement
    void update_filters();

    const Filter& get_filter(std::string filter_id) const;
    

protected:
    void make_filter(std::string filter_id, std::vector<int> dims, std::vector<float> value);

private:
    std::vector<std::string> m_filenames;
    std::vector<Filter*> m_filters;

    std::string prepare_error_message(
        bool id_found  ,
        bool dims_found,
        bool data_found
    );

    template <typename T>
    std::vector<T> parse_vector(std::vector<std::string> vec);
};



#endif