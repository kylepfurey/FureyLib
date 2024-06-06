
// IDamageable Interface Script
// by Kyle Furey

using UnityEngine;

// Inherit from this interface to implement it

/// <summary>
/// Contracts a function that allows an object to be damaged.
/// </summary>
public interface IDamageable
{
    /// <summary>
    /// When this object is damaged.
    /// </summary>
    /// <param name="damage">The damage this object is receiving.</param>
    /// <param name="attacker">The object that is damaging this object.</param>
    /// <returns>The remaining health of this object after taking damage.</returns>
    public abstract float OnDamage(float damage, GameObject attacker);
}
