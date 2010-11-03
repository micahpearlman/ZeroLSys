//
//  BreederAppDelegate.mm
//  ZeroLSys-OSX-Breeder
//
//  Created by Micah Pearlman on 10/29/10.
//  Copyright 2010 Zero Vision. All rights reserved.
//

#import "BreederAppDelegate.h"
#include "../../src/zlsParser.h"
#include <string>
#include <iostream>
#include <sstream>

@implementation BreederAppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {    
	NSLog( @"applicationDidFinishLaunching" );
	
	ZeroLSys::Parser parser;
	std::stringstream ss;
	parser.parse( ss );
}

@end
