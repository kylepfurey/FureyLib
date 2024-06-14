
// Static Select Statement Functions Script
// by Kyle Furey

// Include this heading to use the library
using static Select;

/// Select statements.
public static class Select
{
    /// <summary>
    /// Select from a boolean and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="condition"></param>
    /// <param name="trueData"></param>
    /// <param name="falseData"></param>
    /// <returns></returns>
    public static DataType select<DataType>(bool condition, DataType trueData, DataType falseData)
    {
        return condition ? trueData : falseData;
    }

    /// <summary>
    /// Select from a boolean and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="condition"></param>
    /// <param name="trueData"></param>
    /// <param name="falseData"></param>
    /// <returns></returns>
    public static ref DataType selectref<DataType>(bool condition, ref DataType trueData, ref DataType falseData)
    {
        if (condition)
        {
            return ref trueData;
        }
        else
        {
            return ref falseData;
        }
    }

    /// <summary>
    /// Select from an integer and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="n"></param>
    /// <param name="nData"></param>
    /// <returns></returns>
    public static DataType select<DataType>(int n, params DataType[] nData)
    {
        return nData[n];
    }

    /// <summary>
    /// Select from an integer and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="n"></param>
    /// <param name="nData"></param>
    /// <returns></returns>
    public static ref DataType selectref<DataType>(int n, params DataType[] nData)
    {
        return ref nData[n];
    }

    /// <summary>
    /// Compare two integers and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="comparer"></param>
    /// <param name="compared"></param>
    /// <param name="greaterThanData"></param>
    /// <param name="lessThanData"></param>
    /// <param name="equalToData"></param>
    /// <returns></returns>
    public static DataType GreaterLessEqual<DataType>(int comparer, int compared, DataType greaterThanData, DataType lessThanData, DataType equalToData)
    {
        if (comparer > compared)
        {
            return greaterThanData;
        }
        else if (comparer < compared)
        {
            return lessThanData;
        }
        else
        {
            return equalToData;
        }
    }

    /// <summary>
    /// Compare two integers and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="comparer"></param>
    /// <param name="compared"></param>
    /// <param name="greaterThanData"></param>
    /// <param name="lessThanData"></param>
    /// <param name="equalToData"></param>
    /// <returns></returns>
    public static ref DataType GreaterLessEqualRef<DataType>(int comparer, int compared, ref DataType greaterThanData, ref DataType lessThanData, ref DataType equalToData)
    {
        if (comparer > compared)
        {
            return ref greaterThanData;
        }
        else if (comparer < compared)
        {
            return ref lessThanData;
        }
        else
        {
            return ref equalToData;
        }
    }

    /// <summary>
    /// Compare two floats and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="comparer"></param>
    /// <param name="compared"></param>
    /// <param name="greaterThanData"></param>
    /// <param name="lessThanData"></param>
    /// <param name="equalToData"></param>
    /// <returns></returns>
    public static DataType GreaterLessEqual<DataType>(float comparer, float compared, DataType greaterThanData, DataType lessThanData, DataType equalToData)
    {
        if (comparer > compared)
        {
            return greaterThanData;
        }
        else if (comparer < compared)
        {
            return lessThanData;
        }
        else
        {
            return equalToData;
        }
    }

    /// <summary>
    /// Compare two floats and return the chosen data
    /// </summary>
    /// <typeparam name="DataType"></typeparam>
    /// <param name="comparer"></param>
    /// <param name="compared"></param>
    /// <param name="greaterThanData"></param>
    /// <param name="lessThanData"></param>
    /// <param name="equalToData"></param>
    /// <returns></returns>
    public static ref DataType GreaterLessEqualRef<DataType>(float comparer, float compared, ref DataType greaterThanData, ref DataType lessThanData, ref DataType equalToData)
    {
        if (comparer > compared)
        {
            return ref greaterThanData;
        }
        else if (comparer < compared)
        {
            return ref lessThanData;
        }
        else
        {
            return ref equalToData;
        }
    }
}
