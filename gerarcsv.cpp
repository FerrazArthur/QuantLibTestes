#include "titulos.hpp"

using namespace QuantLib;

std::vector<std::tuple<std::string, double>> precificar(Titulo titulo, Volatility volatility, int imprimir)
{
    /*
     * Input: Titulo com prazo, valor nominal, nome e juros, valor para volatilidade e chave pra imprimir ou nao
     * Output: vector com tupla: <nome do método, custo calculado>
     * Código para calcular o custo de um título por diferentes métodos. se imprimir == 0: imprime detalhes.
     */
    try
    {
        //Output vector com nome do método e custo calculado
        std::vector<std::tuple<std::string, double>> preco;

        // set up dates
        Calendar calendar = TARGET();
        Date todaysDate(23, May, 2023);
        Date settlementDate = todaysDate;
        Settings::instance().evaluationDate() = todaysDate;

        // our options
        Option::Type type(Option::Call);
        Real underlying = titulo.valorNominal;
        Real strike = titulo.valorNominal;
        Spread dividendYield = 0.00;
        Rate riskFreeRate = titulo.taxaJuros;
        //Volatility volatility = 1;
        Date maturity = calendar.advance(todaysDate, titulo.prazo, Years);
        DayCounter dayCounter = Actual365Fixed();

        std::string method;

        // Descrição do titulo 
        std::cout<<std::endl<<"-------------------------------------"<<std::endl;
        std::cout<<"Titulo: "<<titulo.nome<<std::endl;
        if (imprimir == 0)
        {
            std::cout<<"Valor nominal: "<<titulo.valorNominal<<std::endl
            <<"Volatilidade considerada: "<<io::volatility(volatility)<<std::endl
            <<"Vencimento: "<<maturity.dayOfMonth()<<"/"<<maturity.month()<<"/"<<maturity.year()<<std::endl<<std::endl;
        }
        // write column headings
        Size widths[] = { 35, 14 };
        std::cout << std::setw(widths[0]) << std::left << "Método" << std::setw(widths[1]) << std::left << "Preço"<< std::endl;

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));
        
        Handle<Quote> underlyingH(ext::shared_ptr<Quote>(new SimpleQuote(underlying)));

        // bootstrap the yield/dividend/vol curves
        Handle<YieldTermStructure> flatTermStructure(ext::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, riskFreeRate, dayCounter)));
        Handle<YieldTermStructure> flatDividendTS(ext::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, dividendYield, dayCounter)));
        Handle<BlackVolTermStructure> flatVolTS(ext::shared_ptr<BlackVolTermStructure>(new BlackConstantVol(settlementDate, calendar, volatility,dayCounter)));

        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
        ext::shared_ptr<BlackScholesMertonProcess> bsmProcess(new BlackScholesMertonProcess(underlyingH, flatDividendTS,flatTermStructure, flatVolTS));

        // options
        VanillaOption europeanOption(payoff, europeanExercise);

        // Analytic formulas:

        // Black-Scholes for European
        method = "Black Scholes";
        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticEuropeanEngine(bsmProcess)));

        //efetua calculo e salva no vetor preco
        preco.push_back(std::tuple<std::string, double>(method, europeanOption.NPV()));

        std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << std::get<1>(preco.back()) << std::endl;

        //Vasicek rates model for European
        method = "Black Vasicek Model";
        Real r0 = riskFreeRate;
        Real a = 0.001;
        Real b = 0.0005;
        Real sigma_r = 0.0002;
        Real riskPremium = 0.0;
        Real correlation = 0.0;
        ext::shared_ptr<Vasicek> vasicekProcess(new Vasicek(r0, a, b, sigma_r, riskPremium));
        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticBlackVasicekEngine(bsmProcess, vasicekProcess, correlation)));
        
        //efetua calculo e salva no vetor preco
        preco.push_back(std::tuple<std::string, double>(method, europeanOption.NPV()));

        std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << std::get<1>(preco.back()) << std::endl;

        // semi-analytic Heston for European
        method = "Heston semi-analytic";
        ext::shared_ptr<HestonProcess> hestonProcess(new HestonProcess(flatTermStructure, flatDividendTS,underlyingH, volatility*volatility,1.0, volatility*volatility, 0.001, 0.0));
        ext::shared_ptr<HestonModel> hestonModel(new HestonModel(hestonProcess));
        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticHestonEngine(hestonModel)));

        //efetua calculo e salva no vetor preco
        preco.push_back(std::tuple<std::string, double>(method, europeanOption.NPV()));

        std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << std::get<1>(preco.back()) << std::endl;

        // semi-analytic Bates for European
        method = "Bates semi-analytic";
        ext::shared_ptr<BatesProcess> batesProcess( new BatesProcess(flatTermStructure, flatDividendTS, underlyingH, volatility*volatility, 1.0, volatility*volatility, 0.001, 0.0, 1e-14, 1e-14, 1e-14));
        ext::shared_ptr<BatesModel> batesModel(new BatesModel(batesProcess));
        europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new BatesEngine(batesModel)));

        //efetua calculo e salva no vetor preco
        preco.push_back(std::tuple<std::string, double>(method, europeanOption.NPV()));

        std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << std::get<1>(preco.back()) << std::endl;
        return preco;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado na execução da função testarModais" << e.what() << std::endl;
    }
        return {};
}

int main()
{
    /*
     * Código para armazenar um conjunto de testes para cada titulo em arquivos .csv, utilizando os dados no arquivo csv enviado pelo processo seletivo, com diferentes valores para volatilidade.
     */
    try
    {
        std::string header = "MODELO,VARIANCIA,PRECO";
        std::vector<Titulo> titulos = lerArquivo("dados_titulos.csv");

        for (long unsigned i = 0; i < titulos.size(); i++)
        {
            std::vector<std::tuple<std::vector<std::tuple<std::string, double>>, Volatility>> volatil;
            for(int j = 1; j < 100; j += 10)
            {
                volatil.push_back(std::tuple<std::vector<std::tuple<std::string, double>>, Volatility>(precificar(titulos[i], j/100.0, 1), j/100.0));
            }
            
            if (writeCSVHeader(std::tuple<std::vector<std::tuple<std::vector<std::tuple<std::string, double>>, Volatility>>, std::string>(volatil, titulos[i].nome), header, "precos/") != 0)
            {
                throw("Erro ao escrever os preços em arquivo csv.");
            }
            volatil.clear();
        }
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado na execução da main: " << e.what() << std::endl;
    }
    return 1;
}
