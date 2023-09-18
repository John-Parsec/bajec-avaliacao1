#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct passageiro{
    string CPF;
    string Nome;
    string DtNascimento;
    string NumAutorizacao;
};

string randCPF()
{
    string cpf;
    for(int i = 0; i < 11; i++)
        cpf += ((rand()%10) + 48);

    return cpf;
}

void incluir_passageiro(vector<passageiro>& vec)
{
    std::cout << endl;
    passageiro novo;
    std::cout << "Nome: ";
    std::getline(cin >> ws, novo.Nome);
    std::cout << "CPF: ";
    std::cin >> novo.CPF;
    std::cout << "Data de nascimento (dd/mm/aaaa): ";
    std::cin >> novo.DtNascimento;

    string dataaux = novo.DtNascimento.substr(6, 4);
    if(stoi(dataaux) > 2005)
    {  
        std::cout << "Numero de autorizacao: ";
        std::cin >> novo.NumAutorizacao;

    }

    vec.push_back(novo);

    bool incluirNovo;
    std::cout << "Passageiro incluido com sucesso, deseja incluir mais alguém? (sim = 1 / nao = 0): ";
    std::cin >> incluirNovo;
    if(incluirNovo) 
        {incluir_passageiro(vec);}
}

void excluir_passageiro(vector<passageiro>& vec)
{
    std::cout << endl;

    string  cpf;
    std::cout << "Digite o CPF do passageiro: "; 
    std::cin >> cpf;

    bool check = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].CPF == cpf)
        {
            vec.erase(vec.begin() + i);
            i += vec.size();
            check = 1;
        }
    }

    bool excluirNovo;
    if(!check)
        std::cout << "CPF nao encontrado, deseja tentar de novo? (sim = 1 / nao = 0): ";
    else
        std::cout << "Passageiro excluido com sucesso, deseja excluir outro? (sim = 1 / nao = 0): ";

    std::cin >> excluirNovo;
    if(excluirNovo) {(excluir_passageiro(vec));}
}

void alterar_passageiro(vector<passageiro>& vec)
{
    std::cout << endl;

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << "CPF: " << vec[i].CPF << endl;
        std::cout << "Nome: " << vec[i].Nome << endl;
        std::cout << "Data de Nascimento: " << vec[i].DtNascimento << endl;

        string dataaux = vec[i].DtNascimento.substr(6, 4);
        if(stoi(dataaux) > 2005)
        {  
            std::cout << "Numero de autorizacao: " << vec[i].NumAutorizacao << endl;
        }   

        std::cout << "-------------------------" << endl << endl;
    }
}

void listar_passageiro(vector<passageiro>& vec)
{
    std::cout << endl;

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << "CPF: " << vec[i].CPF << endl;
        std::cout << "Nome: " << vec[i].Nome << endl;
        std::cout << "Data de Nascimento: " << vec[i].DtNascimento << endl;

        string dataaux = vec[i].DtNascimento.substr(6, 4);
        if(stoi(dataaux) > 2005)
        {  
            std::cout << "Numero de autorizacao: " << vec[i].NumAutorizacao << endl;
        }   

        std::cout << "-------------------------" << endl << endl;
    }
}

void localizar_passageiro(vector<passageiro>& vec)
{
    std::cout << endl;

    string  cpf;
    std::cout << "Digite o CPF do passageiro: "; 
    std::cin >> cpf;

    bool check = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i].CPF == cpf)
        {
            std::cout << "Nome: " << vec[i].Nome << endl;
            std::cout << "Data de Nascimento: " << vec[i].DtNascimento << endl;

            string dataaux = vec[i].DtNascimento.substr(6, 4);
            if(stoi(dataaux) > 2005)
            {  
                std::cout << "Numero de autorizacao: " << vec[i].NumAutorizacao << endl;
            }

            i += vec.size();
            check = 1;
        }
    }

    bool localizarNovo;
    if(!check)
        std::cout << "CPF nao encontrado, deseja tentar de novo? (sim = 1 / nao = 0): ";
    else
        std::cout << "Passageiro encontrado com sucesso, deseja localizar outro? (sim = 1 / nao = 0): ";

    std::cin >> localizarNovo;
    if(localizarNovo) {(localizar_passageiro(vec));}
}

int main()
{
    vector<passageiro> lista;

    std::cout << "Cadastre um passageiro: " << endl;
    incluir_passageiro(lista);

    
    for(int acao = -1; acao != 0;)
    {

        std::cout << endl << "O que deseja fazer?" << endl <<
        "(1) Incluir um passageiro" << endl <<
        "(2) Excluir um passageiro" << endl <<
        "(3) Alterar um passageiro" << endl <<
        "(4) Listar todos os passageiros" << endl <<
        "(5) Localizar um passageiro" << endl <<
        "(0) Sair" << endl;

        std::cin >> acao;

        if(acao == 1)
            incluir_passageiro(lista);
        else if(acao == 2)
            excluir_passageiro(lista);
        else if(acao == 3)
            alterar_passageiro(lista);
        else if(acao == 4)
            listar_passageiro(lista);
        else if(acao == 5)
            localizar_passageiro(lista);
    }

    std::cout << "Oprecacao finalizada" << endl;
    return 0;
}