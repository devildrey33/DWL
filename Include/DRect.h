#ifndef DRECT_H
	#define DRECT_H
	
	#include "DObjeto.h"

	namespace DWL {

		class DRect : public RECT {
		  public:
							DRect(void)																			{ left = 0; top = 0; right = 0; bottom = 0; };
							DRect(const LONG nLeft, const LONG nTop, const LONG nRight, const LONG nBottom)		{ left = nLeft; top = nTop; right = nRight; bottom = nBottom; };
							DRect(const RECT &nRect)															{ left = nRect.left; top = nRect.top; right = nRect.right; bottom = nRect.bottom; }
			inline DRect   &operator = (const RECT &nRect)														{ left = nRect.left; top = nRect.top; right = nRect.right; bottom = nRect.bottom; }
			inline DRect   &operator = (const DRect &nRect)														{ left = nRect.left; top = nRect.top; right = nRect.right; bottom = nRect.bottom; }
			inline void		Asignar(const LONG nLeft, const LONG nTop, const LONG nRight, const LONG nBottom)	{ left = nLeft; top = nTop; right = nRight; bottom = nBottom; };


		};
	};

#endif