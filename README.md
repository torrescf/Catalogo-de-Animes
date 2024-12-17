# Catálogo de Animes

Este é um projeto de gerenciamento de registros de animes, desenvolvido para aplicar conceitos fundamentais de programação como alocação dinâmica, algoritmos de ordenação e busca, e manipulação de arquivos.

## Funcionalidades

- **Alocação Dinâmica:**
  O vetor que armazena os registros de animes utiliza alocação dinâmica, permitindo que o programa expanda sua capacidade conforme novos animes são adicionados.

- **Ordenação com Quick Sort:**
  Implementação do algoritmo Quick Sort para organizar os registros, facilitando a consulta e a manutenção dos dados.

- **Busca Binária:**
  Localização eficiente de registros específicos no catálogo, aumentando a performance em consultas.

- **Persistência de Dados:**
  Leitura e escrita de registros em arquivos para garantir que os dados sejam mantidos entre execuções do programa.

- **Adicionação de Animes:**
  Permite aos usuários expandir o catálogo com novos registros de animes.

## Requisitos

- Compilador C++ compatível com padrão C++11 ou superior.
- Sistema operacional Windows, Linux ou macOS.

## Como executar o projeto

1. Clone o repositório:
   ```bash
   git clone https://github.com/torrescf/Catalogo-de-Animes.git
   ```

2. Navegue até o diretório do projeto:
   ```bash
   cd Catalogo-de-Animes
   ```

3. Compile o código-fonte:
   ```bash
   g++ -o catalogo main.cpp
   ```

4. Execute o programa:
   ```bash
   ./catalogo
   ```

## Estrutura do Projeto

- `main.cpp`:
  Arquivo principal do programa, contendo a implementação das funcionalidades descritas.

- `data/`:
  Diretório para armazenamento dos arquivos de dados persistentes.

## Funcionalidades Futuras

- Implementação de interface gráfica para maior usabilidade.
- Exportação dos registros em formatos como CSV ou JSON.
- Integração com APIs para buscar informações automáticas sobre animes.
