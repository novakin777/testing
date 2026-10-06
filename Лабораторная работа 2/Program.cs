using System;

namespace Lab2.UnitTesting
{
    class Program
    {
        static void Main(string[] args)
        {
            FactorialCalculator calculator = new FactorialCalculator();
            NumberHelper helper = new NumberHelper();

            int factorialNumber = ReadNumber("Введите число от 0 до 12 для вычисления факториала: ");

            while (factorialNumber < 0 || factorialNumber > 12)
            {
                Console.WriteLine("Ошибка. Число должно быть от 0 до 12.");
                factorialNumber = ReadNumber("Введите число от 0 до 12: ");
            }

            int factorialResult = calculator.Factorial(factorialNumber);
            Console.WriteLine("Факториал числа " + factorialNumber + " равен " + factorialResult);

            int firstNumber = ReadNumber("Введите первое целое число: ");
            int secondNumber = ReadNumber("Введите второе целое число: ");

            bool firstNumberIsEven = helper.IsEven(firstNumber);
            int maxNumber = helper.GetMax(firstNumber, secondNumber);

            if (firstNumberIsEven == true)
            {
                Console.WriteLine("Первое число является четным.");
            }
            else
            {
                Console.WriteLine("Первое число является нечетным.");
            }

            Console.WriteLine("Максимальное число: " + maxNumber);
        }

        static int ReadNumber(string message)
        {
            int number;
            Console.Write(message);

            while (!int.TryParse(Console.ReadLine(), out number))
            {
                Console.WriteLine("Ошибка. Нужно ввести целое число.");
                Console.Write(message);
            }

            return number;
        }
    }

    public class FactorialCalculator
    {
        public int Factorial(int number)
        {
            if (number < 0)
            {
                return 0;
            }

            int result = 1;

            for (int i = 1; i <= number; i++)
            {
                result = result * i;
            }

            return result;
        }
    }

    public class NumberHelper
    {
        public bool IsEven(int number)
        {
            if (number % 2 == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public int GetMax(int firstNumber, int secondNumber)
        {
            if (firstNumber > secondNumber)
            {
                return firstNumber;
            }
            else
            {
                return secondNumber;
            }
        }
    }
}
