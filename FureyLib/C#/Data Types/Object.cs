
// Object Base Class Script
// by Kyle Furey

// REFERENCE: https://learn.microsoft.com/en-us/dotnet/api/system.object?view=net-8.0

// REQUIREMENT: Json Serializer

using System;
using System.Text.Json; // Serializer

/// <summary>
/// •  Base class for all objects in a program.<br/>
/// •  Inherit from object to share common methods and generic storage across any type.<br/>
/// •  All new types should inherit from this class and at least provide a ToString() implementation.
/// </summary>
public abstract class Object : IDisposable, ICloneable, IEquatable<Object>
{
    // CONSTRUCTOR AND DESTRUCTOR

    /// <summary>
    /// Default constructor.
    /// </summary>
    public Object() { }

    /// <summary>
    /// Destructor.
    /// </summary>
    ~Object() { }


    // DEALLOCATION

    /// <summary>
    /// Prepares this object for deletion by releasing its memory.
    /// </summary>
    public virtual void Dispose() { }


    // TO STRING

    /// <summary>
    /// Returns a string interpretation of the given object.
    /// </summary>
    /// <returns></returns>
    public override string ToString()
    {
        return "";
    }

    /// <summary>
    /// Returns a string interpretation of the given object.
    /// </summary>
    /// <param name="other"></param>
    public static implicit operator string(Object other)
    {
        return other.ToString();
    }


    // HASH CODE

    /// <summary>
    /// Returns a unique hash code representing this object's value.
    /// </summary>
    /// <returns></returns>
    public override int GetHashCode()
    {
        int code = 0;

        string str = ToString();

        for (int i = 0; i < str.Length; i++)
        {
            code += str[i] + char.MaxValue * i;
        }

        return code;
    }


    // TYPE AND CASTING

    /// <summary>
    /// Returns this object's type.
    /// </summary>
    /// <returns></returns>
    public Type GetType()
    {
        return base.GetType();
    }

    /// <summary>
    /// Downcasts this object to the given derived type.
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <returns></returns>
    public DataType Cast<DataType>() where DataType : Object
    {
        return this as DataType;
    }


    // MEMBERWISE CLONE

    /// <summary>
    /// Returns a memberwise clone of this object using Json serialization.
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <returns></returns>
    public DataType MemberwiseClone<DataType>() where DataType : Object
    {
        return JsonSerializer.Deserialize<DataType>(ToJson());
    }

    /// <summary>
    /// Returns a memberwise clone of the given object.
    /// </summary>
    /// <returns></returns>
    public object Clone()
    {
        return MemberwiseClone();
    }


    // NULL CHECK

    /// <summary>
    /// Returns whether this object is considered null.
    /// </summary>
    /// <returns></returns>
    public virtual bool IsNull()
    {
        return this == null;
    }

    /// <summary>
    /// Returns whether the given object is not null.
    /// </summary>
    /// <param name="other"></param>
    public static implicit operator bool(Object other)
    {
        return !other.IsNull();
    }

    /// <summary>
    /// Returns whether this object is considered null.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public static bool operator !(Object other)
    {
        return other.IsNull();
    }


    // EQUALITY BY VALUE

    /// <summary>
    /// Returns whether the given object is equal to this.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public override bool Equals(object other)
    {
        if (other == null)
        {
            return false;
        }

        return this == other as Object;
    }

    /// <summary>
    /// Returns whether the given object is equal to this by value.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public virtual bool Equals(Object other)
    {
        if (other == null)
        {
            return false;
        }

        return ToString() == other.ToString();
    }

    /// <summary>
    /// Returns whether the given objects are equal to each other by value.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    public static bool Equals(Object left, Object right)
    {
        if (left == null)
        {
            if (right == null)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (right == null)
        {
            return false;
        }

        return left.ToString() == right.ToString();
    }

    /// <summary>
    /// Returns whether the given object is equal to this by value.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public static bool operator ==(Object left, Object right)
    {
        return left.Equals(right);
    }

    /// <summary>
    /// Returns whether the given object is not equal to this by value.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public static bool operator !=(Object left, Object right)
    {
        return !left.Equals(right);
    }


    // EQUALITY BY REFERENCE

    /// <summary>
    /// Returns whether the given object shares the same memory address.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    public virtual bool ReferenceEquals(Object other)
    {
        return this == other;
    }

    /// <summary>
    /// Returns whether the given objects share the same memory addresses.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    public static bool ReferenceEquals(Object left, Object right)
    {
        return left == right;
    }


    // INSTANTIATION

    /// <summary>
    /// Instantiates a new object of the given derived type.
    /// </summary>
    /// <typeparam name="DerivedType"></typeparam>
    /// <returns></returns>
    public static DerivedType Instantiate<DerivedType>() where DerivedType : Object, new()
    {
        return new DerivedType();
    }

    /// <summary>
    /// Instantiates a new derived object of the given template.
    /// </summary>
    /// <param name="template"></param>
    /// <typeparam name="DerivedType"></typeparam>
    /// <returns></returns>
    public static DerivedType Instantiate<DerivedType>(DerivedType template) where DerivedType : Object
    {
        return (DerivedType)template.Clone();
    }


    // SERIALIZATION

    /// <summary>
    /// Converts the object's values into a Json formatted string.
    /// </summary>
    /// <returns></returns>
    public virtual string ToJson()
    {
        return JsonSerializer.Serialize(this);
    }

    /// <summary>
    /// Reads the given Json formatted string and assigns the object's values from the string.<br/>
    /// </summary>
    /// <param name="json"></param>
    /// <returns>Whether the Json string was successfully parsed.</returns>
    public virtual bool ReadJson(string json)
    {
        /*
        Object newObject = JsonSerializer.Deserialize<Object>(json);

        if (newObject == null)
        {
            return false;
        }

        return true;
        */

        return false;
    }
}
