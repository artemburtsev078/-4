#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;
using std::reverse;

// Вычисление длины маршрута
double calculatePathLength(const vector<int>& tour, const vector<vector<double>>& distanceMatrix) {
    double totalLength = 0.0;
    int numberOfPoints = tour.size();
    
    for (int i = 0; i < numberOfPoints - 1; i++) {
        int from = tour[i];
        int to = tour[i + 1];
        totalLength += distanceMatrix[from][to];
    }
    
    // Замыкаем маршрут (возврат к начальной точке)
    if (numberOfPoints > 1) {
        totalLength += distanceMatrix[tour.back()][tour[0]];
    }
    
    return totalLength;
}

// Проверка улучшения при перестановке рёбер
bool willImproveRoute(int point1, int point2, const vector<int>& route, 
                     const vector<vector<double>>& distances) {
    int prevPoint1 = route[point1 - 1];
    int currPoint1 = route[point1];
    int currPoint2 = route[point2];
    int nextPoint2 = route[point2 + 1];
    
    double currentDistance = distances[prevPoint1][currPoint1] + 
                           distances[currPoint2][nextPoint2];
    double newDistance = distances[prevPoint1][currPoint2] + 
                       distances[currPoint1][nextPoint2];
    
    return newDistance < currentDistance;
}

// Основная функция оптимизации маршрута
vector<int> optimizeRoute(vector<int> route, const vector<vector<double>>& distanceMatrix) {
    if (route.size() <= 3) return route; // Слишком короткий маршрут для оптимизации
    
    bool improvementFound;
    int routeLength = route.size();
    
    do {
        improvementFound = false;
        
        // Перебираем все возможные пары рёбер для перестановки
        for (int i = 1; i < routeLength - 2; i++) {
            for (int j = i + 1; j < routeLength - 1; j++) {
                
                if (willImproveRoute(i, j, route, distanceMatrix)) {
                    // Переворачиваем segment между точками i и j
                    reverse(route.begin() + i, route.begin() + j + 1);
                    improvementFound = true;
                }
            }
        }
        
    } while (improvementFound); // Продолжаем, пока есть улучшения
    
    return route;
}

// Вспомогательная функция для вывода маршрута
void printRoute(const vector<int>& route, const std::string& label = "Маршрут") {
    std::cout << label << ": ";
    for (int point : route) {
        std::cout << point << " ";
    }
    std::cout << "-> " << route[0] << std::endl;
}

// Пример использования
int main() {
    // Пример матрицы расстояний (5 городов)
    vector<vector<double>> distances = {
        {0, 10, 15, 20, 25},
        {10, 0, 35, 25, 30},
        {15, 35, 0, 30, 40},
        {20, 25, 30, 0, 45},
        {25, 30, 40, 45, 0}
    };
    
    // Начальный маршрут (просто по порядку)
    vector<int> initialRoute = {0, 1, 2, 3, 4};
    
    std::cout << "Начальная длина: " << calculatePathLength(initialRoute, distances) << std::endl;
    printRoute(initialRoute, "Исходный маршрут");
    
    // Оптимизируем маршрут
    vector<int> optimizedRoute = optimizeRoute(initialRoute, distances);
    
    std::cout << "Оптимизированная длина: " << calculatePathLength(optimizedRoute, distances) << std::endl;
    printRoute(optimizedRoute, "Оптимизированный маршрут");
    
    return 0;
}
