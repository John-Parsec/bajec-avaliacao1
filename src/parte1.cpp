#include <iostream>

using namespace std;

struct Data{
    short int dia;
    short int mes;
    short int ano;
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
    string NumAutorizacao;
}

struct Roteiro{
    string codigo;
    DataHora datahora;
    Hora duracao;
    string origem;
    string destino;
}

int main(){

    return 0;
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

bool inicializaData(Data &data, short int dia, short int mes, short int ano){
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

bool inicializaDataHora(DataHora &datahora, Data data, Hora hora){
    if (validarData(data->dia, data->mes, data->ano) && validaHora(hora->hora, hora->minuto)){
        datahora->data = data;
        datahora->hora = hora;
        return true;
    }else{
        datahora->data = 0;
        datahora->hora = 0;
        return false;
    }
}



bool validarData(short int dia, short int mes, short int ano){
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