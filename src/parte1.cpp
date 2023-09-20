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

struct Roteiro{
    int Codigo;
    string Data_hora;
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

    string cpf;
    Passageiro passageiro;

    cout << "Digite o CPF: ";
    cin >> cpf;
    
    for (int i = 0; i < passageiros.size(); i++) {
        if (passageiros[i].Cpf == cpf) {
            cout << "Passageiro já cadastrado!" << endl;
            return;
        }
    }

    passageiro.Cpf = cpf;
    cout << "Digite o Nome: ";
    cin >> passageiro.Nome;
    cout << "Digite a Data de Nascimento: ";
    cin >> passageiro.DtNascimento;
    cout << "Digite o Numero de Autorizacao: ";
    cin >> passageiro.NumAutorizacao;
    
    passageiros.push_back(passageiro);
    cout << "Passageiro incluído com sucesso!" << endl;

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
                cin >> cpf;

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
    cout << "Digite a Data e Hora: ";
    cin >> roteiro.Data_hora;
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
            cout << "Data e Hora: " << roteiros[i].Data_hora << endl;
            cout << "Duracao: " << roteiros[i].Duracao << endl;
            cout << "Origem: " << roteiros[i].Origem << endl;
            cout << "Destino: " << roteiros[i].Destino << endl;
            cout << "-------------------------------------" << endl;
            cout << "Deseja alterar o Codigo? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite o Codigo: ";
                cin >> roteiros[i].Codigo;
            }
            cout << "Deseja alterar a Data e Hora? (S/N): ";
            cin >> opcao;
            if(opcao == 'S' || opcao == 's'){
                cout << "Digite a Data e Hora: ";
                cin >> roteiros[i].Data_hora;
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
            cout << "Data e Hora: " << roteiros[i].Data_hora << endl;
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
            cout << "Data e Hora: " << roteiros[i].Data_hora << endl;
            cout << "Duracao: " << roteiros[i].Duracao << endl;
            cout << "Origem: " << roteiros[i].Origem << endl;
            cout << "Destino: " << roteiros[i].Destino << endl;
            cout << "-------------------------------------" << endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado!" << endl;
}

