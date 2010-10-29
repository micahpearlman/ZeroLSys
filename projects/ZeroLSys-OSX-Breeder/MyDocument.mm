//
//  MyDocument.m
//  ZeroLSys-OSX-Breeder
//
//  Created by Micah Pearlman on 10/27/10.
//  Copyright 2010 Zero Vision. All rights reserved.
//

#import "MyDocument.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

@implementation MyDocument


- (id)init {
    self = [super init];
    if (self) {
    
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.
		_lsystemContext = 0;
		
		[[NSDocumentController sharedDocumentController] setAutosavingDelay:1.0];
    
    }
    return self;
}

//- (void) makeWindowControllers {
//	NSWindowController* controller = [[NSWindowController alloc] initWithWindowNibName:[self windowNibName]];
//	[self addWindowController:controller];
//	[controller release];
//}
- (NSString *)windowNibName {
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController {
	
    [super windowControllerDidLoadNib:aController];
    
	_lsystemContext->setStateViewer( openVGView.stateViewer );
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError {
    // Insert code here to write your document to data of the specified type. If the given outError != NULL, ensure that you set *outError when returning nil.

    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.

    // For applications targeted for Panther or earlier systems, you should use the deprecated API -dataRepresentationOfType:. In this case you can also choose to override -fileWrapperRepresentationOfType: or -writeToFile:ofType: instead.

    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
	return nil;
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError {
    // Insert code here to read your document from the given data of the specified type.  If the given outError != NULL, ensure that you set *outError when returning NO.

    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead. 
    

	string xmlfile( (char*)[data bytes] );
	
	stringstream ss;
	ss << xmlfile;
	
	_lsystemContext = new LSystemContext();
	_lsystemContext->initialize();
	_lsystemContext->read( ss );
	_lsystemContext->reset();
	
    
    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
    return YES;
}


#pragma mark Actions

- (IBAction) doIterate:(id)sender {
	_lsystemContext->iterate();
	_lsystemContext->stateViewer()->setState( _lsystemContext->state() );
}

- (void) dealloc {
	if ( _lsystemContext ) {
		delete _lsystemContext;
	}
	[super dealloc];
}

@end
