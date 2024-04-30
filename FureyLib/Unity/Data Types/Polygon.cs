
// Polygon Structures Script
// by Kyle Furey

using UnityEngine;

// Point structure
public struct Point
{
    // The point
    public readonly Vector3 vertice;

    // The direction of the point
    public readonly Vector3 direction;

    // Constructor
    public Point(Vector3 point, Vector3 newDirection)
    {
        vertice = point;

        direction = newDirection.normalized;
    }
}

// Line structure
public struct Line
{
    // The triangle's three points
    public readonly Vector3 verticeA;
    public readonly Vector3 verticeB;

    // The direction of the line
    public readonly Vector3 direction;

    // Constructor
    public Line(Vector3 pointA, Vector3 pointB)
    {
        verticeA = pointA;
        verticeB = pointB;

        direction = (verticeB - verticeA).normalized;
    }

    // Gets a direction from two points
    public static Vector3 GetDirection(Vector3 pointA, Vector3 pointB)
    {
        return (pointB - pointA).normalized;
    }
}

// Triangle structure
public struct Triangle
{
    // The triangle's three points
    public readonly Vector3 verticeA;
    public readonly Vector3 verticeB;
    public readonly Vector3 verticeC;

    // The direction of the triangle
    public readonly Vector3 normal;

    // Constructor
    public Triangle(Vector3 pointA, Vector3 pointB, Vector3 pointC)
    {
        verticeA = pointA;
        verticeB = pointB;
        verticeC = pointC;

        normal = GetNormal(verticeA, verticeB, verticeC);
    }

    // Gets a normal from three points
    public static Vector3 GetNormal(Vector3 pointA, Vector3 pointB, Vector3 pointC)
    {
        Plane plane = new Plane(pointA, pointB, pointC);

        return plane.normal;
    }
}

// Polygon structure
public struct Polygon
{
    // The polygon's four points
    public readonly Vector3 verticeA;
    public readonly Vector3 verticeB;
    public readonly Vector3 verticeC;
    public readonly Vector3 verticeD;

    // The direction of the polygon
    public readonly Vector3 normal;

    // Constructor
    public Polygon(Vector3 pointA, Vector3 pointB, Vector3 pointC, Vector3 pointD)
    {
        verticeA = pointA;
        verticeB = pointB;
        verticeC = pointC;
        verticeD = pointD;

        normal = GetNormal(pointA, pointB, pointC);
    }

    // Gets a normal from three points
    public static Vector3 GetNormal(Vector3 pointA, Vector3 pointB, Vector3 pointC)
    {
        Plane plane = new Plane(pointA, pointB, pointC);

        return plane.normal;
    }
}

// N Polygon structure
public struct Ngon
{
    // The polygon's N number of points
    public readonly Vector3[] vertices;

    // The direction of the polygon
    public readonly Vector3 normal;

    // The polygon's total number of points
    public readonly int totalPoints;

    // Constructor
    public Ngon(params Vector3[] points)
    {
        if (points.Length < 3)
        {
            vertices = new Vector3[points.Length + (3 - points.Length)];

            for (int i = 0; i < points.Length; i++)
            {
                vertices[i] = points[i];
            }

            for (int i = points.Length; i < 3 - points.Length; i++)
            {
                vertices[i] = new Vector3();
            }
        }
        else
        {
            vertices = new Vector3[points.Length];

            for (int i = 0; i < points.Length; i++)
            {
                vertices[i] = points[i];
            }
        }

        totalPoints = vertices.Length;

        normal = GetNormal(vertices[0], vertices[1], vertices[2]);
    }

    // Gets a normal from three points
    public static Vector3 GetNormal(Vector3 pointA, Vector3 pointB, Vector3 pointC)
    {
        Plane plane = new Plane(pointA, pointB, pointC);

        return plane.normal;
    }
}
