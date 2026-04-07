using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        Console.WriteLine("Введите минимальное значение для элементов массива:");
        int minValue = int.Parse(Console.ReadLine());
        
        Console.WriteLine("Введите максимальное значение для элементов массива:");
        int maxValue = int.Parse(Console.ReadLine());
        
        if (minValue > maxValue)
        {
            Console.WriteLine("Ошибка: минимальное значение больше максимального!");
            return;
        }

        int[] array = GenerateRandomArray(10, minValue, maxValue);
        
        Console.WriteLine("Сгенерированный массив:");
        Console.WriteLine(string.Join(", ", array));

        try
        {
            List<int> longest = FindLongest(array);

            Console.WriteLine("Самая длинная знакопеременная подпоследовательность:");
            foreach (int num in longest)
            {
                Console.Write(num + " ");
            }
            Console.WriteLine();
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
    }

    static int[] GenerateRandomArray(int size, int minValue, int maxValue)
    {
        int[] array = new int[size];
        Random random = new Random();
        
        for (int i = 0; i < array.Length; i++)
        {
            int tmp = random.Next(minValue, maxValue + 1);
            
            while (tmp == 0)
            {
                tmp = random.Next(minValue, maxValue + 1);
            }
            array[i] = tmp;
        }
        
        return array;
    }

    static List<int> FindLongest(int[] array)
    {
        if (array == null || array.Length == 0)
        {
            throw new ArgumentException("Массив пуст!", nameof(array));
        }

        if (array.Any(x => x == 0))
        {
            throw new ArgumentException("Массив содержит нули!", nameof(array));
        }

        List<List<int>> sequences = new List<List<int>>();
        List<int> currentSequence = new List<int> { array[0] };
        sequences.Add(new List<int>(currentSequence));

        for (int i = 1; i < array.Length; i++)
        {
            if (array[i] * array[i - 1] < 0)
            {
                currentSequence.Add(array[i]);
            }
            else
            {
                currentSequence = new List<int> { array[i] };
            }

            sequences.Add(new List<int>(currentSequence));
        }

        List<int> longest = sequences[0];
        foreach (var seq in sequences)
        {
            if (seq.Count > longest.Count)
            {
                longest = seq;
            }
        }

        return longest;
    }
}
