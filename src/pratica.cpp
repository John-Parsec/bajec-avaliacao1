#include <ctime>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

typedef struct Passageiro {
    char cpf[12];
    string nome;
    string dtNascimento;
    int numAutorizacao;
} Passageiro;

typedef struct Roteiro {
    int codigo;
    string data_hora;
    int duracao;
    string origem;
    string destino;

} Roteiro;

bool verificar_data(string data)
{
    std::string d, m, a, str;
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

    if(valido && ia > 2023)
        valido = 0;

    return valido;
}

bool verificar_hora(string hora)
{
    std::string hr, min, str;
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

bool temMaisde18(string dataNasc);
bool validaCPF(char cpf[12]) {
    // Verifica se o CPF possui 11 dígitos
    if (strlen(cpf) != 11)
        return false;

    // Verifica se todos os caracteres são dígitos numéricos
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i]))
            return false;
    }

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

void incluirPassageiro(vector<Passageiro> &passageiros);
void listarPassageiros(vector<Passageiro> passageiros);
int buscarPassageiros(vector<Passageiro> passageiros, char cpf[12]);
void excluirPassageiro(vector<Passageiro> &passageiros, char cpf[12]);
void alterarPassageiro(vector<Passageiro> &passageiros, char cpf[12]);

void incluirRoteiro(vector<Roteiro> &roteiros);
void listarRoteiros(vector<Roteiro> roteiros);
int buscarRoteiros(vector<Roteiro> roteiros, int codigo);
void excluirRoteiro(vector<Roteiro> &roteiros, int codigo);
void alterarRoteiro(vector<Roteiro> &roteiros, int codigo);

void gestaoPassageiro(vector<Passageiro> &passageiros) {
    int resposta;
    char cpf[12];
    cout << "Menu de Gestão de passageiros:" << endl;
    do {
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar (por cpf)" << endl;
        cout << "4 - Listar" << endl;
        cout << "5 - Localizar (por cpf)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
        switch (resposta) {
            case 1:
                incluirPassageiro(passageiros);
                break;
            case 2:
                cout << "Digite o cpf do passageiro: ";
                cin >> cpf;
                excluirPassageiro(passageiros, cpf);
                break;
            case 3:
                cout << "Digite o cpf do passageiro: ";
                cin >> cpf;
                alterarPassageiro(passageiros, cpf);
                break;

            case 4:
                listarPassageiros(passageiros);
                break;
            case 5:
                cout << "Digite o cpf do passageiro: ";
                cin >> cpf;
                buscarPassageiros(passageiros, cpf);
                break;
        }

    } while (resposta != 0);
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
void incluirPassageiro(vector<Passageiro> &passageiros) {
    Passageiro passageiro;
    do {
        cout << "Digite o cpf do passageiro: ";
        cin >> passageiro.cpf;
        if (!validaCPF(passageiro.cpf)) {
            cout << "CPF inválido" << endl;
        }
        if (!cpfUnico(passageiros, passageiro.cpf)) {
            cout << "CPF já cadastrado" << endl;
        }
    } while (!validaCPF(passageiro.cpf) || !cpfUnico(passageiros, passageiro.cpf));
    cout << "Digite o nome do passageiro: ";
    cin >> passageiro.nome;
    cout << "Digite a data de nascimento do passageiro: ";
    cin >> passageiro.dtNascimento;
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
        cin >> resposta;
        passageiros.at(posicao).nome = resposta;
    }

    cout << "Deseja alterar a data de nascimento? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova data de nascimento: ";
        cin >> resposta;
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

// Roteiro
void gestaoRoteiro(vector<Roteiro> &roteiros) {
    int resposta;
    int codigo;
    cout << "Menu de Gestão de roteiros:" << endl;
    do {
        cout << "1 - Incluir" << endl;
        cout << "2 - Excluir" << endl;
        cout << "3 - Alterar (por codigo)" << endl;
        cout << "4 - Listar" << endl;
        cout << "5 - Localizar (por codigo)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> resposta;
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
    cout << "Digite o codigo do roteiro: ";
    cin >> roteiro.codigo;
    cin.ignore();
    cout << "Digite a data e hora prevista: ";
    getline(cin, resposta);
    roteiro.data_hora = resposta;
    cout << "Digite a duracao do roteiro: ";
    cin >> roteiro.duracao;
    cin.ignore();
    cout << "Digite a origem do roteiro: ";
    getline(cin, resposta);
    roteiro.origem = resposta;
    cout << "Digite o destino do roteiro: ";
    getline(cin, resposta);
    roteiro.destino = resposta;

    roteiros.push_back(roteiro);
}
void listarRoteiros(vector<Roteiro> roteiros) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return;
    }
    cout << "Codigo\tData e Hora\tDuracao\tOrigem\tDestino" << endl;
    for (int i = 0; i < roteiros.size(); i++) {
        cout << roteiros[i].codigo << "\t";
        cout << roteiros[i].data_hora << "\t";
        cout << roteiros[i].duracao << "\t";
        cout << roteiros[i].origem << "\t";
        cout << roteiros[i].destino << "\t";
        cout << endl;
    }
}
int buscarRoteiros(vector<Roteiro> roteiros, int codigo) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return -1;
    }
    for (int i = 0; i < roteiros.size(); i++) {
        if (roteiros[i].codigo == codigo) {
            cout << "Codigo: " << roteiros[i].codigo << endl;
            cout << "Data e Hora: " << roteiros[i].data_hora << endl;
            cout << "Duracao: " << roteiros[i].duracao << endl;
            cout << "Origem: " << roteiros[i].origem << endl;
            cout << "Destino: " << roteiros[i].destino << endl;
            return i;
        }
    }
    cout << "Roteiro não encontrado" << endl;
    return -1;
}
void excluirRoteiro(vector<Roteiro> &roteiros, int codigo) {
    if (roteiros.size() == 0) {
        cout << "Não há roteiros cadastrados" << endl;
        return;
    }
    for (auto x = roteiros.begin(); x != roteiros.end(); x++) {
        if (x->codigo == codigo) {
            roteiros.erase(x);
            cout << "Roteiro excluido com sucesso" << endl;
            return;
        }
    }
    cout << "Roteiro não encontrado" << endl;
}
void alterarRoteiro(vector<Roteiro> &roteiros, int codigo) {
    int posicao = buscarRoteiros(roteiros, codigo);
    string resposta;
    if (posicao == -1) {
        return;
    }
    cout << "Deseja alterar a data e hora? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova data e hora: ";
        cin >> resposta;
        roteiros.at(posicao).data_hora = resposta;
    }

    cout << "Deseja alterar a duracao? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova duracao: ";
        cin >> resposta;
        roteiros.at(posicao).duracao = stoi(resposta);
    }

    cout << "Deseja alterar a origem? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite a nova origem: ";
        cin >> resposta;
        roteiros.at(posicao).origem = resposta;
    }

    cout << "Deseja alterar o destino? (s/n)";
    cin >> resposta;
    if (resposta == "s") {
        cout << "Digite o novo destino: ";
        cin >> resposta;
        roteiros.at(posicao).destino = resposta;
    }
}

int main(void) {
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;

    int resposta;
    cout << "Menu de Geral:" << endl;

    do {
        cout << "1 - Gestão de Passageiros" << endl;
        cout << "2 - Gestão de Roteiros" << endl;
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
        }
    } while (resposta != 0);

    return 0;
}