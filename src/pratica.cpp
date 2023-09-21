#include <ctime>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct Passageiro {
    char cpf[12];
    string nome;
    string dtNascimento;
    int numAutorizacao = 0;
} ;

struct data_hora{
    string Data;
    string Hora;
};

struct Roteiro {
    char codigo[12];
    data_hora Data_hora;
    int duracao;
    string origem;
    string destino;
};

struct Ocorrencia {
    string descricao;
    data_hora dt_hora;
    int numApolice;
};

struct Embarca {
    bool realizada;
    int duracao;
    data_hora dt_hora;
    char passageiroCPF[12];
    char roteiroCodigo[12];
    Ocorrencia ocorrencia;
};

//Data e hora
bool verificar_data(string data);
bool verificar_dataNascimento(string data);
bool verificar_hora(string hora);
bool temMaisde18(string dataNasc);

//CPF e código
bool validaCPF(char cpf[12]);
bool cpfUnico(vector<Passageiro> passageiros, char cpf[12]);
bool validaCod(char cod[12]);
bool codUnico(vector<Passageiro> passageiros, char cod[12]);

//Passageiro
void gestaoPassageiro(vector<Passageiro> &passageiros);
void incluirPassageiro(vector<Passageiro> &passageiros);
void listarPassageiros(vector<Passageiro> passageiros);
int buscarPassageiros(vector<Passageiro> passageiros, char cpf[12]);
void excluirPassageiro(vector<Passageiro> &passageiros, char cpf[12]);
void alterarPassageiro(vector<Passageiro> &passageiros, char cpf[12]);

//Roteiro
void gestaoRoteiro(vector<Roteiro> &roteiros);
void incluirRoteiro(vector<Roteiro> &roteiros);
void listarRoteiros(vector<Roteiro> roteiros);
int buscarRoteiros(vector<Roteiro> roteiros, char cod[12]);
void excluirRoteiro(vector<Roteiro> &roteiros, char cod[12]);
void alterarRoteiro(vector<Roteiro> &roteiros, char cod[12]);

//Embarque
void gestaoEmbarque(vector<Embarca> &embarques, vector<Passageiro> passageiros, vector<Roteiro> roteiros);
void incluirEmbarque(vector<Embarca> &embarques, vector<Passageiro> passageiros, vector<Roteiro> roteiros);
void listarEmbarques(vector<Embarca> embarques);

//Ocorrência
void gestaoOcorrencia(vector<Ocorrencia> &Ocorrencias, vector<Passageiro> passageiros, vector<Roteiro> roteiros);
void incluirOcorrencia(vector<Ocorrencia> &Ocorrencias);
void listarOcorrenciasRoteiro(vector<Ocorrencia> Ocorrencias, vector<Roteiro> roteiros);

int main(void) {
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;
    vector<Embarca> embarques;
    vector<Ocorrencia> ocorrencias;

    int resposta;
    do {
        cout << endl << "Menu Geral:" << endl;
        cout << "1 - Gestão de Passageiros" << endl;
        cout << "2 - Gestão de Roteiros" << endl;
        cout << "3 - Gestão de Embarque" << endl;
        cout << "4 - Gestão de Ocorrências" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        switch (resposta) {
            case 1:
                gestaoPassageiro(passageiros);
                break;
            case 2:
                gestaoRoteiro(roteiros);
                break;
            case 3:
                gestaoEmbarque(embarques, passageiros, roteiros);
                break;
            case 4:
                gestaoOcorrencia(ocorrencias, passageiros, roteiros);
                break;
        }
    } while (resposta != 0);

    return 0;
}

//Data e hora
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
    return valido;
}

bool verificar_dataNascimento(string data)
{
    string a, str;
    int ia;
    bool valido = 1;

    str = data;

    if(data.size() != 10)
    {
        valido = 0;
    }
    else
    {
        a = str.substr(6, 4);
        ia = stoi(a);
    }

    if(valido && ia > 2023)
        valido = 0;

    valido = verificar_data(str);

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

bool temMaisde18(string dataNasc) {
    int anoNasc = stoi(dataNasc.substr(6, 4));
    time_t dataAtual;
    dataAtual = time(NULL);
    struct tm separaData = *localtime(&dataAtual);
    int anoAtual = separaData.tm_year + 1900;
    int idade = anoAtual - anoNasc;
    if (idade >= 18) {
        return true;
    } else {
        return false;
    }
}

//cpf e codigo
bool validaCPF(char cpf[12]) {
    // Verifica se o CPF possui 11 dígitos
    if (strlen(cpf) != 11)
        return false;

    // Verifica se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i]))
            return false;
    }

/*
    // Converte o array de char para um array de inteiros
    int digitos[11];
    for (int i = 0; i < 11; i++) {
        digitos[i] = cpf[i] - '0';
    }

    // Calcula o primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += digitos[i] * (10 - i);
    }
    int resto = soma % 11;
    int primeiroDigitoVerificador = (resto < 2) ? 0 : 11 - resto;

    // Verifica o primeiro dígito verificador
    if (digitos[9] != primeiroDigitoVerificador)
        return false;

    // Calcula o segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += digitos[i] * (11 - i);
    }
    resto = soma % 11;
    int segundoDigitoVerificador = (resto < 2) ? 0 : 11 - resto;

    // Verifica o segundo dígito verificador
    if (digitos[10] != segundoDigitoVerificador)
        return false;
//*/
    // Se todas as verificações passaram, o CPF é válido
    return true;
}

bool cpfUnico(vector<Passageiro> passageiros, char cpf[12]) {
    for (int i = 0; i < passageiros.size(); i++) {
        if (strcmp(passageiros[i].cpf, cpf) == 0) {
            return false;
        }
    }
    return true;
}

bool validaCod(char cod[12]) {
    // Verifica se o codigo possui 11 dígitos
    if (strlen(cod) != 11)
        return false;

    // Verifica se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cod[i]))
            return false;
    }

    // Se todas as verificações passaram, o codigo é válido
    return true;
}

bool codUnico(vector<Roteiro> roteiros, char cod[12]) {
    for (int i = 0; i < roteiros.size(); i++) {
        if (strcmp(roteiros[i].codigo, cod) == 0) {
            return false;
        }
    }
    return true;
}

//Passageiro
void gestaoPassageiro(vector<Passageiro> &passageiros) {
    int resposta;
    char cpf[12];
    
    do {
        cout << endl << "Menu de Gestão de passageiros:" << endl;
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar (por cpf)" << endl;
        cout << "4 - Listar" << endl;
        cout << "5 - Localizar (por cpf)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        cout << endl;
        switch (resposta) {
            case 1:
                incluirPassageiro(passageiros);
                break;
            case 2:
                cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
                cin >> cpf;
                excluirPassageiro(passageiros, cpf);
                break;
            case 3:
                cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
                cin >> cpf;
                alterarPassageiro(passageiros, cpf);
                break;

            case 4:
                listarPassageiros(passageiros);
                break;
            case 5:
                cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
                cin >> cpf;
                buscarPassageiros(passageiros, cpf);
                break;
        }

    } while (resposta != 0);
}

void incluirPassageiro(vector<Passageiro> &passageiros) {
    Passageiro passageiro;
    do {
        cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
        cin >> passageiro.cpf;
        if (!validaCPF(passageiro.cpf)) {
            cout << "CPF inválido" << endl;
        }
        if (!cpfUnico(passageiros, passageiro.cpf)) {
            cout << "CPF já cadastrado" << endl;
        }
    } while (!validaCPF(passageiro.cpf) || !cpfUnico(passageiros, passageiro.cpf));
    cout << "Digite o nome do passageiro: ";
    getline(cin >> ws, passageiro.nome);
    cout << "Digite a data de nascimento do passageiro:(dd/mm/aaaa) ";
    cin >> passageiro.dtNascimento;
    while(!verificar_dataNascimento(passageiro.dtNascimento))
    {
        cout << "Data de nascimento inválida, insira novamente:(dd/mm/aaaa) ";
        cin >> passageiro.dtNascimento;
    }

    
    if (!temMaisde18(passageiro.dtNascimento)) {
        cout << "Digite o numero de autorização do passageiro: ";
        cin >> passageiro.numAutorizacao;
    } else {
        passageiro.numAutorizacao = -1;
    }
    passageiros.push_back(passageiro);
}

void listarPassageiros(vector<Passageiro> passageiros) {
    if (passageiros.size() == 0) {
        cout << "Não há passageiros cadastrados" << endl;
        return;
    }
    cout << "CPF\tNome\tData de Nascimento\tNumero de Autorização" << endl;
    for (int i = 0; i < passageiros.size(); i++) {
        cout << passageiros[i].cpf << "\t";
        cout << passageiros[i].nome << "\t";
        cout << passageiros[i].dtNascimento << "\t";
        if (passageiros[i].numAutorizacao != -1)
            cout << passageiros[i].numAutorizacao;
        cout << endl;
    }
}

int buscarPassageiros(vector<Passageiro> passageiros, char cpf[12]) {
    if (passageiros.size() == 0) {
        cout << "Não há passageiros cadastrados" << endl;
        return -1;
    }
    for (int i = 0; i < passageiros.size(); i++) {
        if (strcmp(passageiros[i].cpf, cpf) == 0) {
            cout << "CPF: " << passageiros[i].cpf << endl;
            cout << "Nome: " << passageiros[i].nome << endl;
            cout << "Data de Nascimento: " << passageiros[i].dtNascimento << endl;
            if (passageiros[i].numAutorizacao != -1)
                cout << "Numero de Autorização: " << passageiros[i].numAutorizacao << endl;
            return i;
        }
    }
    cout << "Passageiro não encontrado" << endl;
    return -1;
}

void excluirPassageiro(vector<Passageiro> &passageiros, char cpf[12]) {
    if (passageiros.size() == 0) {
        cout << "Não há passageiros cadastrados" << endl;
        return;
    }
    for (auto x = passageiros.begin(); x != passageiros.end(); x++) {
        if (strcmp(x->cpf, cpf) == 0) {
            passageiros.erase(x);
            cout << "Passageiro excluido com sucesso" << endl;
            return;
        }
    }
    cout << "Passageiro não encontrado" << endl;
}

void alterarPassageiro(vector<Passageiro> &passageiros, char cpf[12]) {
    int posicao = buscarPassageiros(passageiros, cpf);
    string resposta;
    if (posicao == -1) {
        return;
    }
    cout << "Deseja alterar o nome? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite o novo nome: ";
        getline(cin >> ws, resposta);
        passageiros.at(posicao).nome = resposta;
    }

    cout << "Deseja alterar a data de nascimento? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova data de nascimento: ";
        cin >> resposta;
        while(!verificar_dataNascimento(resposta))
        {
            cout << "Data de nascimento inválida, insira novamente: ";
            cin >> resposta;
        }

        passageiros.at(posicao).dtNascimento = resposta;
    }
    if (!temMaisde18(passageiros.at(posicao).dtNascimento)) {
        cout << "Deseja alterar o numero de autorização? (s/n)";
        cin >> resposta;
        if (resposta == "s") {
            int autoriza;
            cout << "Digite o novo numero de autorização: ";
            cin >> autoriza;
            passageiros.at(posicao).numAutorizacao = autoriza;
        }
    } else {
        passageiros.at(posicao).numAutorizacao = -1;
    }
}

//Roteiro
void gestaoRoteiro(vector<Roteiro> &roteiros) {
    int resposta;
    char codigo[12];
    do {
        codigo[12] = {0};
        cout << endl << "Menu de Gestão de roteiros:" << endl;
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar (por codigo)" << endl;
        cout << "4 - Listar" << endl;
        cout << "5 - Localizar (por codigo)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        cout << endl;
        switch (resposta) {
            case 1:
                incluirRoteiro(roteiros);
                break;
            case 2:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                excluirRoteiro(roteiros, codigo);
                break;
            case 3:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                alterarRoteiro(roteiros, codigo);
                break;

            case 4:
                listarRoteiros(roteiros);
                break;
            case 5:
                cout << "Digite o codigo do roteiro: ";
                cin >> codigo;
                buscarRoteiros(roteiros, codigo);
                break;
        }

    } while (resposta != 0);
}

void incluirRoteiro(vector<Roteiro> &roteiros) {
    Roteiro roteiro;
    string resposta;
    do {
        cout << "Digite o codigo do roteiro: ";
        cin >> roteiro.codigo;
        if (!validaCod(roteiro.codigo)) {
            cout << "Codigo inválido" << endl;
        }
        if (!codUnico(roteiros, roteiro.codigo)) {
            cout << "Codigo já cadastrado" << endl;
        }
    } while (!validaCod(roteiro.codigo) || !codUnico(roteiros, roteiro.codigo));

    cin.ignore();
    cout << "Digite a data prevista:(dd/mm/aaaa) ";
    getline(cin, resposta);
    while(!verificar_data(resposta))
    {
        cout << "Data inválida, insira novamente:(dd/mm/aaaa) ";
        cin >> (resposta);
    }
    roteiro.Data_hora.Data = resposta;

    cout << "Digite a Hora prevista:(hh:mm) ";
    getline(cin, resposta);
    while(!verificar_hora(resposta))
    {
        cout << "Hora inválida, insira novamente:(hh:mm) ";
        cin >> (resposta);
    }
    roteiro.Data_hora.Hora = resposta;

    
    cout << "Digite a duracao do roteiro:(Apenas numeros) ";
    cin >> roteiro.duracao;
    cin.ignore();
    cout << "Digite a origem do roteiro: ";
    getline(cin >> ws, resposta);
    roteiro.origem = resposta;
    cout << "Digite o destino do roteiro: ";
    getline(cin >> ws, resposta);
    roteiro.destino = resposta;

    roteiros.push_back(roteiro);
}

void listarRoteiros(vector<Roteiro> roteiros) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return;
    }
    cout << "Codigo\tData\tHora\tDuracao\tOrigem\tDestino" << endl;
    for (int i = 0; i < roteiros.size(); i++) {
        cout << roteiros[i].codigo << "\t";
        cout << roteiros[i].Data_hora.Data << "\t";
        cout << roteiros[i].Data_hora.Hora << "\t";
        cout << roteiros[i].duracao << "\t";
        cout << roteiros[i].origem << "\t";
        cout << roteiros[i].destino << "\t";
        cout << endl;
    }
}

int buscarRoteiros(vector<Roteiro> roteiros, char codigo[12]) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return -1;
    }
    for (int i = 0; i < roteiros.size(); i++) {
        cout << roteiros[i].codigo << " - " << codigo;
        if (strcmp(roteiros[i].codigo, codigo) == 0) {
            cout << "Codigo: " << roteiros[i].codigo << endl;
            cout << "Data: " << roteiros[i].Data_hora.Data << endl;
            cout << "Hora: " << roteiros[i].Data_hora.Hora << endl;
            cout << "Duracao: " << roteiros[i].duracao << endl;
            cout << "Origem: " << roteiros[i].origem << endl;
            cout << "Destino: " << roteiros[i].destino << endl;
            return i;
        }
    }
    cout << "Roteiro não encontrado" << endl;
    return -1;
}

void excluirRoteiro(vector<Roteiro> &roteiros, char codigo[12]) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return;
    }
    for (auto x = roteiros.begin(); x != roteiros.end(); x++) {
        cout << "AAAAAAAAAAAAAAAAAAAAAA";
        if (strcmp(x->codigo, codigo) == 0) {
            roteiros.erase(x);
            cout << "Roteiro excluido com sucesso" << endl;
            return;
        }
    }
    cout << "Roteiro não encontrado" << endl;
}

void alterarRoteiro(vector<Roteiro> &roteiros, char codigo[12]) {
    int posicao = buscarRoteiros(roteiros, codigo);
    string resposta;
    if (posicao == -1) {
        return;
    }
    cout << "Deseja alterar a data? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova data:(dd/mm/aaaa)";
        cin >> resposta;
        roteiros.at(posicao).Data_hora.Data = resposta;
    }

    cout << "Deseja alterar a hora? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova hora:(hh:mm) ";
        cin >> resposta;
        roteiros.at(posicao).Data_hora.Hora = resposta;
    }

    cout << "Deseja alterar a duracao? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova duracao:(Apenas numeros) ";
        cin >> resposta;
        roteiros.at(posicao).duracao = stoi(resposta);
    }

    cout << "Deseja alterar a origem? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova origem: ";
        getline(cin >> ws, resposta);
        roteiros.at(posicao).origem = resposta;
    }

    cout << "Deseja alterar o destino? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite o novo destino: ";
        getline(cin >> ws, resposta);
        roteiros.at(posicao).destino = resposta;
    }
}

//Embarque
void gestaoEmbarque(vector<Embarca> &embarques, vector<Passageiro> passageiros, vector<Roteiro> roteiros) {
    int resposta;
    do {
        cout << endl << "Menu de Gestão de embarques:" << endl;
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar" << endl;
        cout << "4 - Listar" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        cout << endl;
        switch (resposta) {
            case 1:
                incluirEmbarque(embarques, passageiros, roteiros);
                break;
            case 2:
                cout << "Espaco para excluir embarque" << endl;
                break;
            case 3:
                cout << "Espaco para alterar embarque" << endl;
                break;
            case 4:
                listarEmbarques(embarques);
                break;
        }

    } while (resposta != 0);
}

void incluirEmbarque(vector<Embarca> &embarques, vector<Passageiro> passageiros, vector<Roteiro> roteiros) {
    Embarca embarque;
    string resposta;

    char cpf[12], codigo[12];

    cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
    cin >> cpf;
    if (!validaCPF(cpf)) {
        cout << "CPF inválido" << endl;
        return;
    }
    if (cpfUnico(passageiros, cpf)) {
        cout << "Passageiro não cadastrado" << endl;
        return;
    }

    strcpy(embarque.passageiroCPF, cpf);

    cout << "Digite o codigo do roteiro: ";
    cin >> codigo;
    if (!validaCod(codigo)) {
        cout << "Codigo inválido" << endl;
        return;
    }
    if (codUnico(roteiros, codigo)) {
        cout << "Codigo não cadastrado" << endl;
        return;
    }

    strcpy(embarque.roteiroCodigo, codigo);

    cin.ignore();
    cout << "Digite a data do embarque:(dd/mm/aaaa) ";
    getline(cin, resposta);
    while(!verificar_data(resposta)){
        cout << "Data inválida, insira novamente:(dd/mm/aaaa) ";
        getline(cin, resposta);
    }
    embarque.dt_hora.Data = resposta;

    cout << "Digite a hora do embarque:(hh:mm) ";
    getline(cin, resposta);
    while(!verificar_hora(resposta)){
        cout << "Hora inválida, insira novamente:(hh:mm) ";
        getline(cin, resposta);
    }
    embarque.dt_hora.Hora = resposta;

    do{
        cout << "O embarque já aconteceu? (s/n)";
        cin >> resposta;

        if (resposta == "s") {
            embarque.realizada = true;
        } 
        else if(resposta == "n"){
            embarque.realizada = false;
        }
        else {
            cout << "Resposta inválida." << endl;
        }
    }while (resposta != "s" && resposta != "n");

    embarque.duracao = roteiros.at(buscarRoteiros(roteiros, codigo)).duracao;

    embarques.push_back(embarque);
}

void listarEmbarques(vector<Embarca> embarques) {
    if (embarques.size() == 0) {
        cout << "Não há embarques cadastrados" << endl;
        return;
    }
    cout << "CPF\tCodigo\tData\tHora\tDuracao\tRealizada" << endl;
    for (int i = 0; i < embarques.size(); i++) {
        cout << embarques[i].dt_hora.Data << "\t";
        cout << embarques[i].dt_hora.Hora << "\t";
        cout << embarques[i].duracao << "\t";
        cout << embarques[i].realizada << "\t";
        cout << endl;
    }
}

//Ocorrência
void gestaoOcorrencia(vector<Ocorrencia> &ocorrencias, vector<Passageiro> passageiros, vector<Roteiro> roteiros){
    int resposta;

    do{
        cout << endl << "Menu de Gestão de ocorrências:" << endl;
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar" << endl;
        cout << "4 - Listar por passageiro" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        cout << endl;
        switch (resposta) {
            case 1:
                incluirOcorrencia(ocorrencias);
                break;
            case 2:
                cout << "Espaco para excluir ocorrencia" << endl;
                break;
            case 3:
                cout << "Espaco para alterar ocorrencia" << endl;
                break;
            case 4:
                cout << "Espaco para listar por passageiro ocorrencia" << endl;
                break;
            case 5:
                listarOcorrenciasRoteiro(ocorrencias, roteiros);
        }
    } while (resposta != 0);
}

void incluirOcorrencia(vector<Embarca> &embarques){
    Ocorrencia ocorrencia;
    string resposta;
    char cpf[12], codigo[12];
    bool achou = false;

    cout << "Digite o cpf do passageiro:(Apenas 11 numeros) ";
    cin >> cpf;

    cout << "Digite o codigo do roteiro: ";
    cin >> codigo;

    cout << "Digite a data da ocorrencia:(dd/mm/aaaa) ";
    getline(cin >> ws, resposta);
    while(!verificar_data(resposta)){
        cout << "Data inválida, insira novamente:(dd/mm/aaaa) ";
        getline(cin >> ws, resposta);
    }
    ocorrencia.dt_hora.Data = resposta;

    cout << "Digite a hora da ocorrencia:(hh:mm) ";
    getline(cin >> ws, resposta);
    while(!verificar_hora(resposta)){
        cout << "Hora inválida, insira novamente:(hh:mm) ";
        getline(cin >> ws, resposta);
    }
    ocorrencia.dt_hora.Hora = resposta;

    cout << "Digite a descricao da ocorrencia: ";
    getline(cin >> ws, ocorrencia.descricao);
    
    for (int i = 0; i < embarques.size(); i++) {
        if (strcmp(embarques[i].passageiroCPF, cpf) == 0 && strcmp(embarques[i].roteiroCodigo, codigo) == 0) {
            embarques[i].ocorrencia = ocorrencia;
            achou = true;
            break;
        }
    }

    if(achou){
        cout << "Ocorrencia cadastrada com sucesso" << endl;
    }
    else{
        cout << "Embarque não encontrado" << endl;
    }
}

void listarOcorrenciasRoteiro(vector<Ocorrencia> Ocorrencias, vector<Roteiro> roteiros){
    string codigo;
    bool achou = false;

    cout << "Digite o codigo do roteiro: ";
    cin >> codigo;

    for (int i = 0; i < roteiros.size(); i++) {
        if (strcmp(roteiros[i].codigo, codigo.c_str()) == 0) {
            achou = true;
            break;
        }
    }

    if(achou){
        cout << "Data\tHora\tDescricao" << endl;
        for (int i = 0; i < Ocorrencias.size(); i++) {
            if (strcmp(Ocorrencias[i].dt_hora.Data.c_str(), roteiros[i].Data_hora.Data.c_str()) == 0) {
                cout << Ocorrencias[i].dt_hora.Data << "\t";
                cout << Ocorrencias[i].dt_hora.Hora << "\t";
                cout << Ocorrencias[i].descricao << "\t";
                cout << endl;
            }
        }
    }
    else{
        cout << "Roteiro não encontrado" << endl;
    }
}
