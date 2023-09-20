#include <iostream>
#include <vector>

using namespace std;

struct date{
    int dia;
    int mes;
    int ano;
};

struct hora{
    int hora;
    int minuto;
};

struct data_hora{
    date d;
    hora h;
};

struct passageiro{
    string nome;
    char cpf[12];
    date dataNascimento;
    int numAutorizacao;
};

struct roteiro{
    string origem;
    string destino;
    string codigo;
    data_hora data_horaPrevista;
    float duracao;
};

bool validaData(string data);
bool validaHora(string data_hora);
bool validaDataHora(string data_hora);
bool validaCPF(string cpf);
date stringToDate(string str);
hora stringToHora(string str);
string dateToString(date d);
string horaToString(hora h);
string dataHoraToString(data_hora dh);
data_hora stringToDataHora(string str);
string cpfNum(string cpf);

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

bool validaData(date data){
    int dia, mes, ano;

    dia = data.dia;
    mes = data.mes;
    ano = data.ano;

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


bool validaHora(hora h){
    int hora, minuto;

    hora = h.hora;
    minuto = h.minuto;

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

bool validaDataHora(data_hora dh){
    date d;
    hora h;

    d = dh.d;
    h = dh.h;

    if(!validaData(d)){
        return false;
    }
    else if(!validaHora(h)){
        return false;
    }

    return true;
}

date stringToDate(string str){
    date d;
    string aux;
    int i = 0, j = 1;

    for(i = 0; i < str.length(); i++){
        aux += str[i];

        if(str[i] == '/'){
            if(j == 1){
                d.dia = stoi(aux);
                j++;
            }
            else{
                d.mes = stoi(aux);
            }
            aux = "";
        }

    }

    d.ano = stoi(aux);

    return d;
}

hora stringToHora(string str){
    hora h;
    string aux;
    int i;

    for(i = 0; i < str.length(); i++){
        aux += str[i];

        if(str[i] == ':'){
            h.hora = stoi(aux);
            aux = "";
        }
    }

    h.minuto = stoi(aux);

    return h;
}

string dateToString(date d){
    string str;

    str = to_string(d.dia) + "/" + to_string(d.mes) + "/" + to_string(d.ano);

    return str;
}


string horaToString(hora h){
    string str;

    str = to_string(h.hora) + ":" + to_string(h.minuto);

    return str;
}

data_hora stringToDataHora(string str){
    data_hora dh;
    string aux;
    int i;

    for(i = 0; i < str.length(); i++){
        aux += str[i];

        if(str[i] == ' '){
            dh.d = stringToDate(aux);
            aux = "";
        }
    }
            
    dh.h = stringToHora(aux);
    aux = "";

    return dh;
}

string dataHoraToString(data_hora dh){
    string str;

    str = dateToString(dh.d) + " " + horaToString(dh.h);

    return str;
}

string cpfNum(string cpf){
    string numCPF;

    for(int i = 0 ; i < cpf.length(); i++){
        if(cpf[i] != '.' && cpf[i] != '-'){
            numCPF += cpf[i];
        }
    }

    return numCPF;
}

bool validaCPF(string cpf){
    int i, j, k, soma = 0, digito1, digito2;
    int cpfInt[11];
    string cpfNumStr; 

    cpfNumStr = cpfNum(cpf);

    for(i = 0; i < 11; i++){
        cpfInt[i] = cpfNumStr[i] - '0';
    }

    for(i = 0, j = 10; i < 9; i++, j--){
        soma += cpfInt[i] * j;
    }

    digito1 = 11 - (soma % 11);

    if(digito1 > 9){
        digito1 = 0;
    }

    soma = 0;

    for(i = 0, j = 11; i < 10; i++, j--){
        soma += cpfInt[i] * j;
    }

    digito2 = 11 - (soma % 11);

    if(digito2 > 9){
        digito2 = 0;
    }

    if(digito1 == cpfInt[9] && digito2 == cpfInt[10]){
        return true;
    }
    else{
        return false;
    }
}

bool cpfIsUnique(vector<passageiro> &passageiros, string cpf){
    for(auto it = passageiros.begin(); it != passageiros.end(); it++){
        if(it->cpf == cpf){
            return false;
        }
    }

    return true;
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
    string dataNascimento;
    cout << "Nome: ";
    cin >> p.nome;
    cout << "CPF: ";
    cin >> p.cpf;

    if(!validaCPF(p.cpf)){
        cout << "CPF inválido!" << endl;
        return;
    }

    if(!cpfIsUnique(passageiros, p.cpf)){
        cout << "CPF já cadastrado!" << endl;
        return;
    }

    cout << "Data de nascimento (dd/mm/aaaa): ";
    cin >> dataNascimento;

    p.dataNascimento = stringToDate(dataNascimento);

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
    else{
        p.numAutorizacao = 0;
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
    string dataNascimento;
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
                cin >> dataNascimento;
                it->dataNascimento = stringToDate(dataNascimento);
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
        cout << "Data de nascimento: " << dateToString(it->dataNascimento) << endl;
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
            cout << "Data de nascimento: " << dateToString(it->dataNascimento) << endl;
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
    string data_hora;

    cout << "Origem: ";
    cin >> r.origem;
    cout << "Destino: ";
    cin >> r.destino;
    cout << "Código: ";
    cin >> r.codigo;
    cout << "Data e hora prevista (dd/mm/aaaa hh:mm): ";
    cin >> data_hora;

    r.data_horaPrevista = stringToDataHora(data_hora);

    if(!validaDataHora(r.data_horaPrevista)){
        cout << "Data inválida!" << endl;
        return;
    }

    cout << "Duração: ";
    cin >> r.duracao;

    roteiros.push_back(r);
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
    string data_hora;
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
                cin >> data_hora;
                it->data_horaPrevista = stringToDataHora(data_hora);
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
        cout << "Data e hora prevista: " << dataHoraToString(it->data_horaPrevista) << endl;
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
            cout << "Data e hora prevista: " << dataHoraToString(it->data_horaPrevista) << endl;
            cout << "Duração: " << it->duracao << endl;
            achou = true;
            break;
        }
    }

    if(!achou){
        cout << "\nRoteiro não encontrado!" << endl;
    }
}