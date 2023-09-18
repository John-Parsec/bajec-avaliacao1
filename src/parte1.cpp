#include <iostream>
#include <vector>

using namespace std;

struct passageiro{
    string nome;
    char cpf[12];
    string dataNascimento;
    int numAutorizacao;
};

struct roteiro{
    string origem;
    string destino;
    string codigo;
    string data_horaPrevista;
    float duracao;
};

bool validaData(string data);
bool validaHora(string data_hora);

void gerirPassageiros(vector<passageiro> &passageiros);
void incluirPassageiro(vector<passageiro> &passageiros);
void excluirPassageiro(vector<passageiro> &passageiros);
void alterarPassageiro(vector<passageiro> &passageiros);
void listarPassageiros(vector<passageiro> &passageiros);
void localizarPassageiro(vector<passageiro> &passageiros);

void gerirRoteiros(vector<roteiro> &roteiros);
void incluirRoteiro(vector<roteiro> &roteiros);
void excluirRoteiro(vector<roteiro> &roteiros);
void alterarRoteiro(vector<roteiro> &roteiros);
void listarRoteiros(vector<roteiro> &roteiros);
void localizarRoteiro(vector<roteiro> &roteiros);

int main(void){
    int opt;
    vector<passageiro> passageiros;
    vector<roteiro> roteiros;

    do{
        cout << "Menu de opções" << endl << endl;
        cout << "1. Gerir passageiros." << endl;
        cout << "2. Gerir roteiros." << endl;
        cout << "0. Sair." << endl;
        cin >> opt;

        if(opt == 0){
            return 0;
        }
        else if(opt == 1){
            gerirPassageiros(passageiros);
        }
        else if(opt == 2){
            gerirRoteiros(roteiros);
        }
        else{
            cout << "Opção inválida!" << endl;
        }
    }while(opt!=0);

    return 0;
}

bool validaData(string data){
    int dia, mes, ano;

    dia = stoi(data.substr(0, 2));
    mes = stoi(data.substr(3, 2));
    ano = stoi(data.substr(6, 4));

    if(dia < 1 || dia > 31){
        return false;
    }
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        if(dia > 30){
            return false;
        }
    }
    else if(mes < 1 || mes > 12){
        return false;
    }
    else if(ano < 1900 || ano > 2040){
        return false;
    }
    else if(mes == 2){
        if(dia > 29){
            return false;
        }
        else if(dia == 29){
            if(ano % 4 != 0){
                return false;
            }
            else if(ano % 100 == 0 && ano % 400 != 0){
                return false;
            }
        }
    }

    return true;
    
}

bool validaHora(string data_hora){
    int hora, minuto;

    hora = stoi(data_hora.substr(11, 2));
    minuto = stoi(data_hora.substr(14, 2));

    cout << hora << " " << minuto << endl;

    if(hora < 0 || hora > 23){
        return false;
    }
    else if(minuto < 0 || minuto > 59){
        return false;
    }
    else{
        return true;
    }
}

void gerirPassageiros(vector<passageiro> &passageiros){
    short int opt;

    do{
        //system("clear");
        
        cout << "\n\nMenu de opções (Passageiros)" << endl;
        cout << "1. Incluir." << endl;
        cout << "2. Excluir" << endl;
        cout << "3. Alterar" << endl;
        cout << "4. Listar" << endl;
        cout << "5. Localizar" << endl;
        cout << "0. Sair." << endl;

        cout << "Escolha uma opção: ";
        cin >> opt;

        switch (opt){
            case 0:
                cout << endl;
                break;
            case 1:
                incluirPassageiro(passageiros);
                break;
            case 2:
                excluirPassageiro(passageiros);
                break;
            case 3:
                alterarPassageiro(passageiros);
                break;
            case 4:
                listarPassageiros(passageiros);
                break;
            case 5: 
                localizarPassageiro(passageiros);
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }while(opt != 0);
}

void incluirPassageiro(vector<passageiro> &passageiros){
    passageiro p;
    int idade;

    cout << "Nome: ";
    cin >> p.nome;
    cout << "CPF: ";
    cin >> p.cpf;
    cout << "Data de nascimento (dd/mm/aaaa): ";
    cin >> p.dataNascimento;
    
    if(!validaData(p.dataNascimento)){
        cout << "Data inválida!" << endl;
        return;
    }

    cout << "Idade: ";
    cin >> idade;

    if(idade < 18){
        cout << "Número de autorização: ";
        cin >> p.numAutorizacao;
    }

    passageiros.push_back(p);
}

void excluirPassageiro(vector<passageiro> &passageiros){
    bool achou = false;
    string cpf;
    cout << "CPF: ";
    cin >> cpf;

    for(auto it = passageiros.begin(); it != passageiros.end(); it++){
        if(it->cpf == cpf){
            passageiros.erase(it);
            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nPassageiro não encontrado!" << endl;
    }
    else{
        cout << "\nPassageiro excluído com sucesso!" << endl;
    }

    //system("PAUSE");
}

void alterarPassageiro(vector<passageiro> &passageiros){
    bool achou = false;
    char opt;
    string cpf;
    cout << "CPF: ";
    cin >> cpf;

    for(auto it = passageiros.begin(); it != passageiros.end(); it++){
        if(it->cpf == cpf){
            cout << "Deseja alterar o nome? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Nome: ";
                cin >> it->nome;
            }
            
            cout << "Deseja alterar o CPF? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "CPF: ";
                cin >> it->cpf;
            }
            
            cout << "Deseja alterar a data de nascimento? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Data de nascimento: ";
                cin >> it->dataNascimento;
            }
            
            cout << "Deseja alterar o número de autorização? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Número de autorização: ";
                cin >> it->numAutorizacao;
            }

            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nPassageiro não encontrado!" << endl;
    }
    else{
        cout << "\nDado(s) alterado com sucesso!" << endl;
    }

    //system("PAUSE");
}

void listarPassageiros(vector<passageiro> &passageiros){
    cout << endl;

    for(auto it = passageiros.begin(); it != passageiros.end(); it++){
        cout << "Nome: " << it->nome << endl;
        cout << "CPF: " << it->cpf << endl;
        cout << "Data de nascimento: " << it->dataNascimento << endl;
        cout << "Número de autorização: " << it->numAutorizacao << endl;
    }

    //system("PAUSE");
}

void localizarPassageiro(vector<passageiro> &passageiros){
    bool achou = false;
    string cpf;
    cout << "CPF: ";
    cin >> cpf;

    for(auto it = passageiros.begin(); it != passageiros.end(); it++){
        if(it->cpf == cpf){
            cout << "Nome: " << it->nome << endl;
            cout << "CPF: " << it->cpf << endl;
            cout << "Data de nascimento: " << it->dataNascimento << endl;
            cout << "Número de autorização: " << it->numAutorizacao << endl;
            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nPassageiro não encontrado!" << endl;
    }
}

void gerirRoteiros(vector<roteiro> &roteiros){
    short int opt;

    do{
        system("clear");
        
        cout << "\n\nMenu de opções (Roteiros)" << endl;
        cout << "1. Incluir." << endl;
        cout << "2. Excluir" << endl;
        cout << "3. Alterar" << endl;
        cout << "4. Listar" << endl;
        cout << "5. Localizar" << endl;
        cout << "0. Sair." << endl;

        cout << "Escolha uma opção: ";
        cin >> opt;

        switch (opt){
            case 0:
                cout << endl;
                break;
            case 1:
                incluirRoteiro(roteiros);
                break;
            case 2:
                excluirRoteiro(roteiros);
                break;
            case 3:
                alterarRoteiro(roteiros);
                break;
            case 4:
                listarRoteiros(roteiros);
                break;
            case 5: 
                localizarRoteiro(roteiros);
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }while(opt != 0);
}

void incluirRoteiro(vector<roteiro> &roteiros){
    roteiro r;

    cout << "Origem: ";
    cin >> r.origem;
    cout << "Destino: ";
    cin >> r.destino;
    cout << "Código: ";
    cin >> r.codigo;
    cout << "Data e hora prevista (dd/mm/aaaa hh:mm): ";
    cin >> r.data_horaPrevista;
    if(!validaData(r.data_horaPrevista)){
        cout << "Data inválida!" << endl;
        return;
    }
    cout << "Duração: ";
    cin >> r.duracao;

    roteiros.push
    if(!validaHora(r.data_horaPrevista)){
        cout << "Hora inválida!" << endl;
        return;
    }_back(r);
}

void excluirRoteiro(vector<roteiro> &roteiros){
    bool achou = false;
    string codigo;
    cout << "Código: ";
    cin >> codigo;

    for(auto it = roteiros.begin(); it != roteiros.end(); it++){
        if(it->codigo == codigo){
            roteiros.erase(it);
            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nRoteiro não encontrado!" << endl;
    }
    else{
        cout << "\nRoteiro excluído com sucesso!" << endl;
    }

    //system("PAUSE");
}

void alterarRoteiro(vector<roteiro> &roteiros){
    bool achou = false;
    char opt;
    string codigo;
    cout << "Código: ";
    cin >> codigo;

    for(auto it = roteiros.begin(); it != roteiros.end(); it++){
        if(it->codigo == codigo){
            cout << "Deseja alterar a origem? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Origem: ";
                cin >> it->origem;
            }
            
            cout << "Deseja alterar o destino? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Destino: ";
                cin >> it->destino;
            }
            
            cout << "Deseja alterar o código? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Código: ";
                cin >> it->codigo;
            }
            
            cout << "Deseja alterar a data e hora prevista? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Data e hora prevista: ";
                cin >> it->data_horaPrevista;
            }
            
            cout << "Deseja alterar a duração? (s/n): ";
            cin >> opt;
            if(opt == 's'){
                cout << "Duração: ";
                cin >> it->duracao;
            }

            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nRoteiro não encontrado!" << endl;
    }
    else{
        cout << "\nDado(s) alterado com sucesso!" << endl;
    }

    //system("PAUSE");
}

void listarRoteiros(vector<roteiro> &roteiros){
    cout << endl;

    for(auto it = roteiros.begin(); it != roteiros.end(); it++){
        cout << "Origem: " << it->origem << endl;
        cout << "Destino: " << it->destino << endl;
        cout << "Código: " << it->codigo << endl;
        cout << "Data e hora prevista: " << it->data_horaPrevista << endl;
        cout << "Duração: " << it->duracao << endl;
    }

    //system("PAUSE");
}

void localizarRoteiro(vector<roteiro> &roteiros){
    bool achou = false;
    string codigo;
    cout << "Código: ";
    cin >> codigo;

    for(auto it = roteiros.begin(); it != roteiros.end(); it++){
        if(it->codigo == codigo){
            cout << "Origem: " << it->origem << endl;
            cout << "Destino: " << it->destino << endl;
            cout << "Código: " << it->codigo << endl;
            cout << "Data e hora prevista: " << it->data_horaPrevista << endl;
            cout << "Duração: " << it->duracao << endl;
            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nRoteiro não encontrado!" << endl;
    }
}