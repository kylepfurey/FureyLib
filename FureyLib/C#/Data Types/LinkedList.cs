
// Linked List Data Types Class
// by Kyle Furey

// REFERENCES: https://learn.microsoft.com/en-us/dotnet/api/system.collections.generic.linkedlist-1?view=net-8.0

using System.Collections.Generic;

// Linked List Class
public class LinkedList<DataType>
{
    // LINK CLASS
    private class Link
    {
        // The data of this link
        public DataType data = default(DataType);

        // The next linked data
        public Link next = null;
    }



}

// Doubly Linked List Class
public class DoublyLinkedList<DataType>
{
    // LINK CLASS
    private class Link
    {
        // The previous linked data
        public Link previous = null;

        // The data of this link
        public DataType data = default(DataType);

        // The next linked data
        public Link next = null;
    }
}
