/*
 * APS3 - Problema da Mochila 0-1
 * Implementação dos três algoritmos:
 *   1. Algoritmo Guloso (razão valor/peso)
 *   2. Força Bruta recursivo
 *   3. Programação Dinâmica bottom-up
 *
 * Compilar: g++ -O2 -o knapsack knapsack.cpp
 * Executar: ./knapsack
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>
#include <climits>

using namespace std;
using namespace chrono;

// ============================================================
//  Estrutura de item
// ============================================================
struct Item {
    int id;
    int peso;
    int valor;
    double razao; // valor / peso
};

// ============================================================
//  Gerador de instâncias aleatórias
// ============================================================
vector<Item> gerarInstancia(int n, int pesoMin, int pesoMax,
                             int valorMin, int valorMax, unsigned seed = 42) {
    mt19937 rng(seed);
    uniform_int_distribution<int> distPeso(pesoMin, pesoMax);
    uniform_int_distribution<int> distValor(valorMin, valorMax);

    vector<Item> itens(n);
    for (int i = 0; i < n; i++) {
        itens[i].id    = i + 1;
        itens[i].peso  = distPeso(rng);
        itens[i].valor = distValor(rng);
        itens[i].razao = (double)itens[i].valor / itens[i].peso;
    }
    return itens;
}

// ============================================================
//  1. ALGORITMO GULOSO (razão valor/peso)
//     Complexidade: O(n log n) — dominada pela ordenação
// ============================================================
struct ResultadoGuloso {
    int valorTotal;
    int pesoTotal;
    vector<int> itensSelecionados; // ids dos itens
};

ResultadoGuloso guloso(vector<Item> itens, int capacidade) {
    // Ordena por razão valor/peso em ordem decrescente
    sort(itens.begin(), itens.end(), [](const Item& a, const Item& b) {
        return a.razao > b.razao;
    });

    ResultadoGuloso res = {0, 0, {}};
    int capacidadeRestante = capacidade;

    for (const auto& item : itens) {
        if (item.peso <= capacidadeRestante) {
            res.valorTotal += item.valor;
            res.pesoTotal  += item.peso;
            res.itensSelecionados.push_back(item.id);
            capacidadeRestante -= item.peso;
        }
    }
    return res;
}

// ============================================================
//  2. FORÇA BRUTA RECURSIVA
//     Complexidade: O(2^n)
// ============================================================
struct ResultadoFB {
    int valorTotal;
    int pesoTotal;
    vector<int> itensSelecionados;
};

// Variáveis globais para rastrear a melhor solução na força bruta
static int melhorValorFB;
static int melhorPesoFB;
static vector<int> melhorItensFB;

void forcaBrutaRec(const vector<Item>& itens, int idx, int capacidade,
                   int valorAtual, int pesoAtual, vector<int>& itensAtuais) {
    // Caso base: todos os itens foram considerados
    if (idx == (int)itens.size()) {
        if (valorAtual > melhorValorFB) {
            melhorValorFB = valorAtual;
            melhorPesoFB  = pesoAtual;
            melhorItensFB = itensAtuais;
        }
        return;
    }

    // Ramo 1: NÃO inclui o item idx
    forcaBrutaRec(itens, idx + 1, capacidade, valorAtual, pesoAtual, itensAtuais);

    // Ramo 2: Inclui o item idx (se couber)
    if (pesoAtual + itens[idx].peso <= capacidade) {
        itensAtuais.push_back(itens[idx].id);
        forcaBrutaRec(itens, idx + 1, capacidade,
                      valorAtual + itens[idx].valor,
                      pesoAtual  + itens[idx].peso,
                      itensAtuais);
        itensAtuais.pop_back();
    }
}

ResultadoFB forcaBruta(const vector<Item>& itens, int capacidade) {
    melhorValorFB = 0;
    melhorPesoFB  = 0;
    melhorItensFB.clear();

    vector<int> itensAtuais;
    forcaBrutaRec(itens, 0, capacidade, 0, 0, itensAtuais);

    return {melhorValorFB, melhorPesoFB, melhorItensFB};
}

// ============================================================
//  3. PROGRAMAÇÃO DINÂMICA BOTTOM-UP
//     Complexidade: O(n * Q) em tempo e espaço
// ============================================================
struct ResultadoPD {
    int valorTotal;
    int pesoTotal;
    vector<int> itensSelecionados;
};

ResultadoPD programacaoDinamica(const vector<Item>& itens, int capacidade) {
    int n = itens.size();

    // dp[i][w] = valor máximo usando os i primeiros itens com capacidade w
    // Usamos long long para evitar overflow em instâncias grandes
    vector<vector<long long>> dp(n + 1, vector<long long>(capacidade + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacidade; w++) {
            // Não inclui o item i
            dp[i][w] = dp[i-1][w];
            // Inclui o item i (se couber)
            if (itens[i-1].peso <= w) {
                long long comItem = dp[i-1][w - itens[i-1].peso] + itens[i-1].valor;
                if (comItem > dp[i][w])
                    dp[i][w] = comItem;
            }
        }
    }

    // Backtracking para descobrir quais itens foram selecionados
    ResultadoPD res;
    res.valorTotal = (int)dp[n][capacidade];
    res.pesoTotal  = 0;

    int w = capacidade;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            // O item i foi incluído
            res.itensSelecionados.push_back(itens[i-1].id);
            res.pesoTotal += itens[i-1].peso;
            w -= itens[i-1].peso;
        }
    }
    reverse(res.itensSelecionados.begin(), res.itensSelecionados.end());

    return res;
}

// ============================================================
//  Utilitários de exibição
// ============================================================
void imprimirSeparador(char c = '=', int n = 72) {
    cout << string(n, c) << "\n";
}

void imprimirItens(const vector<Item>& itens, int maxExibir = 10) {
    int exibir = min((int)itens.size(), maxExibir);
    cout << "  Id  Peso  Valor  Razão V/P\n";
    cout << "  " << string(32, '-') << "\n";
    for (int i = 0; i < exibir; i++) {
        cout << "  " << setw(3) << itens[i].id
             << "  " << setw(4) << itens[i].peso
             << "  " << setw(5) << itens[i].valor
             << "  " << fixed << setprecision(2) << itens[i].razao << "\n";
    }
    if ((int)itens.size() > maxExibir)
        cout << "  ... (e mais " << itens.size() - maxExibir << " itens)\n";
}

template<typename Func>
auto medirTempo(Func f) {
    auto inicio = high_resolution_clock::now();
    auto resultado = f();
    auto fim = high_resolution_clock::now();
    double ms = duration<double, milli>(fim - inicio).count();
    return make_pair(ms, resultado);
}

// ============================================================
//  Execução de um experimento completo
// ============================================================
struct ConfigTeste {
    int    n;
    int    Q;
    int    pesoMin, pesoMax;
    int    valorMin, valorMax;
    bool   executarFB; // Força Bruta pode ser inviável para n grande
};

void executarExperimento(const ConfigTeste& cfg, unsigned seed = 42) {
    imprimirSeparador();
    cout << "INSTÂNCIA: n=" << cfg.n << "  Q=" << cfg.Q
         << "  pesos=[" << cfg.pesoMin << "," << cfg.pesoMax << "]"
         << "  valores=[" << cfg.valorMin << "," << cfg.valorMax << "]\n";
    imprimirSeparador();

    // Geração de instância
    vector<Item> itens = gerarInstancia(cfg.n, cfg.pesoMin, cfg.pesoMax,
                                        cfg.valorMin, cfg.valorMax, seed);

    if (cfg.n <= 20) {
        cout << "Itens gerados:\n";
        imprimirItens(itens, cfg.n);
        cout << "\n";
    }

    // --- Guloso ---
    {
        auto p = medirTempo([&]{ return guloso(itens, cfg.Q); });
        double tempo = p.first;
        auto res = p.second;
        cout << "[GULOSO]  Valor=" << res.valorTotal
             << "  Peso=" << res.pesoTotal
             << "  Tempo=" << fixed << setprecision(4) << tempo << " ms\n";
        if (cfg.n <= 20 && !res.itensSelecionados.empty()) {
            cout << "  Itens selecionados: ";
            for (int id : res.itensSelecionados) cout << id << " ";
            cout << "\n";
        }
    }

    // --- Força Bruta ---
    if (cfg.executarFB) {
        auto p = medirTempo([&]{ return forcaBruta(itens, cfg.Q); });
        double tempo = p.first;
        auto res = p.second;
        cout << "[F.BRUTA] Valor=" << res.valorTotal
             << "  Peso=" << res.pesoTotal
             << "  Tempo=" << fixed << setprecision(4) << tempo << " ms\n";
        if (cfg.n <= 20 && !res.itensSelecionados.empty()) {
            cout << "  Itens selecionados: ";
            for (int id : res.itensSelecionados) cout << id << " ";
            cout << "\n";
        }
    } else {
        cout << "[F.BRUTA] INVIÁVEL - complexidade O(2^" << cfg.n
             << ") tornaria a execução proibitiva.\n";
    }

    // --- Programação Dinâmica ---
    // Verifica viabilidade de memória: n * Q cells
    long long celulas = (long long)cfg.n * cfg.Q;
    if (celulas > 500000000LL) { // ~500M células seria ~4GB com long long
        cout << "[P.DIN.]  INVIÁVEL (memória) - tabela seria "
             << celulas / 1000000 << "M células\n";
    } else {
        auto p = medirTempo([&]{ return programacaoDinamica(itens, cfg.Q); });
        double tempo = p.first;
        auto res = p.second;
        cout << "[P.DIN.]  Valor=" << res.valorTotal
             << "  Peso=" << res.pesoTotal
             << "  Tempo=" << fixed << setprecision(4) << tempo << " ms\n";
        if (cfg.n <= 20 && !res.itensSelecionados.empty()) {
            cout << "  Itens selecionados: ";
            for (int id : res.itensSelecionados) cout << id << " ";
            cout << "\n";
        }
    }
    cout << "\n";
}

// ============================================================
//  Main
// ============================================================
int main() {
    cout << "\n";
    imprimirSeparador('*');
    cout << "  APS3 - Problema da Mochila 0-1\n";
    cout << "  Algoritmos: Guloso | Força Bruta | Programação Dinâmica\n";
    imprimirSeparador('*');
    cout << "\n";

    // Instâncias conforme especificação da APS3
    // n      Q    pMin pMax vMin vMax  exec_FB
    vector<ConfigTeste> testes = {
        {    20,    10,  1,  10,  1, 1000, true  },
        {    50,    30,  1,  30,  1, 1000, true  },
        {   100,    30,  1,  30,  1, 1000, false }, // 2^100 inviável
        {   200,    50,  1,  50,  1, 1000, false },
        {   500,    10,  1,  10,  1, 1000, false },
        {   500,   100,  1, 100,  1, 1000, false },
        {  1000,    50,  1,  50,  1, 1000, false },
        { 10000,   100,  1, 100,  1, 1000, false },
        {500000,   100,  1, 100,  1, 1000, false },
    };

    for (const auto& cfg : testes) {
        executarExperimento(cfg, 42);
    }

    // Demonstração detalhada com exemplo pequeno
    imprimirSeparador('=');
    cout << "DEMONSTRAÇÃO DETALHADA (exemplo dos slides)\n";
    imprimirSeparador('=');
    {
        // Exemplo clássico: 5 itens
        vector<Item> ex = {
            {1, 10,  7, 0.7},
            {2, 20, 10, 0.5},
            {3,  5,  8, 1.6},
            {4,  4,  6, 1.5},
            {5, 15,  9, 0.6},
        };
        int cap = 30;
        cout << "Itens:\n";
        imprimirItens(ex, 10);
        cout << "Capacidade Q = " << cap << "\n\n";

        auto rG  = guloso(ex, cap);
        auto rFB = forcaBruta(ex, cap);
        auto rPD = programacaoDinamica(ex, cap);

        auto mostrar = [](const string& nome, int v, int p, const vector<int>& ids) {
            cout << nome << ": Valor=" << v << "  Peso=" << p << "  Itens=[";
            for (int i = 0; i < (int)ids.size(); i++) {
                if (i) cout << ", ";
                cout << ids[i];
            }
            cout << "]\n";
        };
        mostrar("Guloso  ", rG.valorTotal,  rG.pesoTotal,  rG.itensSelecionados);
        mostrar("F.Bruta ", rFB.valorTotal, rFB.pesoTotal, rFB.itensSelecionados);
        mostrar("P.Din.  ", rPD.valorTotal, rPD.pesoTotal, rPD.itensSelecionados);

        if (rG.valorTotal == rFB.valorTotal)
            cout << "\n→ Guloso encontrou a solução ÓTIMA neste caso!\n";
        else
            cout << "\n→ Guloso encontrou solução SUB-ÓTIMA (Ótimo="
                 << rFB.valorTotal << ")\n";
    }

    cout << "\n";
    imprimirSeparador('*');
    cout << "  Complexidades:\n";
    cout << "  Guloso      : O(n log n)\n";
    cout << "  Força Bruta : O(2^n)\n";
    cout << "  Prog. Din.  : O(n * Q) tempo | O(n * Q) espaço\n";
    imprimirSeparador('*');
    cout << "\n";

    return 0;
}
