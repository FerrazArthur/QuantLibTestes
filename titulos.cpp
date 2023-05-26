#include "titulos.hpp"

Titulo::Titulo(unsigned long id, std::string nome, double valorNominal, unsigned long prazo, double taxaJuros)
{
    this->id = id;
    this->nome = nome;
    this->valorNominal = valorNominal;
    this->prazo = prazo;
    this->taxaJuros = taxaJuros;
}
void Titulo::imprimeConteudo()
{
    std::cout<<"Nome do título: "<<this->nome
    <<"\nId: "<<this->id
    <<"\nValor nominal: "<<this->valorNominal
    <<"\nTaxa de juros: "<<this->taxaJuros
    <<"\nPrazo: "<<this->prazo<<std::endl;
}
//
std::vector<std::string> splitCSVString(std::string linha)
{
    std::vector<std::string> tokens;
    std::string token;
    std::size_t inicio = 0;
    std::size_t fim = 0;
    try
    {
        fim = linha.find(',');//encontra a proxima ocorrencia do caractere que dividirá os tokens
        while(inicio < linha.length())
        {
            //divide a std::string entre os tokens
            tokens.push_back(linha.substr(inicio, fim - inicio));
            //move o controle de inicio para o proximo token
            inicio = fim + 1;
            //procura o próximo divisor
            fim = linha.find(',', inicio);
            if (fim == std::string::npos)//em não encontrando o proximo divisor, teremos apenas mais um token
                fim = linha.length()-1;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado na função splitCSVString: " << e.what() << std::endl;
    }
    return tokens;
}
std::vector<Titulo> lerArquivo(std::string nomeArquivo)
{
    std::vector<Titulo> titulos;
    std::vector<std::string> tokens;
    try
    {
        std::ifstream arquivo(nomeArquivo);
        std::string linha;
        getline(arquivo, linha);//pular a primeira linha com nome das colunas
        while (getline(arquivo, linha))
        {
            tokens = splitCSVString(linha);
            if (tokens.size() != 5)
            {
                throw std::invalid_argument("Arquivo .csv não reconhecido.");
            }

            titulos.push_back(Titulo(stoul(tokens[0]), tokens[1], stod(tokens[2]), stoul(tokens[3]), stod(tokens[4])));
            tokens.clear();
        }
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "Erro na função lerArquivo: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado na função lerArquivo: " << e.what() << std::endl;
    }

    return titulos;
}
int writeCSV(std::vector<std::tuple<std::vector<std::tuple<std::vector<std::tuple<std::string, double>>, QuantLib::Volatility>>, std::string>> precos)
{
    try
    {
        std::ofstream arquivo("dadosPlotar.csv");
        std::string titulo;
        if (arquivo.is_open())
        {
            for(long unsigned i = 0; i < precos.size(); i++)
            {
                arquivo << std::get<1>(precos[i]) << ',';
                for(long unsigned j = 0; j < std::get<0>(precos[i]).size(); j++)
                {
                    if (j != 0) // escreve no começo de cada intervalo de valores, exceto no primeiro
                    {
                        arquivo << ',';
                    }
                    //escreve a volatilidade
                    arquivo << std::get<1>(std::get<0>(precos[i])[j]) << ';';
                    for(long unsigned x = 0; x < std::get<0>(std::get<0>(precos[i])[j]).size(); x++)
                    {
                        if (x != 0)//escreve no começo de cada intervalo de valores, exceto no primeiro
                        {
                            arquivo << ';';
                        }
                        arquivo << std::get<0>(std::get<0>(std::get<0>(precos[i])[j])[x]) << ';' << std::get<1>(std::get<0>(std::get<0>(precos[i])[j])[x]);
                    }
                }
                arquivo << '\n';
            }
            arquivo.close();
            return 0;
        }
        else
        {
            throw std::ofstream::failure("Erro ao abrir o arquivo.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Erro inesperado na função writeCSV: " << e.what() << std::endl;
    }
    return 1;
}