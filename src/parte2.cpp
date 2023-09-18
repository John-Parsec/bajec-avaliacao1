#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct roteiro{
    string Codigo;
    string Duracao_Prevista;
    string Data_Hora_prevista;
    string Origem;
    string Destino;
};

void incluir_roteiro(vector<roteiro>& vec)
{
    std::cout << endl;
    roteiro novo;
    std::cout << "Origem: ";
    std::getline(cin >> ws, novo.Origem);
    std::cout << "Destino: ";
    std::getline(cin >> ws, novo.Destino);
    std::cout << "Codigo: ";
    std::cin >> novo.Codigo;
    for(int i = 0; i < vec.size(); i++)
    {
        if(novo.Codigo == vec[i].Codigo)
        {
            std::cout << "Esse codigo já existe, por favor insira outro: ";
            std::cin >> novo.Codigo;
            i = -1;
        }
    }

    std::cout << "Data/hora prevista: ";
    std::cin >> novo.Data_Hora_prevista;

    std::cout << "Numero de autorizacao: ";
    std::cin >> novo.Duracao_Prevista;

    vec.push_back(novo);

    bool incluirNovo;
    std::cout << "Roteiro incluido com sucesso, deseja incluir mais algum?? (sim = 1 / nao = 0): ";
    std::cin >> incluirNovo;
    if(incluirNovo) 
        {incluir_roteiro(vec);}
}

void excluir_roteiro(vector<roteiro>& vec)
{
    std::cout << endl;

    string Codigo;
    std::cout << "Digite o codigo do roteiro: "; 
    std::cin >> Codigo;

    bool check = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].Codigo == Codigo)
        {
            vec.erase(vec.begin() + i);
            i += vec.size();
            check = 1;
        }
    }

    bool excluirNovo;
    if(!check)
        std::cout << "Codigo nao encontrado, deseja tentar de novo? (sim = 1 / nao = 0): ";
    else
        std::cout << "Roteiro excluido com sucesso, deseja excluir outro? (sim = 1 / nao = 0): ";

    std::cin >> excluirNovo;
    if(excluirNovo) {(excluir_roteiro(vec));}
}

void alterar_roteiro(vector<roteiro>& vec)
{
    std::cout << endl;

    string  Codigo;
    std::cout << "Digite o Codigo do roteiro: "; 
    std::cin >> Codigo;

    bool check = 0;
    int index;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].Codigo == Codigo)
        {
            std::cout << "Origem: " << vec[i].Origem << endl;
            std::cout << "Destino: " << vec[i].Destino << endl;
            std::cout << "Data/hora prevista: " << vec[i].Data_Hora_prevista << endl;
            std::cout << "Duracao prevista: " << vec[i].Duracao_Prevista << endl;

            index = i;
            i += vec.size();
            check = 1;
        }
    }

    if(check)
    {
        bool acao = 0;
        std::cout << "Deseja alterar a origem? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Origem: ";
            std::cin >> vec[index].Origem;
        }

        std::cout << "Deseja alterar o destino? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Destino: ";
            std::cin >> vec[index].Destino;
        }

        std::cout << "Deseja alterar o Codigo? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            string Codigo;
            std::cout << "Codigo: ";
            std::cin >> Codigo;
            for(int i = 0; i < vec.size(); i++)
            {
                if(Codigo == vec[i].Codigo && i!=index)
                {
                    std::cout << "Esse Codigo já existe, por favor insira outro: ";
                    std::cin >> Codigo;
                    i = -1;
                }
            } 
            vec[index].Codigo = Codigo;
        }

        std::cout << "Deseja alterar a Data/hora prevista? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Data/hora prevista: ";
            std::cin >> vec[index].Data_Hora_prevista;
        }

        std::cout << "Deseja alterar a Duracao prevista? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Duracao prevista: ";
            std::cin >> vec[index].Duracao_Prevista;
        }
    }

    bool alterarNovo;
    if(!check)
        std::cout << "Codigo nao encontrado, deseja tentar de novo? (sim = 1 / nao = 0): ";
    else
        std::cout << "Roteiro alterado com sucesso, deseja alterar outro? (sim = 1 / nao = 0): ";

    std::cin >> alterarNovo;
    if(alterarNovo) {(alterar_roteiro(vec));}
}

void listar_roteiro(vector<roteiro>& vec)
{
    std::cout << endl;

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << "Codigo: " << vec[i].Codigo << endl;
        std::cout << "Origem: " << vec[i].Origem << endl;
        std::cout << "Destino: " << vec[i].Destino << endl;
        std::cout << "Data/Hora prevista: " << vec[i].Data_Hora_prevista << endl;
        std::cout << "Duracao prevista: " << vec[i].Duracao_Prevista << endl;
        std::cout << "-------------------------" << endl << endl;
    }
}

void localizar_roteiro(vector<roteiro>& vec)
{
    std::cout << endl;

    string  Codigo;
    std::cout << "Digite o Codigo do roteiro: "; 
    std::cin >> Codigo;

    bool check = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].Codigo == Codigo)
        {
            std::cout << "Origem: " << vec[i].Origem << endl;
            std::cout << "Destino: " << vec[i].Origem << endl;
            std::cout << "Data/hora prevista: " << vec[i].Data_Hora_prevista << endl;
            std::cout << "Duracao prevista: " << vec[i].Duracao_Prevista << endl;

            i += vec.size();
            check = 1;
        }
    }

    bool localizarNovo;
    if(!check)
        std::cout << "Codigo nao encontrado, deseja tentar de novo? (sim = 1 / nao = 0): ";
    else
        std::cout << "Roteiro encontrado com sucesso, deseja localizar outro? (sim = 1 / nao = 0): ";

    std::cin >> localizarNovo;
    if(localizarNovo) {(localizar_roteiro(vec));}
}

int main()
{
    vector<roteiro> lista;

    std::cout << "Cadastre um roteiro: " << endl;
    incluir_roteiro(lista);

    
    for(int acao = -1; acao != 0;)
    {

        std::cout << endl << "O que deseja fazer?" << endl <<
        "(1) Incluir um roteiro" << endl <<
        "(2) Excluir um roteiro" << endl <<
        "(3) Alterar um roteiro" << endl <<
        "(4) Listar todos os roteiros" << endl <<
        "(5) Localizar um roteiro" << endl <<
        "(0) Sair" << endl;

        std::cin >> acao;

        if(acao == 1)
            incluir_roteiro(lista);
        else if(acao == 2)
            excluir_roteiro(lista);
        else if(acao == 3)
            alterar_roteiro(lista);
        else if(acao == 4)
            listar_roteiro(lista);
        else if(acao == 5)
            localizar_roteiro(lista);
    }

    std::cout << "Oprecacao finalizada" << endl;
    return 0;
}