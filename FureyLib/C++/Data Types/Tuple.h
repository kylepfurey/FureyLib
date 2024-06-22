
// Tuple Data Structures Script
// by Kyle Furey

#pragma once

// Include this heading to use the class
#include "Tuple.h"

// Container for two readonly elements of different types.
template <typename DataType1, typename DataType2>
struct tuple2
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// The total number of elements
	const int size = 2;


	// CONSTRUCTORS

	// Default constructor
	tuple2() { }

	// Element constructor
	tuple2(DataType1 item1, DataType2 item2)
	{
		this->item1 = item1;
		this->item2 = item2;
	}

	// Copy constructor
	tuple2(const tuple2<DataType1, DataType2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
	}


	// OPERATORS

	// Copy assignment operator
	tuple2<DataType1, DataType2>& operator=(const tuple2<DataType1, DataType2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;

		return *this;
	}

	// Equality operator
	bool operator==(tuple2<DataType1, DataType2> other)
	{
		return item1 == other.item1 && item2 == other.item2;
	}

	// Inequality operator
	bool operator!=(tuple2<DataType1, DataType2> other)
	{
		return item1 != other.item1 || item2 != other.item2;
	}
};

// Container for three readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3>
struct tuple3
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// The total number of elements
	const int size = 3;


	// CONSTRUCTORS

	// Default constructor
	tuple3() { }

	// Element constructor
	tuple3(DataType1 item1, DataType2 item2, DataType3 item3)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
	}

	// Copy constructor
	tuple3(const tuple3<DataType1, DataType2, DataType3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
	}


	// OPERATORS

	// Copy assignment operator
	tuple3<DataType1, DataType2, DataType3>& operator=(const tuple3<DataType1, DataType2, DataType3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;

		return *this;
	}

	// Equality operator
	bool operator==(tuple3<DataType1, DataType2, DataType3> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3;
	}

	// Inequality operator
	bool operator!=(tuple3<DataType1, DataType2, DataType3> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3;
	}
};

// Container for four readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4>
struct tuple4
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// The total number of elements
	const int size = 4;


	// CONSTRUCTORS

	// Default constructor
	tuple4() { }

	// Element constructor
	tuple4(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
	}

	// Copy constructor
	tuple4(const tuple4<DataType1, DataType2, DataType3, DataType4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
	}


	// OPERATORS

	// Copy assignment operator
	tuple4<DataType1, DataType2, DataType3, DataType4>& operator=(const tuple4<DataType1, DataType2, DataType3, DataType4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;

		return *this;
	}

	// Equality operator
	bool operator==(tuple4<DataType1, DataType2, DataType3, DataType4> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4;
	}

	// Inequality operator
	bool operator!=(tuple4<DataType1, DataType2, DataType3, DataType4> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4;
	}
};

// Container for five readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5>
struct tuple5
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// The total number of elements
	const int size = 5;


	// CONSTRUCTORS

	// Default constructor
	tuple5() { }

	// Element constructor
	tuple5(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
	}

	// Copy constructor
	tuple5(const tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
	}


	// OPERATORS

	// Copy assignment operator
	tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& operator=(const tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;

		return *this;
	}

	// Equality operator
	bool operator==(tuple5<DataType1, DataType2, DataType3, DataType4, DataType5> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5;
	}

	// Inequality operator
	bool operator!=(tuple5<DataType1, DataType2, DataType3, DataType4, DataType5> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5;
	}
};

// Container for six readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6>
struct tuple6
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// The total number of elements
	const int size = 6;


	// CONSTRUCTORS

	// Default constructor
	tuple6() { }

	// Element constructor
	tuple6(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
	}

	// Copy constructor
	tuple6(const tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
	}


	// OPERATORS

	// Copy assignment operator
	tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& operator=(const tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;

		return *this;
	}

	// Equality operator
	bool operator==(tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6;
	}

	// Inequality operator
	bool operator!=(tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6;
	}
};

// Container for seven readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7>
struct tuple7
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// The total number of elements
	const int size = 7;


	// CONSTRUCTORS

	// Default constructor
	tuple7() { }

	// Element constructor
	tuple7(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
	}

	// Copy constructor
	tuple7(const tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;
	}


	// OPERATORS

	// Copy assignment operator
	tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& operator=(const tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;

		return *this;
	}

	// Equality operator
	bool operator==(tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7;
	}

	// Inequality operator
	bool operator!=(tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7;
	}
};

// Container for eight readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8>
struct tuple8
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// The total number of elements
	const int size = 8;


	// CONSTRUCTORS

	// Default constructor
	tuple8() { }

	// Element constructor
	tuple8(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
	}

	// Copy constructor
	tuple8(const tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& copied)
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


	// OPERATORS

	// Copy assignment operator
	tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& operator=(const tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;
		item8 = copied.item8;

		return *this;
	}

	// Equality operator
	bool operator==(tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8;
	}

	// Inequality operator
	bool operator!=(tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8;
	}
};

// Container for nine readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8, typename DataType9>
struct tuple9
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// Element 9
	const DataType9 item9;

	// The total number of elements
	const int size = 9;


	// CONSTRUCTORS

	// Default constructor
	tuple9() { }

	// Element constructor
	tuple9(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
		this->item9 = item9;
	}

	// Copy constructor
	tuple9(const tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& copied)
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


	// OPERATORS

	// Copy assignment operator
	tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& operator=(const tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& copied)
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

		return *this;
	}

	// Equality operator
	bool operator==(tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9;
	}

	// Inequality operator
	bool operator!=(tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9;
	}
};

// Container for ten readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8, typename DataType9, typename DataType10>
struct tuple10
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// Element 9
	const DataType9 item9;

	// Element 10
	const DataType10 item10;

	// The total number of elements
	const int size = 10;


	// CONSTRUCTORS

	// Default constructor
	tuple10() { }

	// Element constructor
	tuple10(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9, DataType10 item10)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
		this->item9 = item9;
		this->item10 = item10;
	}

	// Copy constructor
	tuple10(const tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& copied)
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


	// OPERATORS

	// Copy assignment operator
	tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& operator=(const tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& copied)
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

		return *this;
	}

	// Equality operator
	bool operator==(tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9 && item10 == other.item10;
	}

	// Inequality operator
	bool operator!=(tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9 || item10 != other.item10;
	}
};

// Container for two readonly elements of different types.
template <typename DataType1, typename DataType2>
struct Tuple2
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// The total number of elements
	const int size = 2;


	// CONSTRUCTORS

	// Default constructor
	Tuple2() { }

	// Element constructor
	Tuple2(DataType1 item1, DataType2 item2)
	{
		this->item1 = item1;
		this->item2 = item2;
	}

	// Copy constructor
	Tuple2(const Tuple2<DataType1, DataType2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple2<DataType1, DataType2>& operator=(const Tuple2<DataType1, DataType2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple2<DataType1, DataType2> other)
	{
		return item1 == other.item1 && item2 == other.item2;
	}

	// Inequality operator
	bool operator!=(Tuple2<DataType1, DataType2> other)
	{
		return item1 != other.item1 || item2 != other.item2;
	}
};

// Container for three readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3>
struct Tuple3
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// The total number of elements
	const int size = 3;


	// CONSTRUCTORS

	// Default constructor
	Tuple3() { }

	// Element constructor
	Tuple3(DataType1 item1, DataType2 item2, DataType3 item3)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
	}

	// Copy constructor
	Tuple3(const Tuple3<DataType1, DataType2, DataType3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple3<DataType1, DataType2, DataType3>& operator=(const Tuple3<DataType1, DataType2, DataType3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple3<DataType1, DataType2, DataType3> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3;
	}

	// Inequality operator
	bool operator!=(Tuple3<DataType1, DataType2, DataType3> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3;
	}
};

// Container for four readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4>
struct Tuple4
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// The total number of elements
	const int size = 4;


	// CONSTRUCTORS

	// Default constructor
	Tuple4() { }

	// Element constructor
	Tuple4(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
	}

	// Copy constructor
	Tuple4(const Tuple4<DataType1, DataType2, DataType3, DataType4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple4<DataType1, DataType2, DataType3, DataType4>& operator=(const Tuple4<DataType1, DataType2, DataType3, DataType4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple4<DataType1, DataType2, DataType3, DataType4> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4;
	}

	// Inequality operator
	bool operator!=(Tuple4<DataType1, DataType2, DataType3, DataType4> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4;
	}
};

// Container for five readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5>
struct Tuple5
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// The total number of elements
	const int size = 5;


	// CONSTRUCTORS

	// Default constructor
	Tuple5() { }

	// Element constructor
	Tuple5(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
	}

	// Copy constructor
	Tuple5(const Tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& operator=(const Tuple5<DataType1, DataType2, DataType3, DataType4, DataType5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple5<DataType1, DataType2, DataType3, DataType4, DataType5> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5;
	}

	// Inequality operator
	bool operator!=(Tuple5<DataType1, DataType2, DataType3, DataType4, DataType5> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5;
	}
};

// Container for six readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6>
struct Tuple6
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// The total number of elements
	const int size = 6;


	// CONSTRUCTORS

	// Default constructor
	Tuple6() { }

	// Element constructor
	Tuple6(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
	}

	// Copy constructor
	Tuple6(const Tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& operator=(const Tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6;
	}

	// Inequality operator
	bool operator!=(Tuple6<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6;
	}
};

// Container for seven readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7>
struct Tuple7
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// The total number of elements
	const int size = 7;


	// CONSTRUCTORS

	// Default constructor
	Tuple7() { }

	// Element constructor
	Tuple7(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
	}

	// Copy constructor
	Tuple7(const Tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;
	}


	// OPERATORS

	// Copy assignment operator
	Tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& operator=(const Tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7;
	}

	// Inequality operator
	bool operator!=(Tuple7<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7;
	}
};

// Container for eight readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8>
struct Tuple8
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// The total number of elements
	const int size = 8;


	// CONSTRUCTORS

	// Default constructor
	Tuple8() { }

	// Element constructor
	Tuple8(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
	}

	// Copy constructor
	Tuple8(const Tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& copied)
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


	// OPERATORS

	// Copy assignment operator
	Tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& operator=(const Tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
		item6 = copied.item6;
		item7 = copied.item7;
		item8 = copied.item8;

		return *this;
	}

	// Equality operator
	bool operator==(Tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8;
	}

	// Inequality operator
	bool operator!=(Tuple8<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8;
	}
};

// Container for nine readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8, typename DataType9>
struct Tuple9
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// Element 9
	const DataType9 item9;

	// The total number of elements
	const int size = 9;


	// CONSTRUCTORS

	// Default constructor
	Tuple9() { }

	// Element constructor
	Tuple9(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
		this->item9 = item9;
	}

	// Copy constructor
	Tuple9(const Tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& copied)
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


	// OPERATORS

	// Copy assignment operator
	Tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& operator=(const Tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9>& copied)
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

		return *this;
	}

	// Equality operator
	bool operator==(Tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9;
	}

	// Inequality operator
	bool operator!=(Tuple9<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9;
	}
};

// Container for ten readonly elements of different types.
template <typename DataType1, typename DataType2, typename DataType3, typename DataType4, typename DataType5, typename DataType6, typename DataType7, typename DataType8, typename DataType9, typename DataType10>
struct Tuple10
{
public:

	// VARIABLES

	// Element 1
	const DataType1 item1;

	// Element 2
	const DataType2 item2;

	// Element 3
	const DataType3 item3;

	// Element 4
	const DataType4 item4;

	// Element 5
	const DataType5 item5;

	// Element 6
	const DataType6 item6;

	// Element 7
	const DataType7 item7;

	// Element 8
	const DataType8 item8;

	// Element 9
	const DataType9 item9;

	// Element 10
	const DataType10 item10;

	// The total number of elements
	const int size = 10;


	// CONSTRUCTORS

	// Default constructor
	Tuple10() { }

	// Element constructor
	Tuple10(DataType1 item1, DataType2 item2, DataType3 item3, DataType4 item4, DataType5 item5, DataType6 item6, DataType7 item7, DataType8 item8, DataType9 item9, DataType10 item10)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
		this->item7 = item7;
		this->item8 = item8;
		this->item9 = item9;
		this->item10 = item10;
	}

	// Copy constructor
	Tuple10(const Tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& copied)
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


	// OPERATORS

	// Copy assignment operator
	Tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& operator=(const Tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10>& copied)
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

		return *this;
	}

	// Equality operator
	bool operator==(Tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9 && item10 == other.item10;
	}

	// Inequality operator
	bool operator!=(Tuple10<DataType1, DataType2, DataType3, DataType4, DataType5, DataType6, DataType7, DataType8, DataType9, DataType10> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9 || item10 != other.item10;
	}
};
