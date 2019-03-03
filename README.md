
# Filter Tester
                                                     

Este projeto possibilita a aplicação simples de filtros (Kernels) em imagens.

A configuração é realizada através do arquivo de configuação: <path>/configuration/config.cfg
  Neste arquivo, deve conter os seguintes variáveis:
  
    image   -> path/to/image;
    map     -> path/to/map;
    filters -> path/to/blur.frt,
               path/to/motion.frt,
               path/to/find_edge.frt;
               
  A sintaxe é simples. 
  
  >O id da variável está a esquerda do operador de atribuição (->) e pode ser uma identificador único. Não há limitações no nome   das variáveis. Elas podem iniciar com números ([0-9]) ou caracteres especiais (!@#$%).
  
  >Os elementos do lado direito do operador de atribuição são os values. Eles podem ser um único valor ou uma lista de valores.   Caso seja uma lista de valores, eles devem ser separados por virgula (,).
  
  >Toda a declaração de variável deve finalizar com um ponto-e-virgula (;).
  
## As varíaveis que devem estar presente depende da semântica do arquivo.

###### Config file (*.cfg)
  Um arquivo de configuração (**config.cfg**) deve possuir:  
  - image: o diretório para a imagem
  - map:   o diretório para o arquivo de map, um arquivo que relaciona as camadas do filtro às camadas da imagem
  - filters: uma lista de arquivos de filtros
    
    
###### Map Layer file (*.cfg)
  Um arquivo de mapas (**layer_map**) deve possuir:
  > O arquivo de mapas permite duplicação de varíaveis por uma razão que será explicada a seguir.
  - A sintaxe das variaveis de mapa é: 
  ```
  [filter_id].[filter_layer] -> image.[image_layer] 
  ```
  - Onde:
    - filter_id: é o id do filtro (será falado mais à diante)
    - filter_layer: é a camada do filtro que será aplicado a alguma camada da imagem
    - image_layer: é a camada da imagem na qual será aplicado a respectiva camada do filtro
    
    Ex: 
    ```
    blur.0 -> image.0
    blur.0 -> image.1
    blur.0 -> image.2
    ```
    > Neste exemplo, a camada 0 do filtro (este filtro possui apenas uma camada) é aplicado às camadas 0, 1, 2 da imagem, o que corresponde aos canais RGB.
    
    > A razão do arquivo aceitar duplicação de variáveis é permitir uma mesma camada de um filtro ser aplicado a multiplas camadas da imagem
    
##### Filter file (*.frt)
    
    
