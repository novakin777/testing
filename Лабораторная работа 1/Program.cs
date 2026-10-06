using System;

namespace Lab1_ErrorGuessing
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Лабораторная работа 1. Вариант 1 - ИИ");
            Console.WriteLine("1 - Запустить программу");
            Console.WriteLine("2 - Запустить тесты");
            Console.Write("Выберите действие: ");

            string choice = Console.ReadLine();

            if (choice == "2")
            {
                Tests.Run();
                return;
            }

            long numberA = ReadNumber("Введите число A: ");
            long numberB = ReadNumber("Введите число B: ");
            long result = Calculate(numberA, numberB);

            Console.WriteLine("Контрольное значение: " + result);
        }

        public static long Calculate(long numberA, long numberB)
        {
            long result = numberA * numberB;
            return result;
        }

        static long ReadNumber(string message)
        {
            long number;
            Console.Write(message);

            while (!long.TryParse(Console.ReadLine(), out number) ||
                   number < -1000000000 || number > 1000000000)
            {
                Console.WriteLine("Ошибка. Введите целое число от -1000000000 до 1000000000.");
                Console.Write(message);
            }

            return number;
        }
    }
}
