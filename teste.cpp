#include "titulos.hpp"

using namespace QuantLib;

void testarModais(Titulo titulo)
{

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
    Volatility volatility = 1;
    Date maturity = calendar.advance(todaysDate, titulo.prazo, Years);
    DayCounter dayCounter = Actual365Fixed();

    std::string method;

    // Descrição do titulo
    std::cout<<std::endl<<"Titulo: "<<titulo.nome<<std::endl <<"Valor nominal: "<<titulo.valorNominal<<std::endl<<std::endl;
    
    // write column headings
    Size widths[] = { 35, 14 };
    std::cout << std::setw(widths[0]) << std::left << "Method" << std::setw(widths[1]) << std::left << "European"<< std::endl;

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

    // Método do fluxo de caixa
    method = "Fluxo de caixa";
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << fluxoCaixa(titulo) << std::endl;

    // Analytic formulas:

    // Black-Scholes for European
    method = "Black-Scholes";

    europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticEuropeanEngine(bsmProcess)));
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << europeanOption.NPV()<< std::endl;

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
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << europeanOption.NPV()<< std::endl;

    // semi-analytic Heston for European
    method = "Heston semi-analytic";
    ext::shared_ptr<HestonProcess> hestonProcess(new HestonProcess(flatTermStructure, flatDividendTS,underlyingH, volatility*volatility, 1.0, volatility*volatility, 0.001, 0.0));
    ext::shared_ptr<HestonModel> hestonModel(new HestonModel(hestonProcess));

    europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new AnalyticHestonEngine(hestonModel)));
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << europeanOption.NPV()<< std::endl;

    // semi-analytic Bates for European
    method = "Bates semi-analytic";
    ext::shared_ptr<BatesProcess> batesProcess( new BatesProcess(flatTermStructure, flatDividendTS, underlyingH, volatility*volatility, 1.0, volatility*volatility, 0.001, 0.0, 1e-14, 1e-14, 1e-14));
    ext::shared_ptr<BatesModel> batesModel(new BatesModel(batesProcess));

    europeanOption.setPricingEngine(ext::shared_ptr<PricingEngine>(new BatesEngine(batesModel)));
    std::cout << std::setw(widths[0]) << std::left << method << std::fixed << std::setw(widths[1]) << std::setprecision(2) << std::left << europeanOption.NPV()<< std::endl;

}

int main()
{
    /*
     * Código para testar manipulação dos dados no arquivo csv enviado pelo processo seletivo.
     */
    try
    {

        std::vector<Titulo> titulos = lerArquivo("dados_titulos.csv");
        // // for(long unsigned i = 0; i < titulos.size(); i++)
        // //     testarModais(titulos[i]);

        // for (long unsigned i = 0; i < titulos.size(); i++)
        //     titulos[i].imprimeConteudo();
        for (long unsigned i = 0; i < titulos.size(); i++)
        {

            testarModais(titulos[i]);
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }
    return 1;
}
