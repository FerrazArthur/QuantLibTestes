//#include <ql/quantlib.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Titulo
{
    std::string nome = "";
    long unsigned id = 0, prazo = 0;
    double valorNominal = 0, taxaJuros = 0;
    public:
        Titulo(long unsigned id, std::string nome, double valorNominal, long unsigned prazo, double taxaJuros);
        void imprimeConteudo();
};

std::vector<std::string> splitCSVString(std::string linha);
/* Input: std::string contendo conteúdo de Titulo no formato linha csv
 * Output: vetor de std::strings com conteúdo de Titulo separado em tokens
 * Percorre uma std::string e a divide em substd::strings, utilizando uma virgula como separador
 */

std::vector<Titulo> lerArquivo(std::string nomeArquivo);
    /*
     * Input: std::string com nome do arquivo .csv adequado
     * Output: vetor com os títulos do arquivo armazenados em classes Titulo
     * Realiza a leitura do arquivo que armazena os títulos, onde cada linha é um título e 
     * é composta por: id, nome. valornominal, prazo e taxa de juros, nessa ordem.
     */


