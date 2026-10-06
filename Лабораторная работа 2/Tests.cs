using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Lab2.UnitTesting
{
    [TestClass]
    public class ТестыФакториала
    {
        [TestMethod]
        public void Факториал_Нуля_Равен_Одному()
        {
            FactorialCalculator calculator = new FactorialCalculator();
            int result = calculator.Factorial(0);
            Assert.AreEqual(1, result);
        }

        [TestMethod]
        public void Факториал_Трех_Равен_Шести()
        {
            FactorialCalculator calculator = new FactorialCalculator();
            int result = calculator.Factorial(3);
            Assert.AreEqual(6, result);
        }

        [TestMethod]
        public void Факториал_Пяти_Равен_СтаДвадцати()
        {
            FactorialCalculator calculator = new FactorialCalculator();
            int result = calculator.Factorial(5);
            Assert.AreEqual(120, result);
        }

        [TestMethod]
        public void Факториал_Отрицательного_Числа_Равен_Нулю()
        {
            FactorialCalculator calculator = new FactorialCalculator();
            int result = calculator.Factorial(-2);
            Assert.AreEqual(0, result);
        }
    }

    [TestClass]
    public class ТестыЧисел
    {
        [TestMethod]
        public void Число_Четыре_Является_Четным()
        {
            NumberHelper helper = new NumberHelper();
            bool result = helper.IsEven(4);
            Assert.AreEqual(true, result);
        }

        [TestMethod]
        public void Число_Пять_Не_Является_Четным()
        {
            NumberHelper helper = new NumberHelper();
            bool result = helper.IsEven(5);
            Assert.AreEqual(false, result);
        }

        [TestMethod]
        public void Если_Первое_Число_Больше_Возвращается_Первое()
        {
            NumberHelper helper = new NumberHelper();
            int result = helper.GetMax(8, 3);
            Assert.AreEqual(8, result);
        }

        [TestMethod]
        public void Если_Второе_Число_Больше_Возвращается_Второе()
        {
            NumberHelper helper = new NumberHelper();
            int result = helper.GetMax(2, 7);
            Assert.AreEqual(7, result);
        }
    }
}
