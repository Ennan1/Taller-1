#include <iostream>
#include <fstream>
#include <vector>

/* iNTEGGRANTES: DIEGO AGUIRRE VALENZUEA
                 DYLAN DÍAZ BARRIENTOS
                 BRIAN MOYA ULLOA
   SECCIÓN:411
   FECHA 02/09/2023
   */


const char muro = '#';
const char camino = '*';





//Esta función imprime el contenido de una matriz (el laberinto) en la consola.
void printDaMaze(const std::vector<std::vector<char>>& _matrizLab) {
    for (const auto& row : _matrizLab) {
        for (char value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}


//Esta función busca las coordenadas de la entrada ('e') y la salida ('s') en el laberinto y las marca correctamente.
void MarcaInicioFin(std::vector<std::vector<char>>& laberinto) {
    int entradaFila , entradaColumna, salidaFila , salidaColumna;
    entradaFila = -1; //Se busca el carácter 'e' (entrada) en el laberinto y se almacenan sus coordenadas.
     salidaFila = -1;

    for (int fila = 0; fila < laberinto.size(); ++fila) {
        for (int columna = 0; columna < laberinto[fila].size(); ++columna) {
            if (laberinto[fila][columna] == ' ') {
                if (entradaFila == -1) {
                    entradaFila = fila;
                    entradaColumna = columna;
                }
                else {
                    salidaFila = fila;
                    salidaColumna = columna;
                }
            }
        }
    }

    if (entradaFila != -1) {
        laberinto[entradaFila][entradaColumna] = 'e';
    }
    if (salidaFila != -1) {
        laberinto[salidaFila][salidaColumna] = 's';
    }
}


//Esta es la función principal que implementa la búsqueda en profundidad (DFS) para encontrar un camino desde la entrada hasta la salida en el laberinto.
bool Encontrar_camino_dfs(std::vector<std::vector<char>>& laberinto, int fila, int columna) {
    if (fila < 0 || fila >= laberinto.size() || columna < 0 || columna >= laberinto[fila].size() ||
        laberinto[fila][columna] == muro || laberinto[fila][columna] == camino) {
        return false; // Fuera de los límites, es una pared o ya visitado
    }

    if (laberinto[fila][columna] == 's') {
        laberinto[fila][columna] = camino;
        return true; // Encontramos la salida
    }

    // Marcar la celda como visitada solo temporalmente
    char temp = laberinto[fila][columna];
    laberinto[fila][columna] = camino;

    // Intentamos moverse en todas las direcciones (arriba, abajo, izquierda, derecha)

    if (
            Encontrar_camino_dfs(laberinto, fila, columna + 1) || // Derecha
            Encontrar_camino_dfs(laberinto, fila + 1, columna) || // Abajo
            Encontrar_camino_dfs(laberinto, fila - 1, columna) || // Arriba
            Encontrar_camino_dfs(laberinto, fila, columna - 1)) { // Izquierda
        return true;
    }

    // No hay camino desde esta celda, revertir la marca
    laberinto[fila][columna] = temp;

    return false;
}




int main() {


    std::ofstream _salida("salida.txt");        //fichero salida
    std::ifstream _entrada("nuevo.txt");       //Abre un archivo llamado "nuevo.txt" para leer el laberinto. Si no se puede abrir, muestra un mensaje de error.

    if(!_entrada.is_open()){
        std::cout << "No se pudo leer el fichero" << std::endl;
        return 1;
    }

    std::vector<std::string> _laberinto;
    std::string linea;

    //El laberinto se lee desde el archivo línea por línea y se almacena en _laberinto. Luego, se copia a matrizLaberinto para trabajar con él.

    while( getline(_entrada, linea) ){
        _laberinto.push_back(linea);
    }

    _entrada.close();

    int _filas = _laberinto.size();
    int _columnas = _laberinto[0].size();

    std::cout << "filas: " << _filas << std::endl;
    std::cout << "columnas: " << _columnas << std::endl;


    //matriz

    std::vector<std::vector<char>> matrizLaberinto(_filas, std::vector<char>(_columnas));

    // Transformar vector a matriz.

    for(int i = 0; i < _filas; i++){
        for(int j = 0; j < _columnas; j++){
            matrizLaberinto[i][j] = _laberinto[i][j];
        }
    }

    printDaMaze(matrizLaberinto);

    MarcaInicioFin(matrizLaberinto);


    // Obtén las coordenadas de la entrada ('e')
    int entradaFila = -1;
    int entradaColumna;
    for (int fila = 0; fila < matrizLaberinto.size(); ++fila) {
        for (int columna = 0; columna < matrizLaberinto[fila].size(); ++columna) {
            if (matrizLaberinto[fila][columna] == 'e') {
                entradaFila = fila;
                entradaColumna = columna;
                break;
            }
        }
        if (entradaFila != -1) {
            break;
        }
    }

    //std::cout << "\nLaberinto con entradas (e) y salidas (s):\n";
    //printDaMaze(matrizLaberinto);


    // Verificar si la copia de la matriz es correcta c:.

    /*for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            std::cout << matrizLaberinto[i][j];
        }
        std::cout << std::endl;
    }*/


    /*if(resolver(partida.x, partida.y, _filas, _columnas, matrizLaberinto)){
        printDaMaze(_filas, matrizLaberinto);
    }else
    {
        std::cout << "No se pudo resolver el laberinto" << std::endl;
    }

    */
    // std::cout << "Hello, World!" << std::endl;

      //Se llama a la función Encontrar_camino_dfs con las coordenadas de entrada como punto de inicio para buscar un camino hacia la salida.
    //Si se encuentra un camino, se muestra la solución en la consola.
    if(Encontrar_camino_dfs(matrizLaberinto, entradaFila, entradaColumna)){
        printDaMaze(matrizLaberinto);
    }else
    {
        std::cout << "No se pudo resolver el laberinto" << std::endl;
    }


    // std::cout << "Hello, World!" << std::endl;

    // Se verifica si el archivo de salida se puede abrir. Si es así, se escribe la solución en el archivo de salida ("salida.txt").
    if(!_salida.is_open()) {
        std::cout << "No se puede abrir el fichero de salida" << std::endl;
    }else {
        for (int i = 0; i < _filas; i++) {
            for (int j = 0; j < _columnas; j++) {
                _salida << matrizLaberinto[i][j];
            }
            _salida << std::endl;
        }
    }
     //Se cierra el archivo de salida después de haber guardado la solución.

    _salida.close();

    return 0;
}
