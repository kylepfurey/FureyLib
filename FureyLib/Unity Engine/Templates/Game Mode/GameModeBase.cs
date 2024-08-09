
// Game Mode Base Class Script
// by Kyle Furey

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Events;

/// <summary>
/// Game mode type enum.
/// </summary>
public enum GameModeType
{
    /// <summary>
    /// No game mode selected.
    /// </summary>
    None = 0,

    /// <summary>
    /// Example game mode.
    /// </summary>
    GameMode = 1
};

/// <summary>
/// Base class for a customizable game mode through generalized settings and virtual functions.
/// </summary>
public abstract class GameModeBase : MonoBehaviour
{
    [Header("Base class for a customizable game mode through generalized settings and virtual functions.")]

    [Header("\nGAME SETTINGS")]

    [Header("Events for winning, losing, and closing the game:")]
    public UnityEvent onWin = null;
    public UnityEvent onLose = null;
    public UnityEvent onRestart = null;
    public UnityEvent onQuit = null;

    [Header("\nSCORE SETTINGS")]

    [Header("The starting and high score of this game mode:")]
    [SerializeField] protected int startingScore = 0;
    [SerializeField] protected int highScore = 500;

    [Header("Whether this game mode has a target score:")]
    [SerializeField] protected bool hasTargetScore = false;
    [SerializeField] protected int targetScore = 1000;

    [Header("Events for score change:")]
    public UnityEvent onScoreChange = null;
    public UnityEvent onScoreIncrease = null;
    public UnityEvent onScoreDecrease = null;
    public UnityEvent onTargetScoreReached = null;
    public UnityEvent onHighScoreUpdated = null;
    public UnityEvent onScoreReset = null;

    [Header("\nLIFE SETTINGS")]

    [Header("Whether this game mode has a lives system:")]
    [SerializeField] protected bool hasLives = false;
    [SerializeField] protected int startingLives = 3;

    [Header("The maximum lives the player can have:")]
    [SerializeField] protected int maxLives = 3;

    [Header("Whether to automatically lose on running out of lives:")]
    [SerializeField] protected bool loseOnDeath = true;

    [Header("Events for the lives system:")]
    public UnityEvent onLivesChange = null;
    public UnityEvent onOneUp = null;
    public UnityEvent onLoseLife = null;
    public UnityEvent onDeath = null;
    public UnityEvent onReachMaxLives = null;
    public UnityEvent onLivesReset = null;

    [Header("\nROUND SETTINGS")]

    [Header("The number of rounds in this game mode:")]
    [SerializeField] protected bool infiniteRounds = false;
    [SerializeField] protected int maxRounds = 3;
    [SerializeField] protected int mostRounds = 5;

    [Header("Events for the game's different rounds:")]
    public UnityEvent onRoundStart = null;
    public UnityEvent onRoundChange = null;
    public UnityEvent onRoundEnd = null;
    public UnityEvent onCompleteMaxRounds = null;
    public UnityEvent onMostRoundsUpdated = null;
    public UnityEvent onRoundsReset = null;

    [Header("\nTIME SETTINGS")]

    [Header("Whether this game mode has a time limit:")]
    [SerializeField] protected bool hasTimeLimit = false;
    [SerializeField] protected float startingTimeLimit = 120;

    [Header("Events for the time limit:")]
    public UnityEvent onStartTimeLimit = null;
    public UnityEvent onTimeLimitTick = null;
    public UnityEvent onPauseTimeLimit = null;
    public UnityEvent onResumeTimeLimit = null;
    public UnityEvent onReachedTimeLimit = null;
    public UnityEvent onTimeLimitIncrease = null;
    public UnityEvent onTimeLimitDecrease = null;
    public UnityEvent onTimeLimitReset = null;


    // PROTECTED VARIABLES

    /// <summary>
    /// This game mode's type.
    /// </summary>
    public GameModeType type { get; protected set; }

    /// <summary>
    /// The remaining number of lives the player has.
    /// </summary>
    protected int currentLives = 0;

    /// <summary>
    /// The current score of this game mode.
    /// </summary>
    protected int currentScore = 0;

    /// <summary>
    /// The current round of this game mode (starting from 1).
    /// </summary>
    protected int currentRound = 1;

    /// <summary>
    /// Whether the time limit is active.
    /// </summary>
    protected bool timeLimitActive = false;

    /// <summary>
    /// The remaining time on the time limit.
    /// </summary>
    protected float timeLimitRemaining = 0;


    // UNITY FUNCTIONS

    /// <summary>
    /// Sets the starting values.
    /// </summary>
    public virtual void Awake()
    {
        currentLives = startingLives;

        currentScore = startingScore;

        timeLimitRemaining = startingTimeLimit;
    }

    /// <summary>
    /// Updates the time limit.
    /// </summary>
    public virtual void Update()
    {
        if (hasTimeLimit)
        {
            TimeLimitTick();
        }
    }


    // GAME FUNCTIONS

    /// <summary>
    /// When the player wins the game.
    /// </summary>
    public virtual void Win()
    {
        onWin.Invoke();
    }

    /// <summary>
    /// When the player loses the game.
    /// </summary>
    public virtual void Lose()
    {
        onLose.Invoke();
    }

    /// <summary>
    /// Restarts this game mode.
    /// </summary>
    public virtual void Restart()
    {
        onRestart.Invoke();

        ResetScore();

        ResetTimeLimit();
    }

    /// <summary>
    /// When the player quits the game.
    /// </summary>
    public virtual void Quit()
    {
        onQuit.Invoke();
    }


    // SCORE FUNCTIONS

    /// <summary>
    /// Resets the current score to 0.
    /// </summary>
    public virtual void ResetScore()
    {
        currentScore = startingScore;

        onScoreReset.Invoke();
    }

    /// <summary>
    /// Increases the current score.
    /// </summary>
    public virtual void IncreaseScore(int deltaScore = 1)
    {
        currentScore += deltaScore;

        onScoreIncrease.Invoke();

        onScoreChange.Invoke();

        if (hasTargetScore && currentScore >= targetScore)
        {
            onTargetScoreReached.Invoke();
        }

        if (currentScore > highScore)
        {
            highScore = currentScore;

            onHighScoreUpdated.Invoke();
        }
    }

    /// <summary>
    /// Decreases the current score.
    /// </summary>
    public virtual void DecreaseScore(int deltaScore = 1)
    {
        currentScore -= deltaScore;

        currentScore = Mathf.Max(currentScore, 0);

        onScoreDecrease.Invoke();

        onScoreChange.Invoke();
    }


    // LIFE FUNCTIONS

    /// <summary>
    /// Resets the player's life count.
    /// </summary>
    public virtual void ResetLives()
    {
        currentLives = startingLives;

        onLivesReset.Invoke();
    }

    /// <summary>
    /// Increases the player's life count.
    /// </summary>
    public virtual void IncreaseLives(int lives = 1)
    {
        currentLives += lives;

        currentLives = Mathf.Min(currentLives, maxLives);

        onOneUp.Invoke();

        onLivesChange.Invoke();

        if (currentLives == maxLives)
        {
            onReachMaxLives.Invoke();
        }
    }

    /// <summary>
    /// Decreases the player's lives.
    /// </summary>
    public virtual void DecreaseLives(int lives = 1)
    {
        currentLives -= lives;

        currentLives = Mathf.Max(currentLives, 0);

        onLoseLife.Invoke();

        onLivesChange.Invoke();

        if (currentLives <= 0)
        {
            onDeath.Invoke();

            if (loseOnDeath)
            {
                Lose();
            }
        }
    }


    // ROUND FUNCTIONS

    /// <summary>
    /// Restarts the round count.
    /// </summary>
    public virtual void RestartRounds()
    {
        currentRound = 1;

        onRoundsReset.Invoke();
    }

    /// <summary>
    /// Starts the current round.
    /// </summary>
    public virtual void StartRound()
    {
        onRoundStart.Invoke();
    }

    /// <summary>
    /// Ends the current round.
    /// </summary>
    public virtual void EndRound()
    {
        onRoundEnd.Invoke();
    }

    /// <summary>
    /// Increments the round count.
    /// </summary>
    public virtual void NextRound()
    {
        if (!infiniteRounds && currentRound == maxRounds)
        {
            onCompleteMaxRounds.Invoke();
        }

        currentRound++;

        onRoundChange.Invoke();

        if (currentRound > mostRounds)
        {
            mostRounds = currentRound;

            onMostRoundsUpdated.Invoke();
        }
    }


    // TIME LIMIT FUNCTIONS

    /// <summary>
    /// Starts or restarts the time limit.
    /// </summary>
    public virtual void StartTimeLimit()
    {
        timeLimitActive = true;

        if (timeLimitRemaining != startingTimeLimit)
        {
            timeLimitRemaining = startingTimeLimit;

            onTimeLimitReset.Invoke();
        }

        onStartTimeLimit.Invoke();
    }

    /// <summary>
    /// Resets and pauses the time limit without starting it.
    /// </summary>
    public virtual void ResetTimeLimit()
    {
        timeLimitActive = false;

        timeLimitRemaining = startingTimeLimit;

        onTimeLimitReset.Invoke();
    }

    /// <summary>
    /// Decrements the time limit by the current delta time if the time limit is active.
    /// </summary>
    public virtual void TimeLimitTick(float scale = 1)
    {
        if (timeLimitActive)
        {
            timeLimitRemaining -= Time.deltaTime * scale;

            onTimeLimitTick.Invoke();

            if (timeLimitRemaining <= 0)
            {
                onReachedTimeLimit.Invoke();

                timeLimitActive = false;
            }
        }
    }

    /// <summary>
    /// Pauses the time limit.
    /// </summary>
    public virtual void PauseTimeLimit()
    {
        timeLimitActive = false;

        onPauseTimeLimit.Invoke();
    }

    /// <summary>
    /// Resumes the time limit.
    /// </summary>
    public virtual void ResumeTimeLimit()
    {
        timeLimitActive = true;

        onResumeTimeLimit.Invoke();
    }

    /// <summary>
    /// Increases the time limit by the given number of seconds.
    /// </summary>
    /// <param name="seconds"></param>
    /// <param name="clampLimit"></param>
    public virtual void IncreaseTimeLimit(float seconds, bool clampLimit = true)
    {
        timeLimitRemaining += seconds;

        if (clampLimit && timeLimitRemaining > startingTimeLimit)
        {
            timeLimitRemaining = startingTimeLimit;
        }

        onTimeLimitIncrease.Invoke();
    }

    /// <summary>
    /// Decreases the time limit by the given number of seconds.
    /// </summary>
    /// <param name="seconds"></param>
    public virtual void DecreaseTimeLimit(float seconds)
    {
        timeLimitRemaining -= seconds;

        onTimeLimitDecrease.Invoke();

        if (timeLimitActive && timeLimitRemaining <= 0)
        {
            onReachedTimeLimit.Invoke();

            timeLimitActive = false;
        }
    }
}
