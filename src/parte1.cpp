#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Data{
    short int dia;
    short int mes;
    int ano;
}

struct Horario{
    short int hora;
    short int minuto;
}

struct DataHora{
    Data data;
    Horario horario;
}

struct Passageiro{
    string CPF;
    string nome;
    Data DtNascimento;
    string NumAutorizacao = "";
}

struct Roteiro{
    string codigo;
    DataHora datahora;
    Hora duracao;
    string origem;
    string destino;
}

int main(){
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;

    


    return 0;
}


void menuPassageiros(){
    cout << "1 - Adicionar passageiro" << endl;
    cout << "2 - Remover passageiro" << endl;
    cout << "3 - Alterar passageiro" << endl;
    cout << "4 - Listar passageiros" << endl;
    cout << "5 - Voltar" << endl;
    cout << "Digite a opcao desejada: ";
}

bool addPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao = ""){
    Passageiro pas;

    if(inicializaPassageiro(&pas, CPF, nome, diaNasc, mesNasc, anoNasc, NumAutorizacao)){
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

    dataFormatada += data.dia;
    dataFormatada += "/";
    dataFormatada += data.mes;
    dataFormatada += "/";
    dataFormatada += data.ano;

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
            cout << "Nome: " << passageiros[i].nome << " | Data de nascimento: " << dataFormatada(passageiros[i].DtNascimento) << ((passageiros[i].NumAutorizacao != "")? "Numero de autorizacao" + passageiros[i].NumAutorizacao: "\n");
            return true;
        }
    }
    return false;
}

bool alteraPassageiro(vector<Passageiro> &passageiros, string CPF, string nome, short int diaNasc, short int mesNasc, int anoNasc, string NumAutorizacao = ""){
    Data data;
    if(inicializaData(&data, diaNasc, mesNasc, anoNasc)){
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


bool inicializaHora(Hora &hora, short int hora, short int minuto){

    if (validaHora(hora, minuto)){
        hora->hora = hora;
        hora->minuto = minuto;
        return true;
    }else{
        hora->hora = 0;
        hora->minuto = 0;
        return false;
    }
}

bool inicializaData(Data &data, short int dia, short int mes, int ano){
    if (validarData(dia, mes, ano)){
        data->dia = dia;
        data->mes = mes;
        data->ano = ano;
        return true;
    }else{
        data->dia = 0;
        data->mes = 0;
        data->ano = 0;
        return false;
    }
}

bool inicializaDataHora(DataHora &datahora, short int min, short int hora, short int dia, short int mes, int ano){
    Data data;
    Hora hora;
    inicializaData(&data, dia, mes, ano);
    inicializaHora(&hora, hora, min);
    datahora->data = data;
    datahora->hora = hora;
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
    if (validarData(datahora->data->dia, datahora->data->mes, datahora->data->ano) && validaHora(datahora->hora->hora, datahora->hora->minuto)){
        return true;
    }else{
        return false;
    }
}

bool validaDuracao(shor int hora, short int miuto){
    if (hora < 0 || minuto < 0 || minuto > 59){
        return false;
    }
    return true;
}

bool inicializaPassageiro(Passageiro &pas, string CPF, string nome, short int dia, short int mes, int ano, string NumAutorizacao = ""){
    Data DtNascimento;
    if (inicializaData(&DtNascimento, dia, mes, ano)){
        pas->CPF = CPF;
        pas->nome = nome;
        pas->DtNascimento = DtNascimento;
        pas->NumAutorizacao = NumAutorizacao;
        return true;
    }else{
        pas->CPF = "";
        pas->nome = "";
        pas->DtNascimento = 0;
        pas->NumAutorizacao = "";
        return false;
    }
}


bool inicializaRoteiro(Roteiro &rot, string codigo, DataHora datahora, short int duracaoHora, short int duracaoMin, string origem, string destino){
    if (validaDataHora(DataHora datahora) && validaDuracao(duracaoHora, duracaoMin)){
        rot->codigo = codigo;
        rot->datahora = datahora;
        rot->duracao = duracao;
        rot->origem = origem;
        rot->destino = destino;
        return true;
    }else{
        rot->codigo = "";
        rot->datahora = 0;
        rot->duracao = 0;
        rot->origem = "";
        rot->destino = "";
        return false;
    }
}



