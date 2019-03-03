#include "./layer_map.hh"


LayerMap::LayerMap(std::string filename):
    m_filename{ filename }
{
    this->update_map();
}

LayerMap::LayerMap():
    m_filename{}
{

}

LayerMap::~LayerMap()
{

}

void LayerMap::set_filename(std::string filename)
{
    this->m_filename = filename;
}

std::string LayerMap::get_filename() const
{
    return this->m_filename;
}

void LayerMap::update_map()
{
    if (this->m_filename.empty()) return;

    DataHandler data_handler{ this->m_filename, "->", ",", ";", true};
    
    auto vars = data_handler.get_variables();
    
    for (auto var: vars){
        for (auto value: var.second){
            auto dot_position_first = var.first.find_first_of(".");
            auto dot_position_second = value.find_first_of(".");

            std::string filter_id = var.first.substr(0, dot_position_first);
            int filter_layer = std::stoi(var.first.substr(dot_position_first + 1));
            int image_layer  = std::stoi(value.substr(dot_position_second + 1));

            this->add_map(filter_id, filter_layer, image_layer);
        }
    }
}

void LayerMap::add_map(std::string filter_id, int filter_layer, int image_layer)
{
    auto tp = std::make_tuple(filter_id, filter_layer, image_layer);
    this->m_map.push_back(tp);
}

const std::vector<std::tuple<std::string, int, int>>& LayerMap::get_map() const
{
    return this->m_map;
}

void LayerMap::show_me() const
{
    std::cout << "How filter layers and image layers are related: \n";
    for (auto map: this->m_map){
        std::cout << "\tLayer "  << std::get<1>(map) << " of filter \"" 
                  << std::get<0>(map) << "\" will be applied to layer " 
                  << std::get<1>(map) << " of image" << std::endl;
    }
}

