#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <vector>

namespace cop4530 {

	template <typename T>
		class infix{
			private :
			char target[MAX], stack[MAX] ;
			char *s, *t ;
			int top, l ;
			public :
			infix( ) ;
			void setexpr ( char *str ) ;
			void push ( char c ) ;
			char pop( ) ;
			void convert( ) ;
			int priority ( char c ) ;
			void show( ) ;
		} ;
#include "stack.hpp"

} // end of namespace 4530

#endif