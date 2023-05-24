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

double fluxoCaixa(Titulo titulo)
{
    try{
        return (titulo.valorNominal/pow((1+titulo.taxaJuros), (double)titulo.prazo));
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro inesperado na função fluxoCaixa: " << e.what() << std::endl;
    }
        return 0;
}

