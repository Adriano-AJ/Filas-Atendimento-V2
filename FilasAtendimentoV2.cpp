#include <iostream>
using namespace std;

struct No {
    int dado;
    No* prox;
};

struct Fila {
    No* ini;
    No* fim;
};

struct Guiche {
    int id;
    Fila* senhasAtendidas;
    Guiche* prox;
};

// Funções para fila
Fila* initFila() {
    Fila* f = new Fila;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(Fila* f) {
    return (f->ini == NULL);
}

void enqueue(Fila* f, int v) {
    No* no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

int dequeue(Fila* f) {
    if (isEmpty(f)) {
        return -1;
    } else {
        No* no = f->ini;
        int ret = no->dado;
        f->ini = no->prox;
        if (f->ini == NULL) f->fim = NULL;
        delete no;
        return ret;
    }
}

int count(Fila* f) {
    int qtde = 0;
    No* no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void listarFila(Fila* f) {
    No* no = f->ini;
    while (no != NULL) {
        cout << no->dado << " ";
        no = no->prox;
    }
    cout << endl;
}

// Funções para lista de guichês
Guiche* criarGuiche(Guiche* lista, int id) {
    Guiche* novo = new Guiche;
    novo->id = id;
    novo->senhasAtendidas = initFila();
    novo->prox = lista;
    cout << "Guichê " << id << " aberto." << endl;
    return novo;
}

Guiche* buscarGuiche(Guiche* lista, int id) {
    Guiche* atual = lista;
    while (atual != NULL) {
        if (atual->id == id) return atual;
        atual = atual->prox;
    }
    return NULL;
}

int contarGuiches(Guiche* lista) {
    int total = 0;
    Guiche* atual = lista;
    while (atual != NULL) {
        total++;
        atual = atual->prox;
    }
    return total;
}

int main() {
    Fila* senhasGeradas = initFila();
    Guiche* guiches = NULL;
    int ultimaSenha = 0;
    int opcao;

    do {
        cout << "\n-------------------------------" << endl;
        cout << " MENU DE ATENDIMENTO 2.0" << endl;
        cout << "-------------------------------" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Gerar senha" << endl;
        cout << "2 - Abrir guichê" << endl;
        cout << "3 - Realizar atendimento" << endl;
        cout << "4 - Listar senhas atendidas por guichê" << endl;
        cout << "-------------------------------" << endl;
        cout << "Senhas aguardando: " << count(senhasGeradas) << endl;
        cout << "Guichês abertos: " << contarGuiches(guiches) << endl;
        cout << "-------------------------------" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (!isEmpty(senhasGeradas)) {
                    cout << "Ainda existem senhas aguardando atendimento. Não é possível sair agora!" << endl;
                    opcao = -1;
                } else {
                    // Contar total de senhas atendidas por todos os guichês
                    int totalAtendidas = 0;
                    Guiche* g = guiches;
                    while (g != NULL) {
                        totalAtendidas += count(g->senhasAtendidas);
                        g = g->prox;
                    }
                    cout << "Programa encerrado. Total de senhas atendidas: " << totalAtendidas << endl;
                }
                break;

            case 1:
                ultimaSenha++;
                enqueue(senhasGeradas, ultimaSenha);
                cout << "Senha gerada: " << ultimaSenha << endl;
                break;

            case 2: {
                int id;
                cout << "Digite o ID do guichê a abrir: ";
                cin >> id;
                if (buscarGuiche(guiches, id) == NULL) {
                    guiches = criarGuiche(guiches, id);
                } else {
                    cout << "Guichê já existe!" << endl;
                }
                break;
            }

            case 3: {
                if (isEmpty(senhasGeradas)) {
                    cout << "Nenhuma senha aguardando atendimento!" << endl;
                    break;
                }
                int id;
                cout << "Digite o ID do guichê que está atendendo: ";
                cin >> id;
                Guiche* g = buscarGuiche(guiches, id);
                if (g == NULL) {
                    cout << "Guichê não encontrado!" << endl;
                } else {
                    int senha = dequeue(senhasGeradas);
                    enqueue(g->senhasAtendidas, senha);
                    cout << "Guichê " << id << " atendeu a senha: " << senha << endl;
                }
                break;
            }

            case 4: {
                int id;
                cout << "Digite o ID do guichê: ";
                cin >> id;
                Guiche* g = buscarGuiche(guiches, id);
                if (g == NULL) {
                    cout << "Guichê não encontrado!" << endl;
                } else {
                    cout << "Senhas atendidas pelo guichê " << id << ": ";
                    listarFila(g->senhasAtendidas);
                }
                break;
            }

            default:
                cout << "Opção inválida!" << endl;
        }

    } while (opcao != 0);

    return 0;
}
