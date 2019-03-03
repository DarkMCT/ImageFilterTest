#include "./data_handler.hh"

DataHandler::DataHandler(
    std::string filename,
    std::string assign, 
    std::string separator, 
    std::string end, 
    bool duplication_allowed)
:
    m_filename{ filename },
    m_assign_operator{ assign } ,
    m_values_separator{ separator },
    m_end_expression{ end },
    m_duplication_allowed{ duplication_allowed }
{
    if (!this->m_filename.empty())
        this->update();
}


DataHandler::~DataHandler()
{

}

void DataHandler::update()
{    
    // Restart to inicial state
    this->m_expressions.clear();
    this->m_variables.clear();
    
    // Reserve resources
    static const unsigned int BUFFER_LENGTH = 512;
    char buffer[BUFFER_LENGTH];


    if (this->m_filename.empty()) return;

    // TODO: refactor
    std::ifstream input_file;
    try{
        input_file.open(
            this->m_filename,
            std::ios_base::in
        );
    } catch (...){
        throw std::string{"Error: The file \""} + this->m_filename + "\" wasn't found";
    }

    std::string expression;
    while (!input_file.eof())
    {
        input_file.getline(buffer, BUFFER_LENGTH);
        
        std::string bf{buffer}; // wrap    
        
        if (bf.size() == 0 || bf.at(0) == '#') continue; // comment

        // cout << this->m_end_expression << endl;
        int semicolon_in_buffer = bf.find_first_of(this->m_end_expression);
        if (semicolon_in_buffer == std::string::npos){
            expression.append(bf);
        } else {
            expression.append(bf.substr(0, semicolon_in_buffer));
            // cout << expression << endl;
            this->process_expression(expression);
            expression.erase();
            if (semicolon_in_buffer < bf.size() - 1) // last data
                expression.append(bf.substr(semicolon_in_buffer + 1));
        }
    }
       
}

void DataHandler::set_filename(std::string filename)
{
    this->m_filename = filename;
}

std::string DataHandler::get_filename() const
{
    return this->m_filename;
}

std::vector<std::string> DataHandler::get_expressions() const
{
    return this->m_expressions;
}

DataHandler::MapType DataHandler::get_variables() const
{
    return this->m_variables;
}

void DataHandler::set_assign_operator(std::string oprt)
{
    this->m_assign_operator = oprt;
}

std::string DataHandler::get_assign_operator() const
{
    return this->m_assign_operator;
}


void DataHandler::set_end_expression_operator(std::string oprt)
{
    this->m_end_expression = oprt;
}

std::string DataHandler::get_end_expression_operator() const
{
    return this->m_end_expression;
}

void DataHandler::set_values_separators_operator(std::string oprt)
{
    this->m_values_separator = oprt;
}

std::string DataHandler::get_values_separators_operator() const
{
    return this->m_values_separator;
}

void DataHandler::process_expression(std::string expression)
{
    // using namespace std;
    // cout << expression << endl;
    this->m_expressions.push_back(expression);
    this->process_variables(expression);
}

void DataHandler::process_variables(std::string expression)
{
    expression = this->remove_character(expression, " \n\t\"\'"); 
    
    // get var name
    int  assing_oprt_in_expr = expression.find_first_of(this->m_assign_operator);
    std::string variable = expression.substr(0, assing_oprt_in_expr);
    
    
    // remove var name and assign operator from expression
    expression.erase(0, assing_oprt_in_expr + this->m_assign_operator.size()); // remove the var name from expression

    // read value or values
    std::vector<std::string> values;
    do {
        auto end = expression.find_first_of(this->m_values_separator);
        
        if (end != std::string::npos) // if multi value
            values.push_back(expression.substr(0, end));
        else 
            values.push_back(expression); // if single value
        
        // remove the portion of expression already analyzed
        expression.erase(0, end == std::string::npos ? expression.size() : end + this->m_values_separator.size());

    } while(expression.size());

    
    // --------- Hard block --------
    bool already_declared = this->m_variables.find(variable) != this->m_variables.end();
    if (already_declared && !this->m_duplication_allowed)      
            throw std::string{"Variable redeclaration: \""} + variable + "\" at: \"" + this->m_filename + "\"";
    
    if (already_declared){        
        auto& _values = this->m_variables.at(variable);
        _values.insert(_values.end(), values.begin(), values.end());
    } else {
        auto pair = std::make_pair(variable, values);
        this->m_variables.insert(pair);    
    } 
    // ---------------------------
}

std::string DataHandler::remove_character(std::string source, std::string chrs)
{
    for (auto chr: chrs){
        source.erase(
            std::remove_if(source.begin(), 
                           source.end(),
                           [](unsigned char x)
                                {return std::isspace(x) || x=='\"';}),
            source.end()
        );
    }

    return source;
}