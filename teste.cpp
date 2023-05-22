#include "titulos.hpp"
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
            titulos[i].imprimeConteudo();
        // Restante do código

        return 0;
    }
    catch (const std::exception& e)
    {
        cerr << "Erro inesperado: " << e.what() << endl;
    }
    return 1;
}
