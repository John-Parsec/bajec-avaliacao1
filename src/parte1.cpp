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


void IncluirPassageiro();
void ExcluirPassageiro();
void AlterarPassageiro();
void ListarPassageiro();
void LocalizarPassageiro();

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
                IncluirPassageiro();
                break;
            case 2:
                ExcluirPassageiro();
                break;
            case 3:
                AlterarPassageiro();
                break;
            case 4:
                ListarPassageiro();
                break;
            case 5:
                LocalizarPassageiro();
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }while(opcao != 0);
    return 0;
}

