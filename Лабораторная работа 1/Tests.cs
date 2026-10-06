using System;

namespace Lab1_ErrorGuessing
{
    class Tests
    {
        public static void Run()
        {
            Console.WriteLine();
            Console.WriteLine("Результаты тестирования:");

            Check("Положительные числа", Program.Calculate(3, 4), 12);
            Check("Число B равно нулю", Program.Calculate(15, 0), 0);
            Check("Число B отрицательное", Program.Calculate(5, -3), -15);
            Check("Оба числа отрицательные", Program.Calculate(-4, -2), 8);
            Check("Большие числа", Program.Calculate(1000000000, 1000000000), 1000000000000000000);
        }

        static void Check(string testName, long actualResult, long expectedResult)
        {
            if (actualResult == expectedResult)
            {
                Console.WriteLine("Тест пройден: " + testName);
            }
            else
            {
                Console.WriteLine("Тест не пройден: " + testName);
                Console.WriteLine("Ожидалось: " + expectedResult);
                Console.WriteLine("Получено: " + actualResult);
            }
        }
    }
}
