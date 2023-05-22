#include "titulos.hpp"
#include <math.h>
using namespace std;
int main()
{
    /*
     * Código para testar manipulação dos dados no arquivo csv enviado pelo processo seletivo.
     */
    try
    {
        vector<Titulo> titulos = lerArquivo("dados_titulos.csv");
        for (long unsigned i = 0; i < titulos.size(); i++)
            titulos[i] .imprimeConteudo();
        for (long unsigned i = 0; i < titulos.size(); i++)
        {
            cout<<"Titulo: "<<titulos[i].nome<<endl;
            cout<<"Preço: "<<(titulos[i].valorNominal/pow((1+(titulos[i].taxaJuros*100)), (double)titulos[i].prazo*30/252.0))<<endl;
        }
        // Restante do código

        return 0;
    }
    catch (const std::exception& e)
    {
        cerr << "Erro inesperado: " << e.what() << endl;
    }
    return 1;
}
