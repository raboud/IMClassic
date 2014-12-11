// ==========================================================================
//                     Template Implementation : COXStack
// ==========================================================================

// Source file : OXStack.inl

// Source : R.Mortelmans
// Creation Date : 	   19th December 1995
// Last Modification : 19th December 1995
			  
// //////////////////////////////////////////////////////////////////////////

// Data members -------------------------------------------------------------
// protected:
// private:
	
// Member functions ---------------------------------------------------------
// public:

template <class TYPE, class ARG_TYPE> inline
void COXStack<TYPE, ARG_TYPE>::Push(ARG_TYPE newElement)
    { 
    AddHead(newElement); 
    }

template <class TYPE, class ARG_TYPE> inline
TYPE& COXStack<TYPE, ARG_TYPE>::Peek()
	{ 
	return GetHead(); 
	}

template <class TYPE, class ARG_TYPE> inline
TYPE COXStack<TYPE, ARG_TYPE>::Peek() const
	{ 
	return IsEmpty() ? NULL : GetHead(); 
	}

template <class TYPE, class ARG_TYPE> inline
TYPE COXStack<TYPE, ARG_TYPE>::Pop()
  	{ 
  	return RemoveHead(); 
  	}

// protected:
// private:

// ==========================================================================
