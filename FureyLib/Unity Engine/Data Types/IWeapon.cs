
// IWeapon Interface Script
// by Kyle Furey

using UnityEngine;

// Inherit from this interface to implement it

/// <summary>
/// Contracts functions for a weapon object in a game.
/// </summary>
public interface IWeapon
{
    // SHOOTING

    /// <summary>
    /// When the shoot button is first pressed.
    /// </summary>
    public abstract void OnFirstShot();

    /// <summary>
    /// Each tick while the shoot button is held.
    /// </summary>
    public abstract void OnShoot();

    /// <summary>
    /// When the shoot button is released.
    /// </summary>
    public abstract void OnStopShooting();


    // ADS

    /// <summary>
    /// When the alt fire button is first pressed.
    /// </summary>
    public abstract void OnStartADS();

    /// <summary>
    /// Each tick while the alt fire button is held.
    /// </summary>
    public abstract void OnADS();

    /// <summary>
    /// When the alt fire button is released.
    /// </summary>
    public abstract void OnStopADS();


    // RELOADING

    /// <summary>
    /// When the reload button is first pressed and the player begins reloading.
    /// </summary>
    public abstract void OnReload();

    /// <summary>
    /// When the player cancels reloading through another action.
    /// </summary>
    public abstract void OnCancelReload();


    // SWAPPING

    /// <summary>
    /// When the weapon is swapped in as the player's currently held weapon.
    /// </summary>
    public abstract void OnSwapIn();

    /// <summary>
    /// When the weapon is swapped out to no longer be the player's currently held weapon.
    /// </summary>
    public abstract void OnSwapOut();
}
