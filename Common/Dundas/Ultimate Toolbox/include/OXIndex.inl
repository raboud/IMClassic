// ==========================================================================
//                     Class Implementation : Index
// ==========================================================================

// Source file : OXIndex.inl

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 19th December 1995
			  
// //////////////////////////////////////////////////////////////////////////
// Definition of static members

#define new DEBUG_NEW

// Data members -------------------------------------------------------------
// protected:
	// LONG m_nIndex1;
	// --- The index of the first (and for now only) dimension

// private:
	
// Member functions ---------------------------------------------------------
// public:
inline Index::Index(LONG nIndex1 /* = 0 */)
	:
	m_nIndex1(nIndex1)
	{
	}

inline Index::Index(const Index& index)
	:
	m_nIndex1(index.m_nIndex1)
	{
	}

inline Index::operator LONG() const
	{
	return m_nIndex1;
	}

inline Index& Index::operator++()
	{
	++m_nIndex1;
	return *this;
	}

inline Index& Index::operator++(int)
	{
	m_nIndex1++;
	return *this;
	}

inline Index& Index::operator--()
	{
	--m_nIndex1;
	return *this;
	}

inline Index& Index::operator--(int)
	{
	m_nIndex1--;
	return *this;
	}

inline Index::~Index()
	{
	}

// protected:
// private:

#undef new 
// ==========================================================================
