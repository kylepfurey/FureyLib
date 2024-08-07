
// Template Game Mode Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// A template for a new game mode.
/// </summary>
public class GameMode : GameModeBase
{
    [Header("\nGAME MODE SETTINGS")]

    [Header("Example setting:")]
    [SerializeField] private bool setting = false;

    // New variables here
	
	
    // UNITY FUNCTIONS

    /// <summary>
    /// Configures the game mode.
    /// </summary>
    public override void Awake()
    {
		base.Awake();
		
        // Change the game mode type enum here!
        type = GameModeType.GameMode;
    }

    /// <summary>
    /// Updates the time limit.
    /// </summary>
    public override void Update()
    {
        // Calls the base function
        base.Update();
    }

    /// <summary>
    /// Cleans up the game mode.
    /// </summary>
    private void OnDestroy()
    {

    }


    // GAME FUNCTIONS

    /// <summary>
    /// When the player wins the game.
    /// </summary>
    public override void Win()
    {
        // Calls the base function
        base.Win();
    }

    /// <summary>
    /// When the player loses the game.
    /// </summary>
    public override void Lose()
    {
        // Calls the base function
        base.Lose();
    }

    /// <summary>
    /// Restarts this game mode.
    /// </summary>
    public override void Restart()
    {
        // Calls the base function
        base.Restart();
    }

    /// <summary>
    /// When the player quits the game.
    /// </summary>
    public override void Quit()
    {
        // Calls the base function
        base.Quit();
    }


    // SCORE FUNCTIONS

    /// <summary>
    /// Resets the current score to 0.
    /// </summary>
    public override void ResetScore()
    {
        // Calls the base function
        base.ResetScore();
    }

    /// <summary>
    /// Increases the current score.
    /// </summary>
    public override void IncreaseScore(int deltaScore)
    {
        // Calls the base function
        base.IncreaseScore(deltaScore);
    }

    /// <summary>
    /// Decreases the current score.
    /// </summary>
    public override void DecreaseScore(int deltaScore)
    {
        // Calls the base function
        base.DecreaseLives(deltaScore);
    }


    // LIFE FUNCTIONS

    /// <summary>
    /// Resets the players live count.
    /// </summary>
    public override void ResetLives()
    {
        // Calls the base function
        base.ResetLives();
    }

    /// <summary>
    /// Increases the player's life count.
    /// </summary>
    public override void IncreaseLives(int lives = 1)
    {
        // Calls the base function
        base.IncreaseLives(lives);
    }

    /// <summary>
    /// Decreases the player's lives.
    /// </summary>
    public override void DecreaseLives(int lives = 1)
    {
        // Calls the base function
        base.DecreaseLives(lives);
    }


    // ROUND FUNCTIONS

    /// <summary>
    /// Restarts the round count.
    /// </summary>
    public override void RestartRounds()
    {
        // Calls the base function
        base.RestartRounds();
    }

    /// <summary>
    /// Starts the current round.
    /// </summary>
    public override void StartRound()
    {
        // Calls the base function
        base.StartRound();
    }

    /// <summary>
    /// Ends the current round.
    /// </summary>
    public override void EndRound()
    {
        // Calls the base function
        base.EndRound();
    }

    /// <summary>
    /// Increments the round count.
    /// </summary>
    public override void NextRound()
    {
        // Calls the base function
        base.NextRound();
    }


    // TIME LIMIT FUNCTIONS

    /// <summary>
    /// Starts or restarts the time limit.
    /// </summary>
    public override void StartTimeLimit()
    {
        // Calls the base function
        base.StartTimeLimit();
    }

    /// <summary>
    /// Resets and pauses the time limit without starting it.
    /// </summary>
    public override void ResetTimeLimit()
    {
        // Calls the base function
        base.ResetTimeLimit();
    }

    /// <summary>
    /// Decrements the time limit by the current delta time if the time limit is active.
    /// </summary>
    public override void TimeLimitTick(float scale = 1)
    {
        // Calls the base function
        base.TimeLimitTick(scale);
    }

    /// <summary>
    /// Pauses the time limit.
    /// </summary>
    public override void PauseTimeLimit()
    {
        // Calls the base function
        base.PauseTimeLimit();
    }

    /// <summary>
    /// Resumes the time limit.
    /// </summary>
    public override void ResumeTimeLimit()
    {
        // Calls the base function
        base.ResumeTimeLimit();
    }

    /// <summary>
    /// Increases the time limit by the given number of seconds.
    /// </summary>
    /// <param name="seconds"></param>
    /// <param name="clampLimit"></param>
    public override void IncreaseTimeLimit(float seconds, bool clampLimit = true)
    {
        // Calls the base function
        base.IncreaseTimeLimit(seconds);
    }

    /// <summary>
    /// Decreases the time limit by the given number of seconds.
    /// </summary>
    /// <param name="seconds"></param>
    public override void DecreaseTimeLimit(float seconds)
    {
        // Calls the base function
        base.DecreaseTimeLimit(seconds);
    }
}
