#ifndef __LAYER_MAP__
#define __LAYER_MAP__

// standard include
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

// user include
#include "./data_handler.hh"

class LayerMap{
public:
    LayerMap(std::string filename);
    LayerMap();
    
    ~LayerMap();

    void set_filename(std::string filename);
    std::string get_filename() const;

    void update_map();

    void add_map(std::string filter_id, int filter_layer, int image_layer);

    const std::vector<std::tuple<std::string, int, int>>& get_map() const;

    void show_me() const ;

protected:

private:
    std::string m_filename;
    std::vector<std::tuple<std::string, int, int>> m_map;

};

#endif