using AIBattle.AITeam;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    // Singleton instance
    public static GameManager instance;

    [Header("World Customization Options")]
    [SerializeField]
    int worldSize = 20;
    [SerializeField]
    bool useWorldSeed = false;
    [SerializeField]
    int worldSeed = 1;
    [SerializeField]
    float timeBetweenTurns = 1.0f;
    [SerializeField]
    float timeBetweenPhases = 0.5f;
    [SerializeField]
    float timeBetweenMoves = 0.2f;
    [SerializeField]
    float timeBetweenExplosions = 0.1f;
    [SerializeField]
    bool paused = false;

    [Header("Add Your Competitors Here!")]
    [SerializeField]
    List<BaseAI> combatantScripts;

    // Cardinal Directions
    public enum Direction
    {
        Up,
        Down,
        Left,
        Right,
        Current
    }

    // What kind of objects can exist in a space
    public enum SensorData
    {
        Clear = 1,
        Wall = 2,
        Enemy = 4,
        Bomb = 8,
        Diamond = 16,
        Goal = 32,
        OffGrid = 64
    }

    [Space(20)]

    [Header("UI Connections")]
    [SerializeField]
    List<Text> phaseText;
    [SerializeField]
    Text turnText;

    // Prefabs for generating the map
    [Header("Prefab Data")]
    [SerializeField]
    GameObject floorPrefab;
    [SerializeField]
    GameObject wallPrefab;
    [SerializeField]
    GameObject diamondPrefab;
    [SerializeField]
    GameObject goalPrefab;
    [SerializeField]
    GameObject bombPrefab;
    [SerializeField]
    GameObject explosion;
    [SerializeField]
    GameObject explosionAudio;
    [SerializeField]
    GameObject moveAudio;
    [SerializeField]
    GameObject deathAudio;
    // Prefab for the combatant
    [SerializeField]
    GameObject combatantPrefab;

    // Data about the current combatants in the area
    class CombatantData
    {
        public int playerId;
        public GameObject go;
        public BaseAI aiScript;
        public BaseAI.CombatantAction action;
        public List<Direction> movement;
        public int bombTimer;
        public int health;
        public bool hasDiamond = false;
    }
    Dictionary<int, CombatantData> players = new Dictionary<int, CombatantData>();
    static int lastPlayerId = 0;
    GameObject diamond;

    // Which AI is currently deciding it's action
    int currentPlayerId = -1;

    // Initialize the singleton
    private void Awake()
    {
        if (instance != null)
        {
            Destroy(gameObject);
            return;
        }
        instance = this;
    }

    // Data about a specific tile
    class WorldData
    {
        public SensorData state;
        public GameObject background;
        public Bomb bomb;
        public List<int> players; // Players who are currently at this position
    }
    // Store the state at every grid position
    WorldData[,] world;


    // Generate the map
    private void Start()
    {
        if (useWorldSeed)
            Random.InitState(worldSeed);

        Debug.Log("New Seed: " + Random.seed);

        // Initialize the world data
        world = new WorldData[worldSize, worldSize];

        // Initialize the state of the world
        for (int i = 0; i < worldSize; i++)
        {
            for (int j = 0; j < worldSize; j++)
            {
                // Initialize this world location
                world[i, j] = new WorldData();
                world[i, j].bomb = null;
                world[i, j].players = new List<int>();

                if (Random.Range(0, 100) > 80)
                {
                    world[i, j].background = Instantiate(wallPrefab, new Vector3(i, j), Quaternion.identity);
                    world[i, j].state = SensorData.Wall;
                }
                else
                {
                    world[i, j].background = Instantiate(floorPrefab, new Vector3(i, j), Quaternion.identity);
                    world[i, j].state = SensorData.Clear;
                }
            }
        }


        // Line up the camera
        Camera.main.GetComponent<CameraShake>().SetPosition(new Vector3(worldSize / 2, worldSize / 2, Camera.main.transform.position.z));
        //Camera.main.transform.position = new Vector3(worldSize / 2, worldSize / 2, Camera.main.transform.position.z);
        Camera.main.orthographicSize = worldSize / 2 + 1;

        // Pick a random spawn location
        int x = Random.Range(0, worldSize);
        int y = Random.Range(0, worldSize);

        // Pick a location for the combatants to spawn
        foreach (BaseAI ai in combatantScripts)
        {
            x = Random.Range(0, worldSize);
            y = Random.Range(0, worldSize);

            while (world[x, y].state != SensorData.Clear || world[x, y].players.Count != 0)
            {
                x = Random.Range(0, worldSize);
                y = Random.Range(0, worldSize);
            }

            GameObject newPlayer = Instantiate(combatantPrefab, new Vector3(x, y, -5), Quaternion.identity);

            // Set up the appropriate data about this player
            CombatantData newPlayerData = new CombatantData();
            newPlayerData.playerId = ++lastPlayerId;
            newPlayerData.go = newPlayer;
            newPlayerData.aiScript = Instantiate(ai);
            newPlayerData.movement = new List<Direction>();
            newPlayerData.action = BaseAI.CombatantAction.Pass;
            newPlayerData.bombTimer = 1;
            newPlayerData.health = 3;

            // Keep track of all of the players
            players[newPlayerData.playerId] = newPlayerData;
            world[x, y].players.Add(newPlayerData.playerId);

            // Set the name of the player
            Text name = newPlayer.transform.Find("Canvas/Name").gameObject.GetComponent<Text>();
            name.text = ai.AIName;
        }

        // Pick a location for the diamond
        x = Random.Range(0, worldSize);
        y = Random.Range(0, worldSize);
        while (world[x, y].state != SensorData.Clear || world[x, y].players.Count != 0)
        {
            x = Random.Range(0, worldSize);
            y = Random.Range(0, worldSize);
        }
        diamond = Instantiate(diamondPrefab, new Vector3(x, y, -5), Quaternion.identity);
        world[x, y].state |= SensorData.Diamond;


        // Pick a location for the goal
        x = Random.Range(0, worldSize);
        y = Random.Range(0, worldSize);
        while (world[x, y].state != SensorData.Clear || world[x, y].players.Count != 0)
        {
            x = Random.Range(0, worldSize);
            y = Random.Range(0, worldSize);
        }
        Instantiate(goalPrefab, new Vector3(x, y, -5), Quaternion.identity);
        world[x, y].state |= SensorData.Goal;


        // Start the game!
        StartCoroutine(ResolveTurn());
    }

    private void Update()
    {
        // Debug testing the use sensor function
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            int x = Mathf.RoundToInt(ray.origin.x);
            int y = Mathf.RoundToInt(ray.origin.y);

            Debug.Log(UseSensor(x, y, Direction.Current));
        }

        // Reload scene and exit game
        if (Input.GetKeyDown(KeyCode.Backspace) || Input.GetKeyDown(KeyCode.Delete))
        {
            AIBrain.ResetTeamInformation();

            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
        else if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }
    }

    private void UpdatePhase(string aPhaseName)
    {
        foreach (Text text in phaseText)
        {
            if (text.gameObject.name == aPhaseName)
            {
                text.fontStyle = FontStyle.Bold;
                text.color = Color.red;
            }
            else
            {
                text.fontStyle = FontStyle.Normal;
                text.color = Color.white;
            }
        }
    }

    // Gathers data about the current state of the game
    // Returns what is found and how far away it is
    public SensorData UseSensor(Direction aDirection)
    {
        // Dear students, you are not allowed to call this function directly :)
        int xPos = Mathf.RoundToInt(players[currentPlayerId].go.transform.position.x);
        int yPos = Mathf.RoundToInt(players[currentPlayerId].go.transform.position.y);
        return UseSensor(xPos, yPos, aDirection);
    }
    SensorData UseSensor(int aXPos, int aYPos, Direction aDirection)
    {
        // Dear students, you are not allowed to call this function directly :)

        // Determine the position we are scanning
        if (aDirection == Direction.Up)
        {
            aYPos++;
        }
        else if (aDirection == Direction.Down)
        {
            aYPos--;
        }
        else if (aDirection == Direction.Left)
        {
            aXPos--;
        }
        else if (aDirection == Direction.Right)
        {
            aXPos++;
        }

        // Is this is off the world?
        if (aXPos < 0 || aXPos >= worldSize || aYPos < 0 || aYPos >= worldSize)
        {
            return SensorData.OffGrid;
        }

        // Figure out what is at the location asked for
        SensorData data = world[aXPos, aYPos].state;

        // Are there any players at that position?
        if ((world[aXPos, aYPos].players.Count > 2) || (world[aXPos, aYPos].players.Count >= 1 && !world[aXPos, aYPos].players.Contains(currentPlayerId)))
        {
            data |= SensorData.Enemy;

            // Check if one of the players at this position has the diamond
            for (int i = 0; i < world[aXPos, aYPos].players.Count; i++)
            {
                if (players[world[aXPos, aYPos].players[i]].hasDiamond)
                {
                    data |= SensorData.Diamond;
                }
            }
        }

        // Are there any bombs at that position?
        data |= (world[aXPos, aYPos].bomb == null ? 0 : SensorData.Bomb);

        // Is there a diamond or a goal at that position
        if ((world[aXPos, aYPos].state & SensorData.Diamond) != 0)
        {
            data |= SensorData.Diamond;
        }

        return data;
    }

    // Infinitely resolves turns until the game is over
    IEnumerator ResolveTurn()
    {
        bool gameOver = false;
        int turn = 0;
        while (!gameOver)
        {
            // Increment the turn counter
            turn++;
            turnText.text = turn.ToString();

            // Always have at least a single wait, otherwise the game will be inifinite looping until someone wins
            if (timeBetweenTurns == 0 && timeBetweenExplosions == 0 && timeBetweenMoves == 0 && timeBetweenPhases == 0)
                yield return new WaitForSeconds(0.00001f);

            if (timeBetweenTurns > 0)
                yield return new WaitForSeconds(timeBetweenTurns);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            //Debug.Log("Playing turn " + turn++);
            // 1. Ask all AI for actions
            //Debug.Log("Asking for actions");
            UpdatePhase("PhaseActions");
            foreach (KeyValuePair<int, CombatantData> playerData in players)
            {
                playerData.Value.action = BaseAI.CombatantAction.Pass;
                playerData.Value.movement.Clear();
                playerData.Value.bombTimer = -1;

                if (playerData.Value.go == null)
                {
                    continue;
                }

                try
                {
                    // TODO: Should we check for infinite loops?
                    currentPlayerId = playerData.Value.playerId;
                    playerData.Value.action = playerData.Value.aiScript.GetAction(ref playerData.Value.movement, ref playerData.Value.bombTimer);
                    currentPlayerId = -1;
                }
                catch (System.Exception e)
                {
                    Debug.Log("AI is passing it's turn because " + e.Message);
                    Debug.Log("Callstack: " + e.StackTrace);
                    playerData.Value.action = BaseAI.CombatantAction.Pass;
                }

                // Sanity checks
                if (playerData.Value.action == BaseAI.CombatantAction.DropBomb && playerData.Value.bombTimer <= 0)
                {
                    Debug.Log("AI is passing turn because it dropped a bomb without setting the bomb timer!");
                    playerData.Value.action = BaseAI.CombatantAction.Pass;
                }
                if (playerData.Value.action == BaseAI.CombatantAction.Move && playerData.Value.movement.Count == 0)
                {
                    Debug.Log("AI is passing turn because it moved without specifying which directions!");
                    playerData.Value.action = BaseAI.CombatantAction.Pass;
                }
            }

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // 2. Resolve moves
            // First show all moves using line renderer
            foreach (KeyValuePair<int, CombatantData> playerData in players)
            {
                if (playerData.Value.action == BaseAI.CombatantAction.Move && playerData.Value.movement.Count > 0)
                {
                    if (playerData.Value.go == null)
                    {
                        continue;
                    }
                    LineRenderer lr = playerData.Value.go.GetComponent<LineRenderer>();
                    if (!lr)
                    {
                        continue;
                    }
                    lr.positionCount = playerData.Value.movement.Count + 1;
                    Vector3 position = playerData.Value.go.transform.position + Vector3.back;
                    lr.SetPosition(0, position);
                    for (int i = 0; i < playerData.Value.movement.Count; i++)
                    {
                        if (playerData.Value.movement[i] == Direction.Up)
                        {
                            position += Vector3.up;
                        }
                        else if (playerData.Value.movement[i] == Direction.Down)
                        {
                            position += Vector3.down;
                        }
                        else if (playerData.Value.movement[i] == Direction.Left)
                        {
                            position += Vector3.left;
                        }
                        else if (playerData.Value.movement[i] == Direction.Right)
                        {
                            position += Vector3.right;
                        }
                        lr.SetPosition(i + 1, position);
                    }
                    lr.sortingLayerName = "Bombs";
                    lr.enabled = true;
                }
            }

            // TODO: This should be random for which character gets to move first, this just goes in order right now
            //Debug.Log("Moving");
            UpdatePhase("PhaseMovement");
            bool movementFinished = false;
            while (!movementFinished)
            {
                movementFinished = true;
                foreach (KeyValuePair<int, CombatantData> playerData in players)
                {
                    if (playerData.Value.action == BaseAI.CombatantAction.Move && playerData.Value.movement.Count > 0)
                    {
                        movementFinished = false;
                        MovePlayer(playerData.Key);

                        if (timeBetweenMoves > 0)
                        {
                            Instantiate(moveAudio);
                            yield return new WaitForSeconds(timeBetweenMoves);
                        }
                    }
                    else if (playerData.Value.action == BaseAI.CombatantAction.Move)
                    {
                        // If we were moving, but have finished
                        playerData.Value.action = BaseAI.CombatantAction.Pass;
                    }
                }
            }
            if (timeBetweenPhases > 0)
                yield return new WaitForSeconds(timeBetweenPhases);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // Turn off line renderers
            foreach (KeyValuePair<int, CombatantData> playerData in players)
            {
                if (playerData.Value.go != null)
                {
                    LineRenderer lr = playerData.Value.go.GetComponent<LineRenderer>();
                    if (lr != null) lr.enabled = false;
                }
            }

            // 3. Resolve bomb placement
            //Debug.Log("Placing Bombs");
            UpdatePhase("PhasePlaceBombs");
            foreach (KeyValuePair<int, CombatantData> comData in players)
            {
                if (comData.Value.action == BaseAI.CombatantAction.DropBomb)
                {
                    // Find what location we are at, instantiate a bomb at that location
                    int xPos = Mathf.RoundToInt(comData.Value.go.transform.position.x);
                    int yPos = Mathf.RoundToInt(comData.Value.go.transform.position.y);

                    PlaceBomb(xPos, yPos, comData.Value.bombTimer);

                    comData.Value.action = BaseAI.CombatantAction.Pass;
                    comData.Value.bombTimer = -1;
                }
            }
            if (timeBetweenPhases > 0)
                yield return new WaitForSeconds(timeBetweenPhases);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // 4. Tick down bomb timers
            //Debug.Log("Ticking bombs");
            UpdatePhase("PhaseReduceTimers");
            for (int i = 0; i < world.GetLength(0); i++)
            {
                for (int j = 0; j < world.GetLength(1); j++)
                {
                    if (world[i, j].bomb != null)
                    {
                        world[i, j].bomb.ReduceTime();
                    }
                }
            }
            if (timeBetweenPhases > 0)
                yield return new WaitForSeconds(timeBetweenPhases);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // 5. Explode bombs
            //Debug.Log("Exploding bombs");
            UpdatePhase("PhaseExplode");
            for (int i = 0; i < world.GetLength(0); i++)
            {
                for (int j = 0; j < world.GetLength(1); j++)
                {
                    if (world[i, j].bomb == null)
                    {
                        continue;
                    }

                    if (world[i, j].bomb.ShouldExplode())
                    {
                        ExplodeBomb(i, j);

                        if (timeBetweenExplosions > 0)
                            yield return new WaitForSeconds(timeBetweenExplosions);
                    }
                }
            }
            if (timeBetweenPhases > 0)
                yield return new WaitForSeconds(timeBetweenPhases);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // 6. Check if any players are dead
            //Debug.Log("Cleaning up the dead");
            UpdatePhase("PhaseRemoveDead");
            bool playerDied = false;
            foreach (KeyValuePair<int, CombatantData> comData in players)
            {
                if (comData.Value.health <= 0 && comData.Value.go != null)
                {
                    playerDied = true;
                    DestroyPlayer(comData.Value.playerId);
                }
            }
            if (playerDied)
            {
                Instantiate(deathAudio);
            }

            if (timeBetweenPhases > 0)
                yield return new WaitForSeconds(timeBetweenPhases);

            // Check for pause
            while (paused)
            {
                yield return new WaitForSeconds(0.1f);
            }

            // 7. Check win states
            //Debug.Log("Checking win states");
            UpdatePhase("PhaseCheckWin");
            int playerCount = 0;
            foreach (KeyValuePair<int, CombatantData> comData in players)
            {
                if (comData.Value.health > 0)
                {
                    playerCount += 1;
                }
            }
            if (playerCount == 0)
            {
                Debug.Log("The game is a draw!");
                gameOver = true;
            }
            if (playerCount == 1)
            {
                Debug.Log("The game is over!");
                gameOver = true;
            }

            // Find if a player has the diamond, and is standing on the goal
            foreach (KeyValuePair<int, CombatantData> comData in players)
            {
                if (comData.Value.go != null)
                {
                    int xPos = Mathf.RoundToInt(comData.Value.go.transform.position.x);
                    int yPos = Mathf.RoundToInt(comData.Value.go.transform.position.y);
                    if (comData.Value.hasDiamond && (world[xPos, yPos].state & SensorData.Goal) != 0)
                    {
                        Debug.Log("Someone has captured the diamond!");
                        gameOver = true;
                    }
                }
            }
        }
    }

    // Move the player with the given player index by one position
    void MovePlayer(int aPlayerId)
    {
        // Sanity check
        if (players[aPlayerId].action == BaseAI.CombatantAction.Move && players[aPlayerId].movement.Count == 0)
        {
            players[aPlayerId].action = BaseAI.CombatantAction.Pass;
            return;
        }
        else if (players[aPlayerId].action != BaseAI.CombatantAction.Move)
        {
            Debug.Log("MovePlayer was called on a player who is currently not taking a move action.");
            return;
        }

        int oldXPos = Mathf.RoundToInt(players[aPlayerId].go.transform.position.x);
        int oldYPos = Mathf.RoundToInt(players[aPlayerId].go.transform.position.y);

        // Find the new position of the player
        float newXPosition = players[aPlayerId].go.transform.position.x;
        float newYPosition = players[aPlayerId].go.transform.position.y;
        if (players[aPlayerId].movement[0] == Direction.Up)
        {
            newYPosition += 1.0f;
        }
        if (players[aPlayerId].movement[0] == Direction.Down)
        {
            newYPosition -= 1.0f;
        }
        if (players[aPlayerId].movement[0] == Direction.Right)
        {
            newXPosition += 1.0f;
        }
        if (players[aPlayerId].movement[0] == Direction.Left)
        {
            newXPosition -= 1.0f;
        }

        // Verify the new position is valid (not a wall and not off the map)
        int newX = Mathf.RoundToInt(newXPosition);
        int newY = Mathf.RoundToInt(newYPosition);
        if (newX < 0 || newX >= worldSize || newY < 0 || newY >= worldSize)
        {
            // Movement is off the world
            players[aPlayerId].action = BaseAI.CombatantAction.Pass;
            players[aPlayerId].movement.Clear();
            players[aPlayerId].health--;
            return;
        }

        if (world[newX, newY].state == SensorData.Wall)
        {
            // Movement is into a wall
            players[aPlayerId].action = BaseAI.CombatantAction.Pass;
            players[aPlayerId].movement.Clear();
            players[aPlayerId].health--;
            return;
        }

        // Move the player to the new position
        players[aPlayerId].go.transform.position = new Vector3(newXPosition, newYPosition, 0);
        world[oldXPos, oldYPos].players.Remove(players[aPlayerId].playerId);
        world[newX, newY].players.Add(players[aPlayerId].playerId);

        // Remove the direction of movement from the list
        players[aPlayerId].movement.RemoveAt(0);

        // If the player steps onto the diamond, pick it up
        if ((world[newX, newY].state & SensorData.Diamond) != 0)
        {
            world[newX, newY].state ^= SensorData.Diamond;
            players[aPlayerId].hasDiamond = true;

            // Stop their movement
            players[aPlayerId].movement.Clear();
        }

        // Move the diamond with the player, if it is with them
        if (players[aPlayerId].hasDiamond)
        {
            diamond.transform.position = players[aPlayerId].go.transform.position;
        }

        // TODO: Update the player UI?
        return;
    }

    // Place a bomb at the given location
    void PlaceBomb(int aXPos, int aYPos, int aTime)
    {
        // Check if we can spawn a bomb at this position
        if (world[aXPos, aYPos].state != SensorData.Clear || world[aXPos, aYPos].bomb != null)
        {
            return;
        }

        GameObject bomb = Instantiate(bombPrefab, new Vector3(aXPos, aYPos), Quaternion.identity);
        world[aXPos, aYPos].bomb = bomb.GetComponent<Bomb>();
        world[aXPos, aYPos].bomb.SetTimeRemaining(aTime);

        return;
    }

    // Destroy a player
    void DestroyPlayer(int aPlayerId)
    {
        int xPos = Mathf.RoundToInt(players[aPlayerId].go.transform.position.x);
        int yPos = Mathf.RoundToInt(players[aPlayerId].go.transform.position.y);
        world[xPos, yPos].players.Remove(aPlayerId);

        // Drop the diamond if they had it
        if (players[aPlayerId].hasDiamond)
        {
            players[aPlayerId].hasDiamond = false;
            world[xPos, yPos].state |= SensorData.Diamond;

            // TODO: What do we do if there is someone else on this position with us?
        }

        Destroy(players[aPlayerId].go);
        players[aPlayerId].go = null;
    }

    // Logic for a bomb exploding
    void ExplodeBomb(int aXPos, int aYPos)
    {
        // Deal damage to any adjacent players
        if (aXPos - 1 >= 0)
        {
            foreach (int playerId in world[aXPos - 1, aYPos].players)
            {
                players[playerId].health -= 3;
            }
        }
        if (aXPos + 1 < worldSize)
        {
            foreach (int playerId in world[aXPos + 1, aYPos].players)
            {
                players[playerId].health -= 3;
            }
        }
        if (aYPos - 1 >= 0)
        {
            foreach (int playerId in world[aXPos, aYPos - 1].players)
            {
                players[playerId].health -= 3;
            }
        }
        if (aYPos + 1 < worldSize)
        {
            foreach (int playerId in world[aXPos, aYPos + 1].players)
            {
                players[playerId].health -= 3;
            }
        }
        foreach (int playerId in world[aXPos, aYPos].players)
        {
            players[playerId].health -= 3;
        }

        // Destroy the bomb object
        Destroy(world[aXPos, aYPos].bomb.gameObject);

        // Instantiate some explosions
        Instantiate(explosion, new Vector3(aXPos, aYPos), Quaternion.identity);
        Instantiate(explosion, new Vector3(aXPos, aYPos + 1), Quaternion.identity);
        Instantiate(explosion, new Vector3(aXPos, aYPos - 1), Quaternion.identity);
        Instantiate(explosion, new Vector3(aXPos + 1, aYPos), Quaternion.identity);
        Instantiate(explosion, new Vector3(aXPos - 1, aYPos), Quaternion.identity);
        Instantiate(explosionAudio);

        Camera.main.GetComponent<CameraShake>().AddShake(0.5f, 0.5f);
    }

    // Get the health of the current player
    public int GetHealth()
    {
        if (currentPlayerId > 0 && currentPlayerId < players.Count)
        {
            return players[currentPlayerId].health;
        }
        return -1;
    }

    // Return how many players are in this game
    public int GetTotalPlayerCount()
    {
        return players.Count;
    }

    public void OnDrawGizmos()
    {
        // TODO: You can use this to draw debug information about your AI
        /*
        foreach (KeyValuePair<int, CombatantData> player in players)
        {
            try
            {
                BetterAI ai = (BetterAI)player.Value.aiScript;
                List<BetterAI.WorldData> v = new List<BetterAI.WorldData>();
                ai.DrawData(player.Value.go.transform.position, ai.world, ref v);
            }
            catch
            {

            }
        }
        */
    }
}
