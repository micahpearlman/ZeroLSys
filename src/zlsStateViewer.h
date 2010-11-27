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
#include <vector>
#include <deque>

namespace ZLS {
	
	using namespace std;
	
	class StateViewer {
	public:
		
		StateViewer()
		:	_isDirty( false )
		{}
		
		virtual ~StateViewer() {
			_symbolHandlers.clear();
		}
		
		typedef void (StateViewer::*SymbolHandler)();
		
		virtual void initialize() = 0;
		virtual void terminate() = 0;
		//virtual void execute( const string& state ) = 0;
		virtual void draw() = 0;
		
		string state() const {
			return _state;
		}
		void setState( const string& s ); 
		
		
		void addSymbolHandlerForSymbol( const string& symbol, SymbolHandler handler ) {
			_symbolHandlers[symbol] = handler;
		}
		
		SymbolHandler handlerForSymbol( const string& symbol ) {
			map< string, SymbolHandler >::iterator it = _symbolHandlers.find( symbol );
			if ( it != _symbolHandlers.end() ) {
				return it->second;
			}
			return 0;
		}
		
	protected:
		float nextParameter() {
			const float p = _currentParameters.front();
			_currentParameters.pop_front();
			return p;
		}
		
	protected:
		
		map< string, SymbolHandler >	_symbolHandlers;
		string							_state;
		bool							_isDirty;
		deque<float>					_currentParameters;

	};
	
	
}	
#endif // __ZLS_VIEWER_H__
