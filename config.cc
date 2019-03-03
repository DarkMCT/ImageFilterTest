#include "./config.hh"

Config::Config(std::string filename):
    m_filename{ filename },
    data_handler{ filename }
{
    // data_handle already updated
    this->update_configurations(false);
}

Config::~Config()
{
    // Not is necessary free the file because it's 
    // handled by Congif::update
}

void Config::set_filename(std::string img_filename)
{
    this->m_filename = img_filename;
}

std::string Config::get_filename() const
{
    return this->m_filename;
}

void Config::update_configurations(bool update_data_handler)
{
    if (update_data_handler)
        this->data_handler.update();

    auto vars = this->data_handler.get_variables();

    // what configurations is present
    int img_cnf_found = 0,
        map_cnf_found = 0,
        flt_cnf_found = 0;

    if (vars.find("image") != vars.end()){
        this->m_image_filename = vars["image"][0];
        img_cnf_found = 1;
    }
    if (vars.find("map") != vars.end()){
        this->m_map_filename = vars["map"][0];
        map_cnf_found = 1;
    }
    if (vars.find("filters") != vars.end()){
        this->m_filters_filename = vars["filters"];
        flt_cnf_found = 1;
    }

   /*  for (auto var: vars){
        img_cnf_found += (var.first == "image"   ? 1 : 0);
        map_cnf_found += (var.first == "map"     ? 1 : 0);
        flt_cnf_found += (var.first == "filters" ? 1 : 0);

        if (var.first == "image"  ) this->m_image_filename   = var.second[0]; // Just the first have meaning
        if (var.first == "map"    ) this->m_map_filename     = var.second[0]; // Just the first have meaning
        if (var.first == "filters") this->m_filters_filename = var.second   ; 
    }
    */

    if (img_cnf_found == 0 || map_cnf_found == 0 || flt_cnf_found == 0 ){ 
        
        std::string exception_message{this->prepare_error_message(img_cnf_found, map_cnf_found, flt_cnf_found)};
        throw exception_message;
    } 
}

/* void Config::update() -> refactored to ./data_handler.cc
{
    static const unsigned int BUFFER_LENGTH = 512;
    char buffer[BUFFER_LENGTH];
    std::string expression;

    std::ifstream input_file{
        this->m_filename,
        std::ios_base::in
    };

    while (!input_file.eof())
    {
        input_file.getline(buffer, BUFFER_LENGTH);
        
        std::string bf{buffer}; // wrap        
        
        if (bf.size() == 0 || bf.at(0) == '#') continue; // comment

        int semicolon_in_buffer = bf.find_first_of(";");
        if (semicolon_in_buffer == std::string::npos){
            expression.append(bf);
        } else {
            expression.append(bf.substr(0, semicolon_in_buffer));
            this->process_expression(expression);
            expression.erase();
            if (semicolon_in_buffer < bf.size() - 1) // last data
                expression.append(bf.substr(semicolon_in_buffer + 1));
        }
    }
} */

std::string Config::get_image_filename() const
{
    return this->m_image_filename;
}

std::string Config::get_map_filename() const
{
    return this->m_map_filename;
}

std::vector<std::string> Config::get_filters_filename() const
{
    return this->m_filters_filename;
}

/* void Config::process_expression(std::string expression) -> refactored to ./data_handler.cc
{
    using namespace std;    
    cout << expression << endl;
} */

std::string Config::prepare_error_message(int img_cnf_found, int map_cnf_found, int flt_cnf_found)
{
    std::string exception_message{ "Errors found: \n" };

    if (img_cnf_found == 0)
        exception_message.append(std::string{"\t No declaration of \"image\" variable\n"});

    if (map_cnf_found == 0)
        exception_message.append(std::string{"\t No declaration of \"map\" variable\n"});

    if (flt_cnf_found == 0)
        exception_message.append(std::string{"\t No declaration of \"filters\" variable\n"});

    return exception_message;
}