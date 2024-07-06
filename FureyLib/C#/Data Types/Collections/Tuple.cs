
// Tuple Data Structures Script
// by Kyle Furey

/// <summary>
/// Container for two readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 2;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2)
    {
        this.item1 = item1;
        this.item2 = item2;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
    }
}

/// <summary>
/// Container for three readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 3;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
    }
}

/// <summary>
/// Container for four readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 4;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
    }
}

/// <summary>
/// Container for five readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 5;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
    }
}

/// <summary>
/// Container for six readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// Element 6
    /// </summary>
    public readonly DataType6 item6 = default(DataType6);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 6;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
        this.item6 = item6;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
        item6 = copied.item6;
    }
}

/// <summary>
/// Container for seven readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// Element 6
    /// </summary>
    public readonly DataType6 item6 = default(DataType6);

    /// <summary>
    /// Element 7
    /// </summary>
    public readonly DataType7 item7 = default(DataType7);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 7;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
        this.item6 = item6;
        this.item7 = item7;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
        item6 = copied.item6;
        item7 = copied.item7;
    }
}

/// <summary>
/// Container for eight readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// Element 6
    /// </summary>
    public readonly DataType6 item6 = default(DataType6);

    /// <summary>
    /// Element 7
    /// </summary>
    public readonly DataType7 item7 = default(DataType7);

    /// <summary>
    /// Element 8
    /// </summary>
    public readonly DataType8 item8 = default(DataType8);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 8;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
        this.item6 = item6;
        this.item7 = item7;
        this.item8 = item8;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
        item6 = copied.item6;
        item7 = copied.item7;
        item8 = copied.item8;
    }
}

/// <summary>
/// Container for nine readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// Element 6
    /// </summary>
    public readonly DataType6 item6 = default(DataType6);

    /// <summary>
    /// Element 7
    /// </summary>
    public readonly DataType7 item7 = default(DataType7);

    /// <summary>
    /// Element 8
    /// </summary>
    public readonly DataType8 item8 = default(DataType8);

    /// <summary>
    /// Element 9
    /// </summary>
    public readonly DataType9 item9 = default(DataType9);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 9;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
        this.item6 = item6;
        this.item7 = item7;
        this.item8 = item8;
        this.item9 = item9;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
        item6 = copied.item6;
        item7 = copied.item7;
        item8 = copied.item8;
        item9 = copied.item9;
    }
}

/// <summary>
/// Container for ten readonly elements of different types.
/// </summary>
public readonly struct Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>
{
    // VARIABLES

    /// <summary>
    /// Element 1
    /// </summary>
    public readonly DataType1 item1 = default(DataType1);

    /// <summary>
    /// Element 2
    /// </summary>
    public readonly DataType2 item2 = default(DataType2);

    /// <summary>
    /// Element 3
    /// </summary>
    public readonly DataType3 item3 = default(DataType3);

    /// <summary>
    /// Element 4
    /// </summary>
    public readonly DataType4 item4 = default(DataType4);

    /// <summary>
    /// Element 5
    /// </summary>
    public readonly DataType5 item5 = default(DataType5);

    /// <summary>
    /// Element 6
    /// </summary>
    public readonly DataType6 item6 = default(DataType6);

    /// <summary>
    /// Element 7
    /// </summary>
    public readonly DataType7 item7 = default(DataType7);

    /// <summary>
    /// Element 8
    /// </summary>
    public readonly DataType8 item8 = default(DataType8);

    /// <summary>
    /// Element 9
    /// </summary>
    public readonly DataType9 item9 = default(DataType9);

    /// <summary>
    /// Element 10
    /// </summary>
    public readonly DataType10 item10 = default(DataType10);

    /// <summary>
    /// The total number of elements
    /// </summary>
    public readonly int Count = 10;


    // CONSTRUCTORS

    /// <summary>
    /// Default constructor
    /// </summary>
    public Tuple() { }

    /// <summary>
    /// Element constructor
    /// </summary>
    public Tuple(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9, DataType10 item10)
    {
        this.item1 = item1;
        this.item2 = item2;
        this.item3 = item3;
        this.item4 = item4;
        this.item5 = item5;
        this.item6 = item6;
        this.item7 = item7;
        this.item8 = item8;
        this.item9 = item9;
        this.item10 = item10;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="copied"></param>
    public Tuple(Tuple<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10> copied)
    {
        item1 = copied.item1;
        item2 = copied.item2;
        item3 = copied.item3;
        item4 = copied.item4;
        item5 = copied.item5;
        item6 = copied.item6;
        item7 = copied.item7;
        item8 = copied.item8;
        item9 = copied.item9;
        item10 = copied.item10;
    }
}
