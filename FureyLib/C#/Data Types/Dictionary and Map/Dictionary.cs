
// Dictionary Data Type Class
// by Kyle Furey

// REFERENCES: https://cplusplus.com/reference/map/map/, https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2?view=net-8.0

using System.Collections;
using System.Collections.Generic;

// Dictionary Class
public class Dictionary<KeyType, ValueType> : IEnumerable
{
    // KEY VALUE CLASS
    private class KeyValuePair
    {
        // The key of this pair
        public KeyType key = default(KeyType);

        // The value of this pair
        public ValueType value = default(ValueType);
    }


    // DICTIONARY VARIABLES

    // The dictionary's keys and values
    private List<KeyValuePair> keyValues = new List<KeyValuePair>();

    
    // ENUMERATOR FUNCTION

    // Enumerator implementation
    public IEnumerator GetEnumerator()
    {
        return keyValues.GetEnumerator();
    }
}
