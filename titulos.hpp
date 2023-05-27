#include <ql/qldefines.hpp>
#if !defined(BOOST_ALL_NO_LIB) && defined(BOOST_MSVC)
#  include <ql/auto_link.hpp>
#endif
#include <ql/instruments/vanillaoption.hpp>
#include <ql/math/integrals/tanhsinhintegral.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanvasicekengine.hpp>
#include <ql/pricingengines/vanilla/analytichestonengine.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/batesengine.hpp>
#include <ql/pricingengines/vanilla/binomialengine.hpp>
#include <ql/pricingengines/vanilla/bjerksundstenslandengine.hpp>
#include <ql/pricingengines/vanilla/fdblackscholesvanillaengine.hpp>
#include <ql/pricingengines/vanilla/integralengine.hpp>
#include <ql/pricingengines/vanilla/mcamericanengine.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/pricingengines/vanilla/qdfpamericanengine.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

struct Titulo
{
    std::string nome = "";
    long unsigned id = 0, prazo = 0;
    double valorNominal = 0, taxaJuros = 0;
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

int writeCSVHeader(std::tuple<std::vector<std::tuple<std::vector<std::tuple<std::string, double>>, QuantLib::Volatility>>, std::string> titulo, std::string header, std::string path);
    /*
     * Input: vetor com tupla (vetor com tupla (vetor com tupla nome do método aplicado e preço obtido) e valor para volatilidade) e nome do titulo;
     * Output: 0 se deu tudo certo, 1 se deu errado
     * Escreve o conteúdo do vetor em um arquivo csv para cada título, onde cada linha é uma precificaçao, composta por NOME DO MODELO, VOLATILIDADE, PREÇO 
     */

int writeCSV(std::vector<std::tuple<std::vector<std::tuple<std::vector<std::tuple<std::string, double>>, QuantLib::Volatility>>, std::string>> precos);
    /*
     * Input: vetor com tupla (vetor com tupla (vetor com tupla nome do método aplicado e preço obtido) e valor para volatilidade) e nome do titulo;
     * Output: 0 se deu tudo certo, 1 se deu errado
     * Escreve o conteúdo do vetor em um arquivo csv, onde cada linha é um titulo, as virgulas dividem por volatilidade e ; divide por metodo
     */