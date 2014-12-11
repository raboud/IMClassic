// ==========================================================================
// 					Macro definition for Smart copy 
// ==========================================================================

// Header file : OXSCopy.h

// Copyright © Dundas Software Ltd. 1997 - 1998, All Rights Reserved
                         
// //////////////////////////////////////////////////////////////////////////
// Declarations:
//	To use the virtual clone and copy commands, two steps must be done
//
//	1) Add a copy constructor and assignment operator to your class
//	2) Add DECLARE_BCOPY to your specification (.h)
//	   Add IMPLEMENT_BCOPY to your implementation (.cpp)

// //////////////////////////////////////////////////////////////////////////

// Use :
//	The following public function will be available:
//		virtual COXBrilliantObj* Clone();
		// --- In  :
		// --- Out : 
		// --- Returns : A copy of this object as a COXBrilliantObj pointer
		// --- Effect : 
//		void Copy(class_name * pSource);
		// --- In  :pSource : A pointer to an object of your COXBrilliantObj derived class
		// --- Out : 
		// --- Returns : 
		// --- Effect : Assigns that object to this object
//		virtual void VirtualCopy(COXBrilliantObj* pSource);
		// --- In  : pSource : A pointer to an object of your COXBrilliantObj derived class
		//					   cast as a COXBrilliantObj pointer 
		//					   Make sure it points to an object that belongs
		//					   to the same class as this function
		// --- Out : 
		// --- Returns : 
		// --- Effect : Assigns that object to this object

//	The use of this last function is not recommended.  It is beter to use Copy()
//	but this is a non-virtual function

// //////////////////////////////////////////////////////////////////////////

// Implementation issues:
// 	Clone() constucts a new object using the copy constructor
//	 This is kind of a virtual constructor
//	Copy() uses the assignment operator to assign the source to *this
//	VirtualCopy() casts the source to the class and then calls Copy()
//	 No check is made whether the cast is valid or not, so be careful !!

// //////////////////////////////////////////////////////////////////////////

//	Inclusion:
//	Always included in COXBrilliantObj

// //////////////////////////////////////////////////////////////////////////

#ifndef __OXBCOPY_H__
#define __OXBCOPY_H__

#define DECLARE_BCOPY(class_name) 								\
		public:													\
			virtual COXBrilliantObj* Clone();					\
			void Copy(class_name * pSource);					\
			virtual void VirtualCopy(COXBrilliantObj* pSource);	\
			friend class COXSPtr<class_name>;

#define IMPLEMENT_BCOPY(class_name, base_class_name) 			\
		COXBrilliantObj* class_name::Clone()					\
			{ return new class_name(*this); }					\
		void class_name::Copy(class_name* pSource)				\
			{ *this = *pSource; }								\
		void class_name::VirtualCopy(COXBrilliantObj* pSource)	\
			{ Copy((class_name*)pSource); }

#endif  // __OXBCOPY_H__

// ==========================================================================
