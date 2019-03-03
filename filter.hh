
#ifndef __FILTER__
#define __FILTER__

#define __in__
#define __out__
#define __in_out__

// standard include
#include <memory>
#include <iostream>

// third party include
#include <opencv4/opencv2/core.hpp>


/**
 * This class represent a filter 
*/
class Filter{

public:
    Filter(const cv::Mat& kernel, std::string filter_id = "no_id");
    Filter(std::vector<int> dims, std::vector<float> data, std::string filter_id);

    void set_filter_id(std::string filter_id);
    std::string get_filter_id() const;
    
    // return the filter dimension
    int get_filter_dimensions() const;

    // return a specific filter layer
    const cv::Mat& get_filter(int filter_layer) const;

    void draw_me() const;
    
    ~Filter();


private:
    std::string m_filter_id;
    std::vector<cv::Mat> m_kernel_layers;   

    std::vector<float *> m_memory_allocated;
    float * parse_to_raw_data(const std::vector<float>& source, int offset, int size); 
};

#endif