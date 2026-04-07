using System;

class Program
{
    static void Main()
    {
        int rows, cols;

        do {
            Console.Write("Введите количество строк (>0): ");
        } while (!int.TryParse(Console.ReadLine(), out rows) || rows <= 0);
        
        do {
            Console.Write("Введите количество столбцов (>0): ");
        } while (!int.TryParse(Console.ReadLine(), out cols) || cols <= 0);
        
        Console.WriteLine("Введите минимальное значение для элементов массива:");
        double minValue = double.Parse(Console.ReadLine());
        
        Console.WriteLine("Введите максимальное значение для элементов массива:");
        double maxValue = double.Parse(Console.ReadLine());
        
        if (minValue > maxValue)
        {
            Console.WriteLine("Ошибка: минимальное значение больше максимального!");
            return;
        }
        
        double[,] matrix = GenerateRandomMatrix(rows, cols, minValue, maxValue);
        
        Console.WriteLine("Сгенерированная матрица:");
        PrintMatrix(matrix);
        
        double scalar = CalculateScalar(matrix);
        Console.WriteLine($"\nСкалярное произведение: {scalar:F4}");
    }
    
    static double[,] GenerateRandomMatrix(int rows, int cols, double minValue, double maxValue) 
    {
        double[,] matrix = new double[rows, cols];
        Random random = new Random();
        
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                matrix[i, j] = random.NextDouble() * (maxValue - minValue) + minValue;
            }
        }
        
        return matrix;
    }
    
    static void PrintMatrix(double[,] matrix) 
    {
        Console.Write("      ");
        for (int j = 0; j < matrix.GetLength(1); j++)
        {
            Console.Write($"Col {j+1}".PadLeft(10));
        }
        Console.WriteLine("\n" + new string('-', 10 * (matrix.GetLength(1) + 1)));
    
        for (int i = 0; i < matrix.GetLength(0); i++)
        {
            Console.Write($"Row {i+1}|");
            for (int j = 0; j < matrix.GetLength(1); j++)
            {
                Console.Write($"{matrix[i, j]:F2}".PadLeft(10));
            }
            Console.WriteLine();
        }
    }
    
    static double CalculateScalar(double[, ] matrix) {
      int rows = matrix.GetLength(0);
      int cols = matrix.GetLength(1);
      
      double max_el = matrix[0, 0];
      int max_row = 0;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (matrix [i, j] > max_el) {
            max_el = matrix[i, j];
            max_row = i;
          }
        }
      }
      
      double min_el = matrix[0, 0];
      int min_col = 0;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          if (matrix [i, j] < min_el) {
            min_el = matrix[i, j];
            min_col = j;
          }
        }
      }
      
      Console.WriteLine($"\nНаибольший элемент: {max_el:F2} (строка {max_row + 1})");
      Console.WriteLine($"Наименьший элемент: {min_el:F2} (столбец {min_col + 1})");
      
      double result = 0;
        for (int k = 0; k < cols; k++)
        {
            result += matrix[max_row, k] * matrix[k, min_col];
        }

        return result;
    }
}
