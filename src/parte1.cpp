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
bool inicializaRoteiro(Roteiro &rot, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino);
bool validaDataHora(DataHora datahora);
bool validarData(short int dia, short int mes, int ano);
bool validaHora(short int hora, short int minuto);
bool validaDuracao(short int hora, short int minuto);
bool incializaDuracao(Hora &duracao, short int hora, short int minuto);
void menuPassageiros(vector<Passageiro> &passageiros);
void listPassageiros(vector<Passageiro> passageiros);
bool buscPassageiro(vector<Passageiro> passageiros, string CPF);
string formatData(Data data);

bool addRoteiro(vector<Roteiro> &roteiros, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino);
bool deleteRoteiro(vector<Roteiro> &roteiros, string codigo);
bool alteraRoteiro(vector<Roteiro> &roteiros, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino);
void listRoteiros(vector<Roteiro> roteiros);
bool buscRoteiro(vector<Roteiro> roteiros, string codigo);



int main(){
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;

    menuPassageiros(passageiros);


    return 0;
}


void menuPassageiros(vector<Passageiro> &passageiros){
    int opc, ano;
    string CPF, nome, NumAutorizacao;
    short int dia, mes;

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
                cout << "CPF: ";
                cin >> CPF;
                cout << "Nome do passageiro: ";
                cin >> nome;
                cout << "Dia de nascimento: ";
                cin >> dia;
                cout << "Mes de nascimento: ";
                cin >> mes;
                cout << "Ano de nascimento: ";
                cin >> ano;
                cout << "Digite o numero de autorizacao do passageiro: ";
                cin >> NumAutorizacao;
                if (addPassageiro(passageiros, CPF, nome, dia, mes, ano, NumAutorizacao)){
                    cout << "Passageiro adicionado com sucesso." << endl;
                }else{
                    cout << "Erro ao adicionar passageiro." << endl;
                }
                break;
            case 2:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                if (deletePassageiro(passageiros, CPF)){
                    cout << "Passageiro removido com sucesso." << endl;
                }else{
                    cout << "Erro ao remover passageiro." << endl;
                }
                break;
            case 3:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                if(buscPassageiro(passageiros, CPF)){
                    cout << "Novo nome: ";
                    cin >> nome;
                    cout << "Novo dia de nascimento: ";
                    cin >> dia;
                    cout << "Novo mes de nascimento: ";
                    cin >> mes;
                    cout << "Novo ano de nascimento : ";
                    cin >> ano;
                    cout << "Novo numero de autorizacao : ";
                    cin >> NumAutorizacao;
                    if (alteraPassageiro(passageiros, CPF, nome, dia, mes, ano, NumAutorizacao)){
                        cout << "Passageiro alterado com sucesso." << endl;
                    }else{
                        cout << "Erro ao alterar passageiro." << endl;
                    }
                }
                break;
            case 4:
                listPassageiros(passageiros);
                break;
            case 5:
                cout << "Digite o CPF do passageiro: ";
                cin >> CPF;
                if (buscPassageiro(passageiros, CPF)){
                    cout << "Passageiro encontrado." << endl;
                }else{
                    cout << "Passageiro nao encontrado." << endl;
                }
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

    dataFormatada += to_string(data.dia);
    dataFormatada += "/";
    dataFormatada += to_string(data.mes);
    dataFormatada += "/";
    dataFormatada += to_string(data.ano);

    return dataFormatada;
}

void listPassageiros(vector<Passageiro> passageiros){
    cout << "CPF\t\tNome\t\tData de Nascimento\t\tNumero de Autorizacao" << endl;
    for (int i = 0; i < passageiros.size(); i++){
        cout << passageiros[i].CPF;
        cout << " " << passageiros[i].nome;
        cout << "  " << formatData(passageiros[i].DtNascimento);
        cout << " " << passageiros[i].NumAutorizacao << endl;
    }
    cout << endl;
}

bool buscPassageiro(vector<Passageiro> passageiros, string CPF){
    for (int i = 0; i < passageiros.size(); i++){
        if (passageiros[i].CPF == CPF){
            cout << "Nome: " << passageiros[i].nome << " | Data de nascimento: " << formatData(passageiros[i].DtNascimento) << ((passageiros[i].NumAutorizacao != "")? "Numero de autorizacao" + passageiros[i].NumAutorizacao: "\n");
            return true;
        }
    }
    return false;
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
        cout << "Passageiro nao encontrado." << endl;
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
    }else if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
        if (dia > 30){
            return false;
        }else if (dia > 31){
            return false;
        }
    }
    return true;
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


bool inicializaRoteiro(Roteiro &rot, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Hora duracao;
    if (validaDataHora(datahora) && incializaDuracao(duracao, duracaoHora, duracaoMin)){
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

bool addRoteiro(vector<Roteiro> &roteiros, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Roteiro rot;
    Hora duracao;
    if (inicializaRoteiro(rot, codigo, datahora, duracaoHora, duracaoMin, origem, destino) && incializaDuracao(duracao, duracaoHora, duracaoMin)){
        for (int i = 0; i < roteiros.size(); i++){
            if (roteiros[i].codigo == rot.codigo || 
                (roteiros[i].datahora.data.dia == rot.datahora.data.dia && roteiros[i].datahora.data.mes == rot.datahora.data.mes && roteiros[i].datahora.data.ano == rot.datahora.data.ano &&
                roteiros[i].datahora.horario.hora == rot.datahora.horario.hora && roteiros[i].datahora.horario.minuto == rot.datahora.horario.minuto)){
                return false;
            }
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

bool alteraRoteiro(vector<Roteiro> &roteiros, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino){
    Roteiro rot;
    Hora duracao;
    if (inicializaRoteiro(rot, codigo, datahora, duracaoHora, duracaoMin, origem, destino) && incializaDuracao(duracao, duracaoHora, duracaoMin) && validaDataHora(datahora)){
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



