
// Tuple Data Structures Script
// by Kyle Furey

#pragma once

// Include this heading to use the structure
#include "tuple.h"

// Container for two readonly elements of different types.
template <typename data_type1, typename data_type2>
struct tuple
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// The total number of elements
	const int size = 2;


	// CONSTRUCTORS

	// Default constructor
	tuple() { }

	// Element constructor
	tuple(data_type1 item1, data_type2 item2)
	{
		this->item1 = item1;
		this->item2 = item2;
	}

	// Copy constructor
	tuple(const tuple<data_type1, data_type2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
	}


	// OPERATORS

	// Copy assignment operator
	tuple<data_type1, data_type2>& operator=(const tuple<data_type1, data_type2>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;

		return *this;
	}

	// Equality operator
	bool operator==(tuple<data_type1, data_type2> other)
	{
		return item1 == other.item1 && item2 == other.item2;
	}

	// Inequality operator
	bool operator!=(tuple<data_type1, data_type2> other)
	{
		return item1 != other.item1 || item2 != other.item2;
	}
};

// Container for three readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3>
struct tuple3
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// The total number of elements
	const int size = 3;


	// CONSTRUCTORS

	// Default constructor
	tuple3() { }

	// Element constructor
	tuple3(data_type1 item1, data_type2 item2, data_type3 item3)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
	}

	// Copy constructor
	tuple3(const tuple3<data_type1, data_type2, data_type3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
	}


	// OPERATORS

	// Copy assignment operator
	tuple3<data_type1, data_type2, data_type3>& operator=(const tuple3<data_type1, data_type2, data_type3>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;

		return *this;
	}

	// Equality operator
	bool operator==(tuple3<data_type1, data_type2, data_type3> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3;
	}

	// Inequality operator
	bool operator!=(tuple3<data_type1, data_type2, data_type3> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3;
	}
};

// Container for four readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4>
struct tuple4
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// The total number of elements
	const int size = 4;


	// CONSTRUCTORS

	// Default constructor
	tuple4() { }

	// Element constructor
	tuple4(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
	}

	// Copy constructor
	tuple4(const tuple4<data_type1, data_type2, data_type3, data_type4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
	}


	// OPERATORS

	// Copy assignment operator
	tuple4<data_type1, data_type2, data_type3, data_type4>& operator=(const tuple4<data_type1, data_type2, data_type3, data_type4>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;

		return *this;
	}

	// Equality operator
	bool operator==(tuple4<data_type1, data_type2, data_type3, data_type4> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4;
	}

	// Inequality operator
	bool operator!=(tuple4<data_type1, data_type2, data_type3, data_type4> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4;
	}
};

// Container for five readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5>
struct tuple5
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// The total number of elements
	const int size = 5;


	// CONSTRUCTORS

	// Default constructor
	tuple5() { }

	// Element constructor
	tuple5(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
	}

	// Copy constructor
	tuple5(const tuple5<data_type1, data_type2, data_type3, data_type4, data_type5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;
	}


	// OPERATORS

	// Copy assignment operator
	tuple5<data_type1, data_type2, data_type3, data_type4, data_type5>& operator=(const tuple5<data_type1, data_type2, data_type3, data_type4, data_type5>& copied)
	{
		item1 = copied.item1;
		item2 = copied.item2;
		item3 = copied.item3;
		item4 = copied.item4;
		item5 = copied.item5;

		return *this;
	}

	// Equality operator
	bool operator==(tuple5<data_type1, data_type2, data_type3, data_type4, data_type5> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5;
	}

	// Inequality operator
	bool operator!=(tuple5<data_type1, data_type2, data_type3, data_type4, data_type5> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5;
	}
};

// Container for six readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5, typename data_type6>
struct tuple6
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// Element 6
	const data_type6 item6;

	// The total number of elements
	const int size = 6;


	// CONSTRUCTORS

	// Default constructor
	tuple6() { }

	// Element constructor
	tuple6(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5, data_type6 item6)
	{
		this->item1 = item1;
		this->item2 = item2;
		this->item3 = item3;
		this->item4 = item4;
		this->item5 = item5;
		this->item6 = item6;
	}

	// Copy constructor
	tuple6(const tuple6<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6>& copied)
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
	tuple6<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6>& operator=(const tuple6<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6>& copied)
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
	bool operator==(tuple6<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6;
	}

	// Inequality operator
	bool operator!=(tuple6<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6;
	}
};

// Container for seven readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5, typename data_type6, typename data_type7>
struct tuple7
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// Element 6
	const data_type6 item6;

	// Element 7
	const data_type7 item7;

	// The total number of elements
	const int size = 7;


	// CONSTRUCTORS

	// Default constructor
	tuple7() { }

	// Element constructor
	tuple7(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5, data_type6 item6, data_type7 item7)
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
	tuple7(const tuple7<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7>& copied)
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
	tuple7<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7>& operator=(const tuple7<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7>& copied)
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
	bool operator==(tuple7<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7;
	}

	// Inequality operator
	bool operator!=(tuple7<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7;
	}
};

// Container for eight readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5, typename data_type6, typename data_type7, typename data_type8>
struct tuple8
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// Element 6
	const data_type6 item6;

	// Element 7
	const data_type7 item7;

	// Element 8
	const data_type8 item8;

	// The total number of elements
	const int size = 8;


	// CONSTRUCTORS

	// Default constructor
	tuple8() { }

	// Element constructor
	tuple8(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5, data_type6 item6, data_type7 item7, data_type8 item8)
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
	tuple8(const tuple8<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8>& copied)
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
	tuple8<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8>& operator=(const tuple8<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8>& copied)
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
	bool operator==(tuple8<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8;
	}

	// Inequality operator
	bool operator!=(tuple8<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8;
	}
};

// Container for nine readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5, typename data_type6, typename data_type7, typename data_type8, typename data_type9>
struct tuple9
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// Element 6
	const data_type6 item6;

	// Element 7
	const data_type7 item7;

	// Element 8
	const data_type8 item8;

	// Element 9
	const data_type9 item9;

	// The total number of elements
	const int size = 9;


	// CONSTRUCTORS

	// Default constructor
	tuple9() { }

	// Element constructor
	tuple9(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5, data_type6 item6, data_type7 item7, data_type8 item8, data_type9 item9)
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
	tuple9(const tuple9<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9>& copied)
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
	tuple9<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9>& operator=(const tuple9<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9>& copied)
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
	bool operator==(tuple9<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9;
	}

	// Inequality operator
	bool operator!=(tuple9<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9;
	}
};

// Container for ten readonly elements of different types.
template <typename data_type1, typename data_type2, typename data_type3, typename data_type4, typename data_type5, typename data_type6, typename data_type7, typename data_type8, typename data_type9, typename data_type10>
struct tuple10
{
public:

	// VARIABLES

	// Element 1
	const data_type1 item1;

	// Element 2
	const data_type2 item2;

	// Element 3
	const data_type3 item3;

	// Element 4
	const data_type4 item4;

	// Element 5
	const data_type5 item5;

	// Element 6
	const data_type6 item6;

	// Element 7
	const data_type7 item7;

	// Element 8
	const data_type8 item8;

	// Element 9
	const data_type9 item9;

	// Element 10
	const data_type10 item10;

	// The total number of elements
	const int size = 10;


	// CONSTRUCTORS

	// Default constructor
	tuple10() { }

	// Element constructor
	tuple10(data_type1 item1, data_type2 item2, data_type3 item3, data_type4 item4, data_type5 item5, data_type6 item6, data_type7 item7, data_type8 item8, data_type9 item9, data_type10 item10)
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
	tuple10(const tuple10<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9, data_type10>& copied)
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
	tuple10<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9, data_type10>& operator=(const tuple10<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9, data_type10>& copied)
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
	bool operator==(tuple10<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9, data_type10> other)
	{
		return item1 == other.item1 && item2 == other.item2 && item3 == other.item3 && item4 == other.item4 && item5 == other.item5 && item6 == other.item6 && item7 == other.item7 && item8 == other.item8 && item9 == other.item9 && item10 == other.item10;
	}

	// Inequality operator
	bool operator!=(tuple10<data_type1, data_type2, data_type3, data_type4, data_type5, data_type6, data_type7, data_type8, data_type9, data_type10> other)
	{
		return item1 != other.item1 || item2 != other.item2 || item3 != other.item3 || item4 != other.item4 || item5 != other.item5 || item6 != other.item6 || item7 != other.item7 || item8 != other.item8 || item9 != other.item9 || item10 != other.item10;
	}
};
