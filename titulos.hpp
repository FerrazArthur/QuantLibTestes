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


double fluxoCaixa(Titulo titulo);
    /*
     *Input: tipo titulo contendo prazo em anos, taxa de juros anuais e valor nominal de um titulo
     *Output: Valor calculado com esses parâmetros utilizando o método do fluxo de caixa.
     */
