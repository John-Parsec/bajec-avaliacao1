#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct roteiro{
    string Codigo;
    string Duracao_Prevista;
    string Data;
    string Hora;
    string Origem;
    string Destino;
};

bool verificar_data(string data)
{
    std::string d, m, a, str;
    int id, im, ia;
    bool valido = 1;

    str = data;

    if(data.size() != 10)
    {
        valido = 0;
    }
    else
    {
        d = str.substr(0, 2);
        m = str.substr(3, 2);
        a = str.substr(6, 4);

        id = stoi(d);
        im = stoi(m);
        ia = stoi(a);
    }

    if(im < 1 || im > 12 || id < 1 || id > 31)
        valido = 0;

    if(valido && (im == 4 || im == 6 || im == 9 || im == 11) && id > 30)
        valido = 0;

    if(valido && im == 2)
    {
        if (ia % 4 == 0 && id > 29)
            valido = 0;
        else if (ia % 4 !=0 && id > 28)
            valido = 0;
    }

    return valido;
}

bool verificar_hora(string hora)
{
    std::string hr, min, str;
    int ihr, imin;
    bool valido = 1;

    str = hora;

    if(str.size() != 10)
    {
        valido = 0;
    }
    else
    {
        hr = str.substr(0, 2);
        min = str.substr(3, 2);

        ihr = stoi(hr);
        imin = stoi(min);
    }

    if(imin < 0 || imin > 59)
        valido = 0;

    if(ihr < 0 || ihr > 23)
        valido = 0;

    return valido;
}

bool verificar_codigo(string codigo)
{
    bool valido = 1;
    if(codigo.size() != 11) {valido = 0;}
    for(int i = 0; i < 11 && valido; i++)
    {
        if(codigo[i] < 48 || codigo[i] > 57) {valido = 0;}
    }

    return valido;
}

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
    while(!verificar_codigo(novo.Codigo))
    {
        std::cout << "Codigo invalido, insira novamente (11 numeros): ";
        std::cin >> novo.Codigo;
    }
    for(int i = 0; i < vec.size(); i++)
    {
        if(novo.Codigo == vec[i].Codigo)
        {
            std::cout << "Esse codigo já existe, por favor insira outro: ";
            std::cin >> novo.Codigo;
            while(!verificar_codigo(novo.Codigo))
            {
                std::cout << "Codigo invalido, insira novamente (11 numeros): ";
                std::cin >> novo.Codigo;
            }
            i = -1;
        }
    }

    std::cout << "Data: ";
    std::cin >> novo.Data;
    while(!verificar_data(novo.Data))
            {
                std::cout << "Data invalida, insira novamente (dd/mm/aaaa): ";
                std::cin >> novo.Data;
            }

    std::cout << "Hora: ";
    std::cin >> novo.Hora;
    while(!verificar_hora(novo.Hora))
            {
                std::cout << "Hora invalida, insira novamente (hh:mm): ";
                std::cin >> novo.Data;
            }
            
    std::cout << "Duracao prevista: ";
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
            std::cout << "Data prevista: " << vec[i].Data << endl;
            std::cout << "Hora prevista: " << vec[i].Hora << endl;
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
            while(!verificar_codigo(Codigo))
            {
                std::cout << "Codigo invalido, insira novamente (11 numeros): ";
                std::cin >> Codigo;
            }
            for(int i = 0; i < vec.size(); i++)
            {
                if(Codigo == vec[i].Codigo && i!=index)
                {
                    std::cout << "Esse Codigo já existe, por favor insira outro: ";
                    std::cin >> Codigo;
                    while(!verificar_codigo(Codigo))
                    {
                        std::cout << "Codigo invalido, insira novamente (11 numeros): ";
                        std::cin >> Codigo;
                    }
                    i = -1;
                }
            } 
            vec[index].Codigo = Codigo;
        }

        std::cout << "Deseja alterar a Data prevista? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Data: ";
            std::cin >> vec[index].Data;
            while(!verificar_data(vec[index].Data))
            {
                std::cout << "Data invalida, insira novamente (dd/mm/aaaa): ";
                std::cin >> vec[index].Data;
            }
        }

        std::cout << "Deseja alterar a Hora prevista? (sim = 1 / nao = 0): ";
        std::cin >> acao;
        if(acao)
        {
            std::cout << "Hora: ";
            std::cin >> vec[index].Hora;
            while(!verificar_hora(vec[index].Hora))
            {
                std::cout << "Hora invalida, insira novamente (hh:mm): ";
                std::cin >> vec[index].Data;
            }            
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
        std::cout << "Data: " << vec[i].Data << endl;
        std::cout << "Hora: " << vec[i].Hora << endl;
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
            std::cout << "Data prevista: " << vec[i].Data << endl;
            std::cout << "Hora prevista: " << vec[i].Hora << endl;
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