
#ifndef __IMAGE__
#define __IMAGE__

// standard import
#include <iostream>
#include <vector>
#include <tuple>

// third party import
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>

// user import
#include "filter.hh"


/** 
 *  IMAGEM
 *  
 *  Description
 *      Repesenta uma imagem. Possui a capacidade de aplicar um filtro
 *      e um batch de filtros. A primeira aplica um filtro para uma 
 *      camada específica. A segunda utiliza a primeira para aplicar uma
 *      sequência de imagens.
 */

class Image{
public:
/**
 * ctor
 * 
 * @image recebe uma imagem do tipo cv::Mat
 */
    Image(const cv::Mat& image);

/**
 * Aplica uma filtro "filter" na camada "layer" desta imagem
 * 
 * @filter o filtro do tipo Filter
 * @layer a camada na imagem no qual o filtro será aplicado
 */
    void apply_filter(const Filter& filter,int filter_layer, int image_layer);
    void apply_filter(cv::Mat filter, int filter_layer, int image_layer);

    cv::Mat get_image() const;
    
/**
 *  Aplica um conjunto de filtros para esta imagem
 *  a entrada é um vetor com um par de filtros de 
 *  filtro e a camada na qual aplicar o filtro
 * 
 * @batch um vetor no qual o elemento é uma tupla e cada nó da tupla é representado por um filtro,
 *        a camada do filtro, a camada da imagem. A camada do filtro será aplicado a respectiva
 *        camada da imagem
 */
    void apply_filter_batch(std::vector<std::tuple<const Filter&, int, int>> batch);


/**
 *  Dimensões desta imagem
 * 
 *  @return retorna cv::Size representando as dimensões da imagem
 */
    cv::Size get_dimensions() const;

    ~Image();

protected:

private:
    std::vector<cv::Mat> m_image_layers;

};

#endif