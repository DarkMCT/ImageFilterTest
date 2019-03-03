#include "./filter.hh"
#include "./image.hh"
#include "./config.hh"
#include "./data_handler.hh"
#include "./filter_factory.hh"
#include "./layer_map.hh"

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/videoio.hpp>

#include <iostream>
#include <fstream>

void display_help(){
    using namespace std;
    
    static const int BUFFER_SIZE = 256;
    static char buffer[BUFFER_SIZE];
    
    std::ifstream ifs{"./help/usage.txt"};
    std::string line;
    while (!ifs.eof()){
        ifs.getline(buffer, BUFFER_SIZE);
        cout << std::string{buffer} << endl;
    }
}

bool file_exists(std::string filename){
    using namespace std;
    
    try{
        ifstream{filename}.close();
        return true;
    } catch (...){
        return false;
    }
}

int main(int argc, char ** argv){
    using namespace std;

    if (argc <= 1){
        display_help();
        return 0;
    }
    
    try{
        // Get config file
        std::string config_filename{ argv[1] };

        // Create Config object
        Config config{ config_filename };
        cout << config.get_image_filename() << endl;
        

        // Build the filters specified by config file
        FilterFactory filter_factory{ config.get_filters_filename() };    

        
        
        if (!file_exists(config.get_image_filename())){
            throw std::string{"Image \""} + config.get_image_filename() + "\" not found";
        }

        // Load image from config file
        cv::Mat mat = cv::imread(config.get_image_filename());    
        Image img{mat};
        

        LayerMap layer_map{ config.get_map_filename() };
        layer_map.show_me();
        for (auto map : layer_map.get_map()){
            auto filter_id    = std::get<0>(map);
            auto filter_layer = std::get<1>(map);
            auto image_layer  = std::get<2>(map);

            // Load some filter
            const Filter& filter{filter_factory.get_filter(filter_id)};
            filter.draw_me();
            img.apply_filter(filter, filter_layer, image_layer);            
        }

        cv::namedWindow("Output", 1);

        const char TIME_MS = 33;
        const char ESC_KEY = 27;
        while (cv::waitKey(TIME_MS) != ESC_KEY){
            cv::imshow("Output", img.get_image());
        }
    
    } catch (std::string e){
        cout << e << endl;
    }
    
    
    return 0;
}