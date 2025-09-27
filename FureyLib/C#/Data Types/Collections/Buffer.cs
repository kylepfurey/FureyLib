// .cs
// Generic Stack Buffer Class
// by Kyle Furey

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

/// <summary>
/// A fixed-sized buffer of a certain type and size.
/// </summary>
public sealed class Buffer<T> : IEnumerable, IEnumerable<T>
{
    /// <summary>
    /// An ID used to locate data within a buffer.
    /// </summary>
    public struct ID : IEquatable<ID>
    {
        /// <summary>
        /// The numeric value of this ID.
        /// </summary>
        private uint _number;

        /// <summary>
        /// The numeric value of this ID.
        /// </summary>
        public uint Number => _number;

        /// <summary>
        /// Whether this ID is valid.
        /// </summary>
        public bool Valid => Number != uint.MaxValue;

        /// <summary>
        /// Constructs a new ID with the given number.
        /// </summary>
        public ID(uint number) { _number = number; }

        /// <summary>
        /// Compares this ID with another.
        /// </summary>
        public bool Equals(ID other) => Number == other.Number;

        /// <summary>
        /// Determines whether two object instances are equal.
        /// </summary>
        public override bool Equals(object obj) => obj is ID other && Equals(other);

        /// <summary>
        /// Serves as the default hash function.
        /// </summary>
        public override int GetHashCode() => Number.GetHashCode();

        /// <summary>
        /// Compares this ID with another.
        /// </summary>
        public static bool operator ==(ID left, ID right) => left.Equals(right);

        /// <summary>
        /// Compares this ID with another.
        /// </summary>
        public static bool operator !=(ID left, ID right) => !left.Equals(right);
    }

    /// <summary>
    /// A delegate for modifying all valid data in a buffer.
    /// </summary>
    public delegate bool BufferAction(ref T data);

    /// <summary>
    /// The value of a buffer ID that indicates the buffer is full.
    /// </summary>
    public static ID Error { get; private set; } = new ID(uint.MaxValue);

    /// <summary>
    /// The maximum size of this buffer.
    /// </summary>
    public uint Size => (uint)Data.Length;

    /// <summary>
    /// The underlying array containing the data of this buffer.
    /// </summary>
    public T[] Data { get; private set; } = null;

    /// <summary>
    /// A bitset used to check whether data is being stored in this buffer.
    /// </summary>
    public byte[] Available { get; private set; } = null;

    /// <summary>
    /// The current number of spaces occupied in this buffer.
    /// </summary>
    public uint Count { get; private set; } = 0;

    /// <summary>
    /// The next available ID in this buffer.
    /// </summary>
    public ID NextID { get; private set; } = new ID(0);

    /// <summary>
    /// Indexes into this buffer with the given ID.
    /// </summary>
    public T this[ID id]
    {
        get => Find(id);
        set
        {        
            if (Contains(id))
            {
                Data[id.Number] = value;
            }
            else
            {
                throw new Exception("ERROR: Invalid ID when accessing buffer!");
            }
        }
    }

    /// <summary>
    /// Allocates a new zeroed-out buffer of the given size.
    /// </summary>
    public Buffer(uint size)
    {
        Data = new T[size];
        Available = new byte[(size + 7) / 8];
    }

    /// <summary>
    /// Iterates over this buffer.
    /// </summary>
    public IEnumerator<T> GetEnumerator()
    {
        uint count = Count;
        for (uint i = 0; i < Size && count > 0; ++i)
        {
            if ((Available[i / 8] & 1u << (int)(i % 8)) != 0)
            {
                --count;
                yield return Data[i];
            }
        }
    }

    /// <summary>
    /// Iterates over this buffer.
    /// </summary>
    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    /// <summary>
    /// Inserts new data into this buffer and returns its ID, or Buffer.Error if the buffer is full.
    /// </summary>
    public ID Add(T data)
    {
        if (Count >= Size)
        {
            return Error;
        }
        ID id = NextID;
        NextID = new ID(NextID.Number + 1);
        Data[id.Number] = data;
        Available[id.Number / 8] |= (byte)(1u << (int)(id.Number % 8));
        ++Count;
        while (NextID.Number < Size && (Available[NextID.Number / 8] & 1u << (int)(NextID.Number % 8)) != 0)
        {
            NextID = new ID(NextID.Number + 1);
        }
        return id;
    }

    /// <summary>
    /// Erases the data in this buffer with the given ID and returns whether it was successful.
    /// </summary>
    public bool Remove(ID id)
    {
        if (id.Number >= Size || (Available[id.Number / 8] & 1u << (int)(id.Number % 8)) == 0)
        {
            return false;
        }
        Data[id.Number] = default(T);
        Available[id.Number / 8] &= (byte)~(1u << (int)(id.Number % 8));
        --Count;
        NextID = id.Number < NextID.Number ? id : NextID;
        return true;
    }

    /// <summary>
    /// Returns the data in this buffer with the given ID, or null if no data exists.
    /// </summary>
    public T Find(ID id)
    {
        if (id.Number >= Size || (Available[id.Number / 8] & 1u << (int)(id.Number % 8)) == 0)
        {
            return default(T);
        }
        return Data[id.Number];
    }

    /// <summary>
    /// Returns whether the given ID is valid and outputs a reference to the data in this buffer with the given ID.
    /// </summary>
    public bool TryFind(ID id, ref T data)
    {
        if (id.Number >= Size || (Available[id.Number / 8] & 1u << (int)(id.Number % 8)) == 0)
        {
            return false;
        }
        data = ref Data[id.Number];
        return true;
    }

    /// <summary>
    /// Returns whether this buffer has data associated with the given ID.
    /// </summary>
    public bool Contains(ID id)
    {
        if (id.Number >= Size)
        {
            return false;
        }
        return (Available[id.Number / 8] & 1u << (int)(id.Number % 8)) != 0;
    }

    /// <summary>
    /// Clears this buffer.
    /// </summary>
    public uint Clear()
    {
        uint count = Count;
        Data = new T[Size];
        Available = new byte[(Size + 7) / 8];
        Count = 0;
        NextID = new ID(0);
        return count;
    }

    /// <summary>
    /// Iterates through this buffer with the given function and returns whether the iteration successfully completed.
    /// </summary>
    public bool ForEach(BufferAction action)
    {
        uint count = Count;
        for (int i = 0; i < Size && count > 0; ++i)
        {
            if ((Available[i / 8] & 1u << (i % 8)) != 0)
            {
                --count;
                if (!action(ref Data[i]))
                {
                    return false;
                }
            }
        }
        return true;
    }

    /// <summary>
    /// Returns this buffer as a string.
    /// </summary>
    /// <returns></returns>
    public override string ToString()
    {
        StringBuilder result = new StringBuilder();
        result.Append('[');
        uint count = Count;
        for (int i = 0; i < Size && count > 0; ++i)
        {
            if ((Available[i / 8] & 1u << (i % 8)) != 0)
            {
                --count;
                result.Append(Data[i] != null ? Data[i].ToString() : "null");
                if (count > 0)
                {
                    result.Append(", ");
                }
            }
        }
        result.Append(']');
        return result.ToString();
    }
}
