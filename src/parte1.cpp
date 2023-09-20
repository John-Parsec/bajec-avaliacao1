#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Data{
    short int dia;
    short int mes;
    int ano;
};

struct Hora{
    short int hora;
    short int minuto;
};

struct DataHora{
    Data data;
    Hora horario;
};

struct Passageiro{
    string CPF;
    string nome;
    Data DtNascimento;
    string NumAutorizacao = "";
};

struct Roteiro{
    string codigo;
    DataHora datahora;
    Hora duracao;
    string origem;
    string destino;
};

bool addPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao);
bool deletePassageiro(vector<Passageiro> &passageiros, string CPF);
bool alteraPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao);
bool inicializaPassageiro(Passageiro &pas, string CPF, string nome, short int dia, short int mes, int ano, string NumAutorizacao);
bool inicializaData(Data &data, short int dia, short int mes, int ano);
bool inicializaHora(Hora &Hora, short int hora, short int minuto);
bool inicializaDataHora(DataHora &datahora, short int min, short int hora, short int dia, short int mes, int ano);
bool inicializaRoteiro(Roteiro &rot, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino);
bool validaDataHora(DataHora datahora);
bool validarData(short int dia, short int mes, int ano);
bool validaHora(short int hora, short int minuto);
bool validaDuracao(short int hora, short int minuto);
bool incializaDuracao(Hora &duracao, short int hora, short int minuto);
void menuPassageiros(vector<Passageiro> &passageiros);
void listPassageiros(vector<Passageiro> passageiros);
bool buscPassageiro(vector<Passageiro> passageiros, string CPF);
Passageiro returnPassasgeiro(vector<Passageiro> passageiros, string CPF);
string formatData(Data data);
bool validarInputHora(string hora);
void horaToNum(string hora, short int &horaNum, short int &minutoNum);

bool addRoteiro(vector<Roteiro> &roteiros, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino);
bool deleteRoteiro(vector<Roteiro> &roteiros, string codigo);
bool alteraRoteiro(vector<Roteiro> &roteiros, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino);
void listRoteiros(vector<Roteiro> roteiros);
bool buscRoteiro(vector<Roteiro> roteiros, string codigo);
Roteiro returnRoteiro(vector<Roteiro> roteiros, string codigo);
void menuRoteiro(vector<Roteiro> &roteiros);

bool validarInputData(string data);
void dataToNum(string data, short int &dia, short int &mes, int &ano);

bool validaCPF(string CPF);
void CPFtoNum(string &CPF);
string formatCPF(string CPF);

int main(){
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;

    menuPassageiros(passageiros);
    menuRoteiro(roteiros);


    return 0;
}


void menuPassageiros(vector<Passageiro> &passageiros){
    int opc, ano;
    string CPF, nome, NumAutorizacao, data;
    short int dia, mes;
    char ch;
    Passageiro pas;

    do{
        cout << "1 - Adicionar passageiro" << endl;
        cout << "2 - Remover passageiro" << endl;
        cout << "3 - Alterar passageiro" << endl;
        cout << "4 - Listar passageiros" << endl;
        cout << "5 - Busca passageiro" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opc;

        switch (opc){
            case 1:
                do{
                    cout << "CPF: ";
                    cin >> CPF;
                    if(!validaCPF(CPF))
                        cout << "CPF invalido.\n";
                }while(!validaCPF(CPF));
                CPFtoNum(CPF);
                cout << "Nome: ";
                cin >> nome;

                do{
                    cout << "Data de nascimento (DD/MM/AAAA): ";
                    cin >> data;
                }while(!validarInputData(data));
                dataToNum(data, dia, mes, ano);

                cout << "Digite o numero de autorizacao do passageiro: ";
                cin >> NumAutorizacao;

                if (addPassageiro(passageiros, CPF, nome, dia, mes, ano, NumAutorizacao))
                    cout << "Passageiro adicionado com sucesso.\n\n";
                else
                    cout << "Erro ao adicionar passageiro.\n\n";
                break;
            case 2:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                CPFtoNum(CPF);
                if (deletePassageiro(passageiros, CPF))
                    cout << "Passageiro removido com sucesso.\n\n";
                else
                    cout << "Erro ao remover passageiro.\n\n";
                break;
            case 3:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                CPFtoNum(CPF);
                if(buscPassageiro(passageiros, CPF)){
                    pas = returnPassasgeiro(passageiros, CPF);
                    cout << "Deseja alterar nome? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Novo nome: ";
                        cin >> nome;
                    }else{
                        nome = pas.nome;
                    }
                    cout << "Deseja alterar data de nascimento? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        do{
                            cout << "Nova data de nascimento (DD/MM/AAAA): ";
                            cin >> data;
                        }while(!validarInputData(data));
                        dataToNum(data, dia, mes, ano);
                    }else{
                        dia = pas.DtNascimento.dia;
                        mes = pas.DtNascimento.mes;
                        ano = pas.DtNascimento.ano;
                    }
                    cout << "Deseja alterar numero de autorizacao? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Novo numero de autorizacao: ";
                        cin >> NumAutorizacao;
                    }else{ 
                        NumAutorizacao = pas.NumAutorizacao;
                    }
                    if (alteraPassageiro(passageiros, CPF, nome, dia, mes, ano, NumAutorizacao))
                        cout << "Passageiro alterado com sucesso.\n\n";
                    else
                        cout << "Erro ao alterar passageiro.\n\n";
                }else
                    cout << "Passageiro nao encontrado.\n\n";
                break;
            case 4:
                listPassageiros(passageiros);
                break;
            case 5:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                CPFtoNum(CPF);
                cout << ((buscPassageiro(passageiros, CPF))? "\n\n": "Passageiro nao encontrado.\n\n");
                break;
            case 6:
                break;
            default:
                cout << "Opcao invalida." << endl;
                cout << "Digite a opcao desejada: ";
                cin >> opc;
                break;
        }
    }while(opc != 6);
}

bool addPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao){
    Passageiro pas;

    if(inicializaPassageiro(pas, CPF, nome, diaNasc, mesNasc, anoNasc, NumAutorizacao)){
        for (int i = 0; i < passageiros.size(); i++){
            if (passageiros[i].CPF == pas.CPF){
                cout << "CPF ja cadastrado.";
                return false;
            }
        }
        passageiros.push_back(pas);
        return true;
    }
    return false;
}


bool deletePassageiro(vector<Passageiro> &passageiros, string CPF){
    for (int i = 0; i < passageiros.size(); i++){
        if (passageiros[i].CPF == CPF){
            passageiros.erase(passageiros.begin() + i);
            return true;
        }
    }
    return false;
}

string formatData(Data data){
    string dataFormatada = "";

    if(data.dia < 10)
        dataFormatada += "0";
    dataFormatada += to_string(data.dia);
    dataFormatada += "/";
    if(data.mes < 10)
        dataFormatada += "0";
    dataFormatada += to_string(data.mes);
    dataFormatada += "/";
    dataFormatada += to_string(data.ano);

    return dataFormatada;
}

void listPassageiros(vector<Passageiro> passageiros){
    cout << "CPF\t\tNome\t\tData de Nascimento\tNumero de Autorizacao\n";
    for (int i = 0; i < passageiros.size(); i++){
        cout << formatCPF(passageiros[i].CPF);
        cout << "\t" << passageiros[i].nome;
        cout << "\t" << formatData(passageiros[i].DtNascimento);
        cout << "\t" << passageiros[i].NumAutorizacao << endl;
    }
    cout << endl;
}

bool buscPassageiro(vector<Passageiro> passageiros, string CPF){
    for (int i = 0; i < passageiros.size(); i++){
        if (passageiros[i].CPF == CPF){
            cout << "Nome: " << passageiros[i].nome;
            cout <<  " | Data de nascimento: " << formatData(passageiros[i].DtNascimento);
            cout << ((passageiros[i].NumAutorizacao != "")? " | Numero de autorizacao: " + passageiros[i].NumAutorizacao: "\n");
            return true;
        }
    }
    return false;
}

Passageiro returnPassasgeiro(vector<Passageiro> passageiros, string CPF){
    for (int i = 0; i < passageiros.size(); i++){
        if (passageiros[i].CPF == CPF){
            return passageiros[i];
        }
    }
}

bool alteraPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao){
    Data data;
    if(inicializaData(data, diaNasc, mesNasc, anoNasc)){
        for (int i = 0; i < passageiros.size(); i++){
            if (passageiros[i].CPF == CPF){
                passageiros[i].nome = nome;
                passageiros[i].DtNascimento = data;
                passageiros[i].NumAutorizacao = NumAutorizacao;
                return true;
            }
        }
        return false;
    }
    cout << "Data invalida." << endl;
    return false;
}


bool inicializaHora(Hora &Hora, short int hora, short int minuto){

    if (validaHora(hora, minuto)){
        Hora.hora = hora;
        Hora.minuto = minuto;
        return true;
    }else{
        Hora.hora = 0;
        Hora.minuto = 0;
        return false;
    }
}

bool inicializaData(Data &data, short int dia, short int mes, int ano){
    if (validarData(dia, mes, ano)){
        data.dia = dia;
        data.mes = mes;
        data.ano = ano;
        return true;
    }else{
        data.dia = 0;
        data.mes = 0;
        data.ano = 0;
        return false;
    }
}

bool inicializaDataHora(DataHora &datahora, short int min, short int hora, short int dia, short int mes, int ano){
    Data data;
    Hora horario;
    inicializaData(data, dia, mes, ano);
    inicializaHora(horario, hora, min);
    datahora.data = data;
    datahora.horario = horario;
    if (validarData(dia, mes, ano) && validaHora(hora, min))
        return true;
    else
        return false;
}


bool validarData(short int dia, short int mes, int ano){
    if (ano < 0 || mes < 1 || mes > 12 || dia <1){
        return false;
    }
    if (mes == 2){
        if (( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0){
            if (dia > 29)
                return false;
        }
        else if (dia > 28){
            return false;
        }
    }else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia >30)
        return false;
    else if(dia > 31)
        return false;
    return true;
}

bool validarInputData(string data){
    vector<string> dataSeparada;
    string aux = "";
    int i;

    for(i = 0; i<=data.size(); i++){
        if(i != data.size()){
            if(data[i] != '/')
                aux += data[i];
            else{
                dataSeparada.push_back(aux);
                aux = "";
            }
        }else
            dataSeparada.push_back(aux);
    }

    if(dataSeparada.size() != 3)
        return false;

    for (i=0; i<3; i++){
        if(i == 2){
            if(dataSeparada[i].size() != 4)
                return false;
        }else{
            if(dataSeparada[i].size() != 2)
                return false;
        }
        for(char ch: dataSeparada[i]){
            if(!isdigit(ch))
                return false;
        }
    }

    return true;
}

void dataToNum(string data, short int &dia, short int &mes, int &ano){
    dia = stoi(data.substr(0,2));
    mes = stoi(data.substr(3,2));
    ano = stoi(data.substr(6));
}

bool validaHora(short int hora, short int minuto){
    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59){
        return false;
    }
    return true;
}

bool validaDataHora(DataHora datahora){
    if (validarData(datahora.data.dia, datahora.data.mes, datahora.data.ano) && validaHora(datahora.horario.hora, datahora.horario.minuto)){
        return true;
    }else{
        return false;
    }
}

bool validaDuracao(short int hora, short int minuto){
    if (hora < 0 || minuto < 0 || minuto > 59){
        return false;
    }
    return true;
}

bool incializaDuracao(Hora &duracao, short int hora, short int minuto){
    if (validaDuracao(hora, minuto)){
        duracao.hora = hora;
        duracao.minuto = minuto;
        return true;
    }else{
        duracao.hora = 0;
        duracao.minuto = 0;
        return false;
    }
}

bool inicializaPassageiro(Passageiro &pas, string CPF, string nome, short int dia, short int mes, int ano, string NumAutorizacao){
    Data DtNascimento;
    if (inicializaData(DtNascimento, dia, mes, ano)){
        pas.CPF = CPF;
        pas.nome = nome;
        pas.DtNascimento = DtNascimento;
        pas.NumAutorizacao = NumAutorizacao;
        return true;
    }else{
        pas.CPF = "";
        pas.nome = "";
        pas.DtNascimento = DtNascimento;
        pas.NumAutorizacao = "";
        return false;
    }
}

void menuRoteiro(vector<Roteiro> &roteiros){
    int opc, ano;
    string codigo, origem, destino, data, inputHora;
    short int dia, mes, duracaoHora, duracaoMin, hora, min;
    DataHora datahora;
    Roteiro rot;
    char ch;

    do{
        cout << "1 - Adicionar roteiro" << endl;
        cout << "2 - Remover roteiro" << endl;
        cout << "3 - Alterar roteiro" << endl;
        cout << "4 - Listar roteiros" << endl;
        cout << "5 - Busca roteiro" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite a opcao desejada: ";
        cin >> opc;

        switch (opc){
            case 1:
                cout << "Codigo: ";
                cin >> codigo;

                do{
                    cout << "Data (DD/MM/AAAA): ";
                    cin >> data;
                }while(!validarInputData(data));
                dataToNum(data, dia, mes, ano);

                do{
                    cout << "Hora (HH:MM): ";
                    cin >> inputHora;
                }while(!validarInputHora(inputHora));
                horaToNum(inputHora, hora, min);

                do{
                    cout << "Duracao (HH:MM): ";
                    cin >> inputHora;
                }while(!validarInputHora(inputHora));
                cout << "Origem: ";
                cin >> origem;
                cout << "Destino: ";
                cin >> destino;
                if (addRoteiro(roteiros, codigo, min, hora, dia, mes, ano, duracaoHora, duracaoMin, origem, destino))
                    cout << "Roteiro adicionado com sucesso." << endl;
                else
                    cout << "Erro ao adicionar roteiro." << endl;
                break;
            case 2:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                if (deleteRoteiro(roteiros, codigo))
                    cout << "Roteiro removido com sucesso." << endl;
                else
                    cout << "Erro ao remover roteiro." << endl;
                break;
            case 3:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                if(buscRoteiro(roteiros, codigo)){
                    rot = returnRoteiro(roteiros, codigo);
                    cout << "Deseja alterar data? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        do{
                            cout << "Nova data (DD/MM/AAAA): ";
                            cin >> data;
                        }while(!validarInputData(data));
                        dataToNum(data, dia, mes, ano);
                    }else{
                        dia = rot.datahora.data.dia;
                        mes = rot.datahora.data.mes;
                        ano = rot.datahora.data.ano;
                    }
                    cout << "Deseja alterar hora? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Nova hora (HH:MM): ";
                        cin >> inputHora;
                        horaToNum(inputHora, hora, min);
                    }else{
                        hora = rot.datahora.horario.hora;
                        min = rot.datahora.horario.minuto;
                    }
                    cout << "Deseja alterar duracao? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Nova duracao (HH:MM): ";
                        cin >> inputHora;
                        horaToNum(inputHora, duracaoHora, duracaoMin);
                    }else{
                        duracaoHora = rot.duracao.hora;
                        duracaoMin = rot.duracao.minuto;
                    }
                    cout << "Deseja alterar origem? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Nova origem: ";
                        cin >> origem;
                    }else{
                        origem = rot.origem;
                    }
                    cout << "Deseja alterar destino? (S/N): ";
                    cin >> ch;
                    ch = tolower(ch);
                    if(ch == 's'){
                        cout << "Novo destino: ";
                        cin >> destino;
                    }else{
                        destino = rot.destino;
                    }
                    if(alteraRoteiro(roteiros, codigo, min, hora, dia, mes, ano, duracaoHora, duracaoMin, origem, destino))
                        cout << "Roteiro alterado com sucesso." << endl;
                    else
                        cout << "Erro ao alterar roteiro." << endl;
                }else
                    cout << "Roteiro nao encontrado." << endl;
                break;
            case 4:
                listRoteiros(roteiros);
                break;
            case 5:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                cout << (buscRoteiro(roteiros, codigo)? "\n\n" : "Roteiro nao encontrado.\n\n");
                break;
            case 6:
                break;
            default:
                cout << "Opcao invalida." << endl;
                cout << "Digite a opcao desejada: ";
                cin >> opc;
                break;
        }
    }while (opc!=6);
}


bool inicializaRoteiro(Roteiro &rot, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Hora duracao;
    DataHora datahora;
    if (inicializaDataHora(datahora, min, hora, dia, mes, ano) && incializaDuracao(duracao, duracaoHora, duracaoMin)){
        rot.codigo = codigo;
        rot.datahora = datahora;
        rot.duracao = duracao;
        rot.origem = origem;
        rot.destino = destino;
        return true;
    }else{
        rot.codigo = "";
        rot.datahora = datahora;
        rot.duracao = duracao;
        rot.origem = "";
        rot.destino = "";
        return false;
    }
}

bool addRoteiro(vector<Roteiro> &roteiros, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Roteiro rot;
    if (inicializaRoteiro(rot, codigo, min, hora, dia, mes, ano, duracaoHora, duracaoMin, origem, destino)){
        for (int i = 0; i < roteiros.size(); i++){
            if (roteiros[i].codigo == rot.codigo)
                return false;
        }
        roteiros.push_back(rot);
        return true;
    }
    return false;
}

bool deleteRoteiro(vector<Roteiro> &roteiros, string codigo){
    for (int i = 0; i < roteiros.size(); i++){
        if (roteiros[i].codigo == codigo){
            roteiros.erase(roteiros.begin() + i);
            return true;
        }
    }
    return false;
}

bool alteraRoteiro(vector<Roteiro> &roteiros, string codigo, short int min, short int hora, short int dia, short int mes, int ano, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Roteiro rot;
    if (inicializaRoteiro(rot, codigo, min, hora, dia, mes, ano, duracaoHora, duracaoMin, origem, destino)){
        for (int i = 0; i < roteiros.size(); i++){
            if (roteiros[i].codigo == rot.codigo){
                roteiros[i].origem = rot.origem;
                roteiros[i].destino = rot.destino;
                roteiros[i].duracao = rot.duracao;
                roteiros[i].datahora = rot.datahora;
                return true;
            }
        }
        return false;
    }
    return false;
}

void listRoteiros(vector<Roteiro> roteiros){
    cout << "Codigo\t\tData\t\tHora\t\tDuracao\t\tOrigem\t\tDestino" << endl;
    for (int i = 0; i < roteiros.size(); i++){
        cout << roteiros[i].codigo;
        cout << "\t\t" << formatData(roteiros[i].datahora.data);
        cout << "\t\t" << roteiros[i].datahora.horario.hora << ":" << roteiros[i].datahora.horario.minuto;
        cout << "\t\t" << roteiros[i].duracao.hora << ":" << roteiros[i].duracao.minuto;
        cout << "\t\t" << roteiros[i].origem;
        cout << "\t\t" << roteiros[i].destino << endl;
    }
    cout << endl;
}

bool buscRoteiro(vector<Roteiro> roteiros, string codigo){
    for (int i = 0; i < roteiros.size(); i++){
        if (roteiros[i].codigo == codigo){
            cout << "cod.: " << roteiros[i].codigo;
            cout << " | Data: " << formatData(roteiros[i].datahora.data);
            cout << " | Hora: " << roteiros[i].datahora.horario.hora << ":" << roteiros[i].datahora.horario.minuto;
            cout << " | Duracao: " << roteiros[i].duracao.hora << ":" << roteiros[i].duracao.minuto; 
            cout << " | Origem: " << roteiros[i].origem;
            cout << " | Destino: " << roteiros[i].destino << endl;
            return true;
        }
    }
    return false;
}

Roteiro returnRoteiro(vector<Roteiro> roteiros, string codigo){
    for (int i = 0; i < roteiros.size(); i++){
        if (roteiros[i].codigo == codigo){
            return roteiros[i];
        }
    }
}

bool validaCPF(string CPF){
    string numCPF = "";

    for(char ch : CPF){
        if(isdigit(ch))
            numCPF += ch;
    }

    if(numCPF.size() != 11)
        return false;
    else
        return true;
}


void CPFtoNum(string &CPF){
    string numCPF = "";

    for(char ch : CPF){
        if(isdigit(ch))
            numCPF += ch;
    }

    CPF = numCPF;
}

string formatCPF(string CPF){
    string CPFFormatado = "";

    CPFFormatado += CPF.substr(0,3);
    CPFFormatado += ".";
    CPFFormatado += CPF.substr(3,3);
    CPFFormatado += ".";
    CPFFormatado += CPF.substr(6,3);
    CPFFormatado += "-";
    CPFFormatado += CPF.substr(9);

    return CPFFormatado;
}

bool validarInputHora(string hora){
    vector<string> horaSeparada;
    string aux = "";
    int i;

    for(i = 0; i<=hora.size(); i++){
        if(i != hora.size()){
            if(hora[i] != ':')
                aux += hora[i];
            else{
                horaSeparada.push_back(aux);
                aux = "";
            }
        }else
            horaSeparada.push_back(aux);
    }

    if(horaSeparada.size() != 2)
        return false;

    for (i=0; i<2; i++){
        if(horaSeparada[i].size() != 2)
            return false;
        for(char ch: horaSeparada[i]){
            if(!isdigit(ch))
                return false;
        }
    }
    return true;
}

void horaToNum(string hora, short int &horaNum, short int &minutoNum){
    horaNum = stoi(hora.substr(0,2));
    minutoNum = stoi(hora.substr(3));
}