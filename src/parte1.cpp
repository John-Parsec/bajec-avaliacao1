#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Passageiro{
    string Cpf;
    string Nome;
    int DtNascimento;
    int NumAutorizacao;
};


void IncluirPassageiro(vector<Passageiro> &passageiros);
void ExcluirPassageiro(vector<Passageiro> &passageiros);
void AlterarPassageiro(vector<Passageiro> &passageiros);
void ListarPassageiro(vector<Passageiro> &passageiros);
void LocalizarPassageiro(vector<Passageiro> &passageiros);

int main(){

    vector<Passageiro> passageiros;

    int opcao = 0;

    do {
        cout << "1 - Incluir Passageiro" << endl;
        cout << "2 - Excluir Passageiro" << endl;
        cout << "3 - Alterar Passageiro" << endl;
        cout << "4 - Listar Passageiro" << endl;
        cout << "5 - Localizar Passageiro" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opcao;

        switch(opcao){
            case 0:
                cout << "Saindo..." << endl;
                break;
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
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }while(opcao != 0);
    return 0;
}

void IncluirPassageiro(vector<Passageiro> &passageiros){

    string cpf;
    Passageiro passageiro;

    cout << "Digite o CPF: ";
    cin >> cpf;


    if(passageiros.size() == 0){
        passageiro.Cpf = cpf;
        cout << "Digite o Nome: ";
        cin >> passageiro.Nome;
        cout << "Digite a Data de Nascimento: ";
        cin >> passageiro.DtNascimento;
        cout << "Digite o Numero de Autorizacao: ";
        cin >> passageiro.NumAutorizacao;
        passageiros.push_back(passageiro);
        cout << "Passageiro incluido com sucesso!" << endl;
        return;
    }
    else{
        for(int i = 0; i < passageiros.size(); i++){
            if(passageiros[i].Cpf == cpf){
                cout << "Passageiro ja cadastrado!" << endl;
                return;
            }
            passageiro.Cpf = cpf;
            cout << "Digite o Nome: ";
            cin >> passageiro.Nome;
            cout << "Digite a Data de Nascimento: ";
            cin >> passageiro.DtNascimento;
            cout << "Digite o Numero de Autorizacao: ";
            cin >> passageiro.NumAutorizacao;
            passageiros.push_back(passageiro);
            cout << "Passageiro incluido com sucesso!" << endl;
            return;
        }
    }
}

void ExcluirPassageiro(vector<Passageiro> &passageiros){
    string cpf;
    cout << "Digite o CPF: ";
    cin >> cpf;

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
    string cpf;
    char opcao;
    cout << "Digite o CPF: ";
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
                cout << "Digite o CPF: ";
                cin >> passageiros[i].Cpf;
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
                cout << "Digite a Data de Nascimento: ";
                cin >> passageiros[i].DtNascimento;
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
    cout << "Digite o CPF: ";
    cin >> cpf;

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