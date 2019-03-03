#include "./filter_factory.hh"

FilterFactory::FilterFactory(std::vector<std::string> filters_filenames):
    m_filenames{ filters_filenames }
{
    this->update_filters();
}

FilterFactory::~FilterFactory()
{
    for(int i = 0;i < this->m_filters.size(); i++)
       delete this->m_filters[i];    
}

void FilterFactory::add_filename(std::string filter_filename)
{
    this->m_filenames.push_back(filter_filename);
}

void FilterFactory::remove_filename(std::string filter_filename)
{
    auto position = std::find(
        this->m_filenames.begin(),
        this->m_filenames.end(),
        filter_filename
    );

    if (position != this->m_filenames.end())
        this->m_filenames.erase(position, position + 1);
}

void FilterFactory::update_filters()
{
    DataHandler data_handler{};
    for (auto filename: this->m_filenames){
        data_handler.set_filename(filename);
        data_handler.update();

        
        auto vars = data_handler.get_variables();

        auto is_present = [&vars](std::string field) -> bool{
            return vars.find(field) != vars.end();
        };

        bool id_is_present   = is_present("id")  ,
             dims_is_present = is_present("dim"),
             data_is_present = is_present("data");

        if (!id_is_present || !dims_is_present || !data_is_present)
            throw this->prepare_error_message(id_is_present, dims_is_present, data_is_present);
        
        std::string filter_id =  vars["id"][0];
        std::vector<std::string> dims = vars["dim"];
        std::vector<std::string> data = vars["data"];    

        this->make_filter(
            filter_id,
            this->parse_vector<int>(dims),
            this->parse_vector<float>(data)
        );
    }
}


const Filter& FilterFactory::get_filter(std::string filter_id) const
{
    for (auto& filter: this->m_filters)
        if ((*filter).get_filter_id() == filter_id)
            return *filter;

    throw "Unexistend filter";
}

void FilterFactory::make_filter(std::string filter_id, std::vector<int> dims, std::vector<float> value)
{
    
    this->m_filters.push_back(
        new Filter{
            dims,
            value,
            filter_id
        }
    );
    
}

template <typename U, typename T>
U parse(T source){
    return (U)source;
}

template <>
float parse<float, std::string>(std::string source){
    return std::stof(source);
}

template <>
int parse<int, std::string>(std::string source){
    return std::stoi(source);
}

template<typename T>
std::vector<T> FilterFactory::parse_vector(std::vector<std::string> vec)
{
    std::vector<T> target{};
    for (auto value: vec)
        target.push_back(parse<T>(value));

    return target;
}

std::string FilterFactory::prepare_error_message(bool id_found, bool dims_found, bool data_found)
{
    std::string error_message{"Errors found:"};

    if (!id_found)   error_message.append("\tFilter \"id\" wasn't found\n")  ;
    if (!dims_found) error_message.append("\tFilter \"dims\" wasn't found\n");
    if (!data_found) error_message.append("\tFilter \"data\" wasn't found\n");

    return error_message;
}