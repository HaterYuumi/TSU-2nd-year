using System;

using System.String;
//https://docs.google.com/spreadsheets/d/1MpbWQyYh2BBIxV0HYxt6X7YYSHUTbH_6f1PuH2IvGJc/edit?gid=1453611449#gid=1453611449

using System.Text; //для класса String.Builder

class Program
{
    static void Main()
    {
         Console.WriteLine("Выберите режим работы: ");
        Console.WriteLine("1 - Ввести строку вручную и перевернуть ее");
        Console.WriteLine("2 - Создать строку случайных символов заданного размера");
        Console.Write("Ваш выбор (1 или 2): ");
        
        string choice = Console.ReadLine();
        string originalString = "";
        
        if (choice == "1")
        {
          Console.WriteLine("Введите строку для переворота: ");
            originalString = Console.ReadLine();
            
            if (string.IsNullOrEmpty(originalString))
            {
                Console.WriteLine("Вы ввели пустую строку");
                return;
            }
        }
        else if (choice == "2") 
        {
          Console.WriteLine("Введите длину случайной строки: ");
            if (!int.TryParse(Console.ReadLine(), out int length) || length <= 0) // пытается преобразовать строку в целое число, если успешно сохраняет в length
            {
                Console.WriteLine("Некорректный ввод. Число должно быть положительным.");
                return;
            }
            
            originalString = GenerateRandomString(length);
            Console.WriteLine($"Сгенерированная строка: {originalString}");
        }
        else
        {
          Console.WriteLine("Некорректный выбор");
            return;
        }
        
        StringBuilder stringBuilder = new StringBuilder();
        foreach (char c in originalString)
        {
            stringBuilder.Append(c);
        }
        string builtString = stringBuilder.ToString();
        
        char[] charArray = builtString.ToCharArray();
        Array.Reverse(charArray);
        string reversedString = new string(charArray);
        
        Console.WriteLine("Результаты:");
        Console.WriteLine($"Исходная строка: {builtString}");
        Console.WriteLine($"Перевернутая строка: {reversedString}");
    }
    
    static string GenerateRandomString(int length)
    {
        Random random = new Random();
        StringBuilder sb = new StringBuilder();
        
        // Диапазон ASCII символов (от 33 до 126 - печатные символы)
        const int minChar = 33;
        const int maxChar = 126;
        
        for (int i = 0; i < length; i++)
        {
            char randomChar = (char)random.Next(minChar, maxChar + 1);
            sb.Append(randomChar);
        }
        
        return sb.ToString();
    }
}
