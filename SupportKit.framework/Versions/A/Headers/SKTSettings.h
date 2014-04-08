//
//  SKTSettings.h
//  SupportKit
//
//  Created by Michael Spensieri on 2/7/14.
//  Copyright (c) 2014 Radialpoint. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SKTSettings : NSObject

/**
 Initializes a settings object with the given knowledge base URL. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").

 The default ticket creation page is constructed from the knowledge base URL as follows: "knowledgeBaseURL/anonymous_requests/new". To change this value, use +settingsWithKnowledgeBaseURL:andTicketURL: instead.

 @param knowledgeBaseURL Fully qualified URL to your knowledge base.
 */
+(instancetype)settingsWithKnowledgeBaseURL:(NSString*)knowledgeBaseURL;

/**
 Initializes a settings object with the given knowledge base URL and ticket URL. Both URLs must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").

 @param knowledgeBaseURL Fully qualified URL to your knowledge base.
 @param ticketURL Fully qualified URL, or nil to disable creating support tickets.
 */
+(instancetype)settingsWithKnowledgeBaseURL:(NSString*)knowledgeBaseURL andTicketURL:(NSString*)ticketURL;

/**
 The base URL of your knowledge base, to be used in constructing the search endpoint. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").
 */
@property NSString* knowledgeBaseURL;

/**
 Specifies the location of the ticket creation page. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com/anonymous_requests/new").

 Setting to nil will disable creating tickets.
 */
@property NSString* ticketURL;

/**
 A Boolean property that indicates whether to enable the app-wide gesture (two-finger swipe down) to present the SupportKit UI. Use option shift (⌥⇧) drag to perform the gesture on the simulator.

 The default value is YES.
 */
@property BOOL enableAppWideGesture;

/**
 A Boolean property that indicates whether to show a hint on how to perform the app-wide gesture when SupportKit is launched for the first time (without using the gesture).

 The default value is YES.
 */
@property BOOL enableGestureHintOnFirstLaunch;

@end
