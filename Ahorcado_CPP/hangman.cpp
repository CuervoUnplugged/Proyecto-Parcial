#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

string seleccionarPalabra(vector<string>& palabras) {
    srand(time(0));
    int indice = rand() % palabras.size();
    string palabraSeleccionada = palabras[indice];
    
    transform(palabraSeleccionada.begin(), palabraSeleccionada.end(), 
              palabraSeleccionada.begin(), ::toupper);
    
    if (palabraSeleccionada.size() > 50) {
        cerr << "Error: Palabra demasiado larga." << endl;
        exit(1);
    }
    
    return palabraSeleccionada;
}

vector<char> inicializarEstado(const string& palabraSecreta) {
    vector<char> estado(palabraSecreta.size(), '_');
    return estado;
}

void visualizarEstado(const vector<char>& estado, int intentos, const vector<char>& letrasUsadas) {
    cout << "Palabra Secreta: ";
    for (size_t i = 0; i < estado.size(); i++) {
        cout << estado[i] << ' ';
    }
    cout << endl;
    cout << "Intentos restantes: " << intentos << endl;
    cout << "Letras usadas: ";
    for (size_t i = 0; i < letrasUsadas.size(); i++) {
        cout << letrasUsadas[i] << ' ';
    }
    cout << endl;
}

char validarEntrada(string entrada, const vector<char>& letrasUsadas) {
    if (entrada.length() != 1 || !isalpha(entrada[0])) {
        throw invalid_argument("Error: Debe ser una sola letra.");
    }
    
    char letra = toupper(entrada[0]);
    
    for (size_t i = 0; i < letrasUsadas.size(); i++) {
        if (letrasUsadas[i] == letra) {
            throw invalid_argument("Error: Letra ya usada.");
        }
    }
    
    return letra;
}

bool verificarLetra(const string& palabraSecreta, char letra, vector<char>& estado) {
    bool acierto = false;
    for (size_t i = 0; i < palabraSecreta.size(); i++) {
        if (palabraSecreta[i] == letra) {
            estado[i] = letra;
            acierto = true;
        }
    }
    return acierto;
}

bool verificarVictoria(const vector<char>& estado, const string& palabraSecreta) {
    for (size_t i = 0; i < estado.size(); i++) {
        if (estado[i] != palabraSecreta[i]) {
            return false;
        }
    }
    return true;
}

void registrarIntento(vector<char>& letrasUsadas, char letra) {
    letrasUsadas.push_back(letra);
}

void dibujarAhorcado(int intentos) {
    int errores = 6 - intentos;
    
    vector<string> lines(7, "          ");
    
    lines[0] = "  +---+   ";
    lines[1] = "  |   |   ";
    
    if (errores >= 1) {
        lines[2] = "  |   O   ";
    } else {
        lines[2] = "  |       ";
    }
    
    if (errores >= 2) {
        lines[3] = "  |   |   ";
    } else {
        lines[3] = "  |       ";
    }
    
    if (errores >= 3 && errores < 4) {
        lines[4] = "  |  /    ";
    } else if (errores >= 4) {
        lines[4] = "  |  /|\\  ";
    } else {
        lines[4] = "  |       ";
    }
    
    if (errores >= 5 && errores < 6) {
        lines[5] = "  |  /    ";
    } else if (errores >= 6) {
        lines[5] = "  |  / \\  ";
    } else {
        lines[5] = "  |       ";
    }
    
    lines[6] = "  |_______";
    
    for (size_t i = 0; i < lines.size(); i++) {
        cout << lines[i] << endl;
    }
    cout << endl;
}

int main() {
    vector<string> palabras = {"programacion", "computadora", "ahorcado", "algoritmo", "compilador", "lenguaje", "desarrollo", "codigo", "variable", "funcion"};
    
    string palabraSecreta = seleccionarPalabra(palabras);
    vector<char> estado = inicializarEstado(palabraSecreta);
    int intentos = 6;
    vector<char> letrasUsadas;
    
    cout << "Juego del Ahorcado\n";
    cout << "Tienes " << intentos << " intentos para adivinar la palabra.\n";
    
    while (intentos > 0 && !verificarVictoria(estado, palabraSecreta)) {
        dibujarAhorcado(intentos);
        visualizarEstado(estado, intentos, letrasUsadas);
        
        cout << "Ingresa una letra: ";
        string entrada;
        cin >> entrada;
        
        try {
            char letra = validarEntrada(entrada, letrasUsadas);
            registrarIntento(letrasUsadas, letra);
            
            if (!verificarLetra(palabraSecreta, letra, estado)) {
                intentos--;
                cout << "Letra incorrecta. Te quedan " << intentos << " intentos.\n";
            } else {
                cout << "¡Letra correcta!\n";
            }
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
    
    dibujarAhorcado(intentos);
    
    if (verificarVictoria(estado, palabraSecreta)) {
        cout << "\n¡Felicidades! Adivinaste la palabra: ";
        for (size_t i = 0; i < estado.size(); i++) {
            cout << estado[i];
        }
        cout << endl;
    } else {
        cout << "\nGame over. La palabra era: " << palabraSecreta << endl;
    }
    
    return 0;
}
