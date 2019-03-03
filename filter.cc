#include "./filter.hh"

Filter::Filter(const cv::Mat& kernel, std::string filter_id):
    m_filter_id{ filter_id },
    m_memory_allocated{ false }
{
    cv::split(kernel, this->m_kernel_layers);
}

Filter::Filter(std::vector<int> dims, std::vector<float> data, std::string filter_id):
    m_filter_id{ filter_id },
    m_memory_allocated{ false }
{
    if (dims.size() >  3) throw "Too much dims for this system";
    if (dims.size() <= 0) throw "At least one dimension is required";
    while (dims.size() < 3) dims.push_back(1);
    
    int w = dims[0], h = dims[1], d = dims[2];

    if (w <= 0 || h <= 0 || d <= 0) throw "Bad dims, should be greater than 0";

    for(int i = 0;i < d;i++)
    {        
        // just the layer elements
        float * mem = this->parse_to_raw_data(
            data,
            w*h*i,
            w*h
        );

        cv::Mat mat{w, h, CV_32F, mem};
        this->m_kernel_layers.push_back(mat);
        // std::cout << data.size() << '\n';
        // data.erase(data.begin(), data.begin() + w * h - 1);

    }
}

void Filter::set_filter_id(std::string filter_id)
{
    this->m_filter_id = filter_id;
}

std::string Filter::get_filter_id() const
{
    return this->m_filter_id;
}

int Filter::get_filter_dimensions() const
{
    return this->m_kernel_layers.size();
}

const cv::Mat& Filter::get_filter(int filter_layer) const
{
    if (filter_layer >= this->m_kernel_layers.size())
        throw std::string{"This kernel doesn't have too many layers"};
    return this->m_kernel_layers[filter_layer];
}

void Filter::draw_me() const
{
    int w = this->m_kernel_layers[0].size().width, 
        h = this->m_kernel_layers[0].size().height,
        d = this->m_kernel_layers.size();
    std::cout << "filter id: " << this->m_filter_id << '\n';
    std::cout << "dimensions[w h d]: " << w << "x" << h << "x" << d << "\n";
    int l = 0;
    for (auto layer: this->m_kernel_layers){
        std::cout << "layer: " << l++ << '\n';
        for(size_t i = 0; i < h; i++)
        {
            for(size_t j = 0; j < w; j++)
            {
                std::cout << layer.at<float>(i, j) << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
        
    }
}

Filter::~Filter()
{
    // std::cout << "destructor called:" << this->m_filter_id << std::endl;
    for(auto&& mem : this->m_memory_allocated)
        delete[] mem;  
}

float * Filter::parse_to_raw_data(const std::vector<float>& source, int offset, int size)
{
    if (source.size() < (offset + size)) 
        throw std::string{"Error: The dimensions of filter not agree with data at \""} + 
              this->m_filter_id + "\".";
    // if (this->m_memory_allocated) delete[] this->m_raw_data;
    float* raw_data = new float[size];
    this->m_memory_allocated.push_back(raw_data);
    // this->m_memory_allocated = true;

    for(auto i = 0;i < size;i++) 
        raw_data[i] = source[offset + i];

    return raw_data;
}

