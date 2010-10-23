/*
 *  zlsViewer.h
 *  ZeroLSys-OSX
 *
 *  Created by Micah Pearlman on 10/22/10.
 *  Copyright 2010 Zero Vision. All rights reserved.
 *
 */

#ifndef __ZLS_VIEWER_H__
#define __ZLS_VIEWER_H__

#include <string>
#include <map>

namespace ZeroLSys {
	
	using namespace std;
	
	class StateViewer {
	public:
		typedef void (StateViewer::*SymbolHandler)();
		
		virtual void initialize() = 0;
		virtual void terminate() = 0;
		virtual void execute( const string& state ) = 0;
		virtual void draw() = 0;
		
		void addSymbolHandlerForSymbol( const string& symbol, SymbolHandler handler ) {
			_symbolHandlers[symbol] = handler;
		}
		
		SymbolHandler handlerFromSymbol( const string& symbol ) {
			map< string, SymbolHandler >::iterator it = _symbolHandlers.find( symbol );
			if ( it != _symbolHandlers.end() ) {
				return it->second;
			}
			return 0;
		}
	protected:
		
		map< string, SymbolHandler >	_symbolHandlers;
	};
	
	
}	
#endif // __ZLS_VIEWER_H__
