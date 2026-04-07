using System;

public class Rectangle
{
    
    private Point A;       // Левый нижний угол прямоугольника
    private double a;      // Горизонтальная сторона (ширина)
    private double b;      // Вертикальная сторона (высота)

    // Конструкторы
    public Rectangle()
    {
        A = new Point(0, 0);
        a = 1;
        b = 1;
    }

    public Rectangle(Point point, double width, double height)
    {
        A = point;
        a = width > 0 ? width : 1;
        b = height > 0 ? height : 1;
    }

    public Rectangle(double x, double y, double width, double height)
    {
        A = new Point(x, y);
        a = width > 0 ? width : 1;
        b = height > 0 ? height : 1;
    }

    // Ввод прямоугольника
    public void Input()
    {
        Console.WriteLine("Введите координаты левого нижнего угла:");
        Console.Write("X: ");
        double x = double.Parse(Console.ReadLine());
        Console.Write("Y: ");
        double y = double.Parse(Console.ReadLine());
        A = new Point(x, y);

        Console.Write("Введите ширину прямоугольника (a > 0): ");
        a = double.Parse(Console.ReadLine());
        while (a <= 0)
        {
            Console.Write("Некорректный ввод. Введите ширину (a > 0): ");
            a = double.Parse(Console.ReadLine());
        }

        Console.Write("Введите высоту прямоугольника (b > 0): ");
        b = double.Parse(Console.ReadLine());
        while (b <= 0)
        {
            Console.Write("Некорректный ввод. Введите высоту (b > 0): ");
            b = double.Parse(Console.ReadLine());
        }
    }

    
    public void Output()
    {
        Console.WriteLine($"Прямоугольник с левым нижним углом в точке ({A.X}, {A.Y})");
        Console.WriteLine($"Ширина: {a}, Высота: {b}");
    }

    // Нахождение периметра
    public double GetPerimeter()
    {
        return 2 * (a + b);
    }

    // Нахождение центра описанной окружности
    public Point GetCircumscribedCircleCenter()
    {
        return new Point(A.X + a / 2, A.Y + b / 2);
    }

    // Проверка, является ли прямоугольник квадратом
    public bool IsSquare()
    {
        return Math.Abs(a - b) < double.Epsilon;
    }

    // Нахождение симметричного прямоугольника относительно начала координат
    public Rectangle GetSymmetricRectangle()
    {
        return new Rectangle(-A.X - a, -A.Y - b, a, b);
    }

    // Проверка двух прямоугольников на подобие
    public bool AreSimilar(Rectangle other)
    {
        double ratio1 = this.a / this.b;
        double ratio2 = other.a / other.b;
        return Math.Abs(ratio1 - ratio2) < double.Epsilon;
    }

    // Проверка, имеет ли прямоугольник пересечение со всеми четвертями
    public bool IntersectsAllQuadrants()
    {
        Point topRight = new Point(A.X + a, A.Y + b);
        return A.X < 0 && topRight.X > 0 && A.Y < 0 && topRight.Y > 0;
    }

    // Проверка пересечения прямоугольников
    public bool Intersect(Rectangle other)
    {
        return this.A.X < other.A.X + other.a &&
               this.A.X + this.a > other.A.X &&
               this.A.Y < other.A.Y + other.b &&
               this.A.Y + this.b > other.A.Y;
    }
}

// Вспомогательный класс для работы с точками
public class Point
{
    public double X { get; }
    public double Y { get; }

    public Point(double x, double y)
    {
        X = x;
        Y = y;
    }
}


class Program
{
    static void Main(string[] args)
    {
        Rectangle rect1 = new Rectangle();
        rect1.Input();
        rect1.Output();

        Rectangle rect2 = new Rectangle(new Point(1, 1), 3, 4);
        rect2.Output();
        Console.WriteLine($"Периметр: {rect2.GetPerimeter()}");
        Console.WriteLine($"Центр описанной окружности: ({rect2.GetCircumscribedCircleCenter().X}, {rect2.GetCircumscribedCircleCenter().Y})");
        Console.WriteLine($"Это квадрат? {rect2.IsSquare()}");

        Rectangle rect3 = rect2.GetSymmetricRectangle();
        Console.WriteLine("Симметричный прямоугольник:");
        rect3.Output();

        Console.WriteLine($"rect1 и rect2 подобны? {rect1.AreSimilar(rect2)}");
        Console.WriteLine($"rect1 пересекает все четверти? {rect1.IntersectsAllQuadrants()}");
        Console.WriteLine($"rect1 и rect2 пересекаются? {rect1.Intersect(rect2)}");
    }
}
