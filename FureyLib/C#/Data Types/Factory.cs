
// Factory Class Script
// by Kyle Furey

using System;

// Inherit from this interface to implement it.

/// <summary>
/// Provides two functions used for easy instantiation of derived objects.
/// </summary>
public abstract class Factory
{
    // INSTANTATION

    /// <summary>
    /// Instantiates a new object of the given derived type.
    /// </summary>
    public virtual DerivedType Instantiate<DerivedType>() where DerivedType : new()
    {
        return new DerivedType();
    }

    /// <summary>
    /// Instantiates a new derived object of the given template.
    /// </summary>
    public virtual DerivedType Instantiate<DerivedType>(DerivedType template) where DerivedType : ICloneable
    {
        return (DerivedType)template.Clone();
    }
}

/// <summary>
/// Provides two functions used for easy instantiation of derived objects.
/// </summary>
public abstract class Factory<BaseClass>
{
    // INSTANTATION

    /// <summary>
    /// Instantiates a new object of the given derived type.
    /// </summary>
    public virtual DerivedType Instantiate<DerivedType>() where DerivedType : BaseClass, new()
    {
        return new DerivedType();
    }

    /// <summary>
    /// Instantiates a new derived object of the given template.
    /// </summary>
    public virtual DerivedType Instantiate<DerivedType>(DerivedType template) where DerivedType : BaseClass, ICloneable
    {
        return (DerivedType)template.Clone();
    }
}
