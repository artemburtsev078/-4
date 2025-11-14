mst_lower_bound += w
    
    approximation_ratio = tour_cost / mst_lower_bound if mst_lower_bound > 0 else float('inf')
    
    print("\nАНАЛИЗ КАЧЕСТВА РЕШЕНИЯ:")
    print(f"Стоимость найденного тура: {tour_cost}")
    print(f"Нижняя оценка (вес MST): {mst_lower_bound}")
    print(f"Коэффициент аппроксимации: {approximation_ratio:.3f}")
    
    if approximation_ratio <= 2.0:
        print("✓ Алгоритм обеспечивает 2-аппроксимацию")
    else:
        print("⚠ Коэффициент превышает 2, возможна ошибка")

# Пример использования
if name == "__main__":
    # Метрическая матрица расстояний (удовлетворяет неравенству треугольника)
    distances = [
        [0, 10, 15, 20, 25],
        [10, 0, 35, 25, 30],
        [15, 35, 0, 30, 20],
        [20, 25, 30, 0, 15],
        [25, 30, 20, 15, 0]
    ]
    
    print("МАТРИЦА РАССТОЯНИЙ (5 городов):")
    for i, row in enumerate(distances):
        print(f"Город {i}: {row}")
    
    # Запуск алгоритма
    tour, cost = tsp_2_approximation(distances)
    
    print(f"\nФИНАЛЬНЫЙ МАРШРУТ: {tour}")
    print(f"ПОРЯДОК ОБХОДА: {' → '.join(map(str, tour))}")
    
    # Анализ качества
    analyze_solution_quality(cost, distances)
    
    # Проверка корректности
    unique_cities = set(tour[:-1])
    print(f"\nПРОВЕРКА КОРРЕКТНОСТИ:")
    print(f"✓ Все города посещены: {len(unique_cities) == len(distances)}")
    print(f"✓ Маршрут замкнут: {tour[0] == tour[-1]}")
    print(f"✓ Длина маршрута: {len(tour)} точек")
    print(f"✓ Уникальных городов: {len(unique_cities)}")
