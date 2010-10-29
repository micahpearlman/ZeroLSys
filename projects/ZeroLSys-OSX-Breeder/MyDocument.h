//
//  MyDocument.h
//  ZeroLSys-OSX-Breeder
//
//  Created by Micah Pearlman on 10/27/10.
//  Copyright 2010 Zero Vision. All rights reserved.
//


#import <Cocoa/Cocoa.h>
#import "OpenVGView.h"
#import "../../src/zlsContext.h"

using namespace ZeroLSys;

@interface MyDocument : NSDocument {

@public	
	IBOutlet OpenVGView*		openVGView;

@private
	LSystemContext*		_lsystemContext;
}


- (IBAction) doIterate:(id)sender;

@end
