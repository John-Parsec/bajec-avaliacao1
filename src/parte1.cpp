#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Passageiro{
    string Cpf;
    string Nome;
    string DtNascimento;
    int NumAutorizacao;
};

struct data_hora{
    string Data;
    string Hora;
};

struct Roteiro{
    int Codigo;
    data_hora Data_hora;
    string Duracao;
    string Origem;
    string Destino;
};


void MenuPassageiro();
void MenuRoteiro();
void IncluirPassageiro(vector<Passageiro> &passageiros);
void ExcluirPassageiro(vector<Passageiro> &passageiros);
void AlterarPassageiro(vector<Passageiro> &passageiros);
void ListarPassageiro(vector<Passageiro> &passageiros);
void LocalizarPassageiro(vector<Passageiro> &passageiros);
void IncluirRoteiro(vector<Roteiro> &roteiros);
void ExcluirRoteiro(vector<Roteiro> &roteiros);
void AlterarRoteiro(vector<Roteiro> &roteiros);
void ListarRoteiro(vector<Roteiro> &roteiros);
void LocalizarRoteiro(vector<Roteiro> &roteiros);
bool verificar_data(string data);
bool verificar_hora(string hora);
bool verificar_cpf(string cpf);

int main(){
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;
    int opcaoPrincipal = 0, opcao = 0;
    
    while(opcaoPrincipal != 3){
        cout << "1 - Passageiro" << endl;
        cout << "2 - Roteiro" << endl;
        cout << "3 - Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opcaoPrincipal;
        cout << endl;

        switch(opcaoPrincipal){
            case 1:
                do{
                    MenuPassageiro();
                    cin >> opcao;
                    cout << endl;

                    switch(opcao){
                        case 1:
                            IncluirPassageiro(passageiros);
                            break;
                        case 2:
                            ExcluirPassageiro(passageiros);
                            break;
                        case 3:
                            AlterarPassageiro(passageiros);
                            break;
                        case 4:
                            ListarPassageiro(passageiros);
                            break;
                        case 5:
                            LocalizarPassageiro(passageiros);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcao invalida!" << endl;
                            break;
                    }
                } while(opcao != 0);
                break;
            case 2:
                do{
                    MenuRoteiro();
                    cin >> opcao;
                    cout << endl;

                    switch(opcao){
                        case 1:
                            IncluirRoteiro(roteiros);
                            break;
                        case 2:
                            ExcluirRoteiro(roteiros);
                            break;
                        case 3:
                            AlterarRoteiro(roteiros);
                            break;
                        case 4:
                            ListarRoteiro(roteiros);
                            break;
                        case 5:
                            LocalizarRoteiro(roteiros);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcao invalida!" << endl;
                            break;
                    }
                }while(opcao != 0);
                break;
            case 3:
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }
}

void MenuPassageiro(){
    cout << "1 - Incluir Passageiro" << endl;
    cout << "2 - Excluir Passageiro" << endl;
    cout << "3 - Alterar Passageiro" << endl;
    cout << "4 - Listar Passageiro" << endl;
    cout << "5 - Localizar Passageiro" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite a opcao desejada: ";
}

void MenuRoteiro(){
    cout << "1 - Incluir Roteiro" << endl;
    cout << "2 - Excluir Roteiro" << endl;
    cout << "3 - Alterar Roteiro" << endl;
    cout << "4 - Listar Roteiro" << endl;
    cout << "5 - Localizar Roteiro" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite a opcao desejada: ";
}

void IncluirPassageiro(vector<Passageiro> &passageiros){

    string cpf, dtNascimento;
    Passageiro passageiro;

    cout << "Digite o CPF:(11 numeros) ";
    cin >> cpf;
    if(!verificar_cpf(cpf))
    {
        cout << "CPF invalido!" << endl;
        return;
    }

    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiros[i].Cpf == cpf) {
            cout << "Passageiro já cadastrado!" << endl;
            return;
        }
    }

    passageiro.Cpf = cpf;
    cout << "Digite o Nome: ";
    cin >> passageiro.Nome;
    cout << "Digite a Data de Nascimento:(dd/mm/aaaa) ";
    cin >> dtNascimento;

    if(!verificar_data(dtNascimento))
    {
        cout << "Data invalida!" << endl;
        return;
    }

    passageiro.DtNascimento = dtNascimento;
    cout << "Digite o Numero de Autorizacao: ";
    cin >> passageiro.NumAutorizacao;
    
    passageiros.push_back(passageiro);
    cout << "Passageiro incluído com sucesso!" << endl;

}

void ExcluirPassageiro(vector<Passageiro> &passageiros){
    string cpf;
    cout << "Digite o CPF:(11 numeros) ";
    cin >> cpf;

    if(!verificar_cpf(cpf))
    {
        cout << "CPF invalido!" << endl;
        return;
    }

    for(int i = 0; i < passageiros.size(); i++){
        if(passageiros[i].Cpf == cpf){
            passageiros.erase(passageiros.begin() + i);
            cout << "Passageiro excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void AlterarPassageiro(vector<Passageiro> &passageiros){
    string cpf, dtNascimento;
    char opcao;
    cout << "Digite o CPF:(11 numeros) ";
    cin >> cpf;

    for(int i = 0; i < passageiros.size(); i++){
        if(passageiros[i].Cpf == cpf){
            cout << "CPF: " << passageiros[i].Cpf << endl;
            cout << "Nome: " << passageiros[i].Nome << endl;
            cout << "Data de Nascimento: " << passageiros[i].DtNascimento << endl;
            cout << "Numero de Autorizacao: " << passageiros[i].NumAutorizacao << endl;
            cout << "-------------------------------------" << endl;
            cout << "Deseja alterar o CPF? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o CPF:(11 numeros) ";
                cin >> cpf;
                
                if(!verificar_cpf(cpf))
                {
                    cout << "CPF invalido!" << endl;
                    return;
                }

                for(int j = 0; j < passageiros.size(); j++){
                    if(passageiros[j].Cpf == cpf){
                        cout << "Passageiro ja cadastrado!" << endl;
                        return;
                    }
                }
                passageiros[i].Cpf;
            }
            cout << "Deseja alterar o Nome? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o Nome: ";
                cin >> passageiros[i].Nome;
            }
            cout << "Deseja alterar a Data de Nascimento? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Data de Nascimento:(dd/mm/aaaa) ";
                cin >> dtNascimento;

                if(!verificar_data(dtNascimento))
                {
                    cout << "Data invalida!" << endl;
                    return;
                }

                passageiros[i].DtNascimento = dtNascimento;
            }
            cout << "Deseja alterar o Numero de Autorizacao? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o Numero de Autorizacao: ";
                cin >> passageiros[i].NumAutorizacao;
            }
            cout << "Passageiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void ListarPassageiro(vector<Passageiro> &passageiros){
    if(passageiros.size() == 0){
        cout << "Nao ha passageiros cadastrados!" << endl;
        return;
    }
    else{
        for(int i = 0; i < passageiros.size(); i++){
            cout << "CPF: " << passageiros[i].Cpf << endl;
            cout << "Nome: " << passageiros[i].Nome << endl;
            cout << "Data de Nascimento: " << passageiros[i].DtNascimento << endl;
            cout << "Numero de Autorizacao: " << passageiros[i].NumAutorizacao << endl;
            cout << "-------------------------------------" << endl;
        }
    }
}

void LocalizarPassageiro(vector<Passageiro> &passageiros){
    string cpf;
    cout << "Digite o CPF:(11 numeros) ";
    cin >> cpf;

    if(!verificar_cpf(cpf))
    {
        cout << "CPF invalido!" << endl;
        return;
    }

    for(int i = 0; i < passageiros.size(); i++){
        if(passageiros[i].Cpf == cpf){
            cout << "CPF: " << passageiros[i].Cpf << endl;
            cout << "Nome: " << passageiros[i].Nome << endl;
            cout << "Data de Nascimento: " << passageiros[i].DtNascimento << endl;
            cout << "Numero de Autorizacao: " << passageiros[i].NumAutorizacao << endl;
            cout << "-------------------------------------" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado!" << endl;
}

void IncluirRoteiro(vector<Roteiro> &roteiros){
    int codigo;
    Roteiro roteiro;

    cout << "Digite o Codigo: ";
    cin >> codigo;

    for(int i = 0; i < roteiros.size(); i++){
        if(roteiros[i].Codigo == codigo){
            cout << "Roteiro ja cadastrado!" << endl;
            return;
        }
    }

    roteiro.Codigo = codigo;
    cout << "Digite a Data:(dd/mm/aaaa) ";
    cin >> roteiro.Data_hora.Data;
    cout << "Digite a Hora:(hh:mm) ";
    cin >> roteiro.Data_hora.Hora;
    cout << "Digite a Duracao: ";
    cin >> roteiro.Duracao;
    cout << "Digite a Origem: ";
    cin >> roteiro.Origem;
    cout << "Digite o Destino: ";
    cin >> roteiro.Destino;

    roteiros.push_back(roteiro);
    cout << "Roteiro incluido com sucesso!" << endl;
}

void ExcluirRoteiro(vector<Roteiro> &roteiros){
    int codigo;
    cout << "Digite o Codigo: ";
    cin >> codigo;

    for(int i = 0; i < roteiros.size(); i++){
        if(roteiros[i].Codigo == codigo){
            roteiros.erase(roteiros.begin() + i);
            cout << "Roteiro excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

void AlterarRoteiro(vector<Roteiro> &roteiros){
    int codigo;
    char opcao;
    cout << "Digite o Codigo: ";
    cin >> codigo;

    for(int i = 0; i < roteiros.size(); i++){
        if(roteiros[i].Codigo == codigo){
            cout << "Codigo: " << roteiros[i].Codigo << endl;
            cout << "Data: " << roteiros[i].Data_hora.Data << endl;
            cout << "Hora: " << roteiros[i].Data_hora.Hora << endl;
            cout << "Duracao: " << roteiros[i].Duracao << endl;
            cout << "Origem: " << roteiros[i].Origem << endl;
            cout << "Destino: " << roteiros[i].Destino << endl;
            cout << "-------------------------------------" << endl;
            cout << "Deseja alterar o Codigo? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o Codigo: ";
                cin >> codigo;

                for(int j = 0; j < roteiros.size(); j++){
                    if(roteiros[j].Codigo == codigo){
                        cout << "Roteiro ja cadastrado!" << endl;
                        return;
                    }
                }
                roteiros[i].Codigo;
            }
            cout << "Deseja alterar a Data (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Data:(dd/mm/aaaa) ";
                cin >> roteiros[i].Data_hora.Data;
            }
            cout << "Deseja alterar a Hora? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Hora:(hh:mm) ";
                cin >> roteiros[i].Data_hora.Hora;
            }
            cout << "Deseja alterar a Duracao? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Duracao: ";
                cin >> roteiros[i].Duracao;
            }
            cout << "Deseja alterar a Origem? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Origem: ";
                cin >> roteiros[i].Origem;
            }
            cout << "Deseja alterar o Destino? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o Destino: ";
                cin >> roteiros[i].Destino;
            }
            cout << "Roteiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

void ListarRoteiro(vector<Roteiro> &roteiros){
    if(roteiros.size() == 0){
        cout << "Nao ha roteiros cadastrados!" << endl;
        return;
    }
    else{
        for(int i = 0; i < roteiros.size(); i++){
            cout << "Codigo: " << roteiros[i].Codigo << endl;
            cout << "Data: " << roteiros[i].Data_hora.Data << endl;
            cout << "Hora: " << roteiros[i].Data_hora.Hora << endl;
            cout << "Duracao: " << roteiros[i].Duracao << endl;
            cout << "Origem: " << roteiros[i].Origem << endl;
            cout << "Destino: " << roteiros[i].Destino << endl;
            cout << "-------------------------------------" << endl;
        }
    }
}

void LocalizarRoteiro(vector<Roteiro> &roteiros){
    int codigo;
    cout << "Digite o Codigo: ";
    cin >> codigo;

    for(int i = 0; i < roteiros.size(); i++){
        if(roteiros[i].Codigo == codigo){
            cout << "Codigo: " << roteiros[i].Codigo << endl;
            cout << "Data: " << roteiros[i].Data_hora.Data << endl;
            cout << "Hora: " << roteiros[i].Data_hora.Hora << endl;
            cout << "Duracao: " << roteiros[i].Duracao << endl;
            cout << "Origem: " << roteiros[i].Origem << endl;
            cout << "Destino: " << roteiros[i].Destino << endl;
            cout << "-------------------------------------" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

bool verificar_data(string data)
{
    string d, m, a, str;
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

    if(valido && ia > 2023)
        valido = 0;

    return valido;
}

bool verificar_hora(string hora)
{
    string hr, min, str;
    int ihr, imin;
    bool valido = 1;

    str = hora;

    if(str.size() != 5)
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

bool verificar_cpf(string cpf)
{
    bool valido = 1;
    if(cpf.size() != 11) {valido = 0;}
    for(int i = 0; i < 11 && valido; i++)
    {
        if(cpf[i] < 48 || cpf[i] > 57) {valido = 0;}
    }

    return valido;
}