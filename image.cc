#include "./image.hh"



Image::Image(const cv::Mat& image)
{
    cv::split(image, this->m_image_layers);
}

void Image::apply_filter(
    const Filter& filter,
    int filter_layer,
    int image_layer)
{
    if (image_layer >= this->m_image_layers.size())
        throw std::string{"This image doesn't have too many layers"};
   
    // using namespace std;

    const static int depth_as_input_source = -1;
    
    cv::Mat knl = filter.get_filter(filter_layer);
    // cout << knl.size().width << endl;

    const cv::Mat& img = this->m_image_layers[image_layer];

    cv::filter2D(
        img,
        img,
        depth_as_input_source,
        knl    
    );

}
void Image::apply_filter(
    cv::Mat filter,
    int filter_layer,
    int image_layer)
{
    
    Filter filter_{filter};

    this->apply_filter(
      filter_,
      filter_layer,
      image_layer 
    );
}

cv::Mat Image::get_image() const{
    cv::Mat output;
    cv::merge(this->m_image_layers, output);
    return output;
}

void Image::apply_filter_batch(
    std::vector<std::tuple<const Filter&, int, int>> batch)
{

}

cv::Size Image::get_dimensions() const
{

    return this->m_image_layers[0].size();
}

Image::~Image()
{

}

