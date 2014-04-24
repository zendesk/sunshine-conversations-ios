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
 *  Initializes a settings object with the given knowledge base URL. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").
 *
 *  The default ticket creation page is constructed from the knowledge base URL as follows: "knowledgeBaseURL/anonymous_requests/new". To change this value, use +settingsWithKnowledgeBaseURL:andTicketURL: instead.
 *
 *  @param knowledgeBaseURL Fully qualified URL to your knowledge base.
 */
+(instancetype)settingsWithKnowledgeBaseURL:(NSString*)knowledgeBaseURL;

/**
 *  Initializes a settings object with the given knowledge base URL and ticket URL. Both URLs must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").
 *
 *  @param knowledgeBaseURL Fully qualified URL to your knowledge base.
 *  @param ticketURL Fully qualified URL, or nil to disable creating support tickets.
 */
+(instancetype)settingsWithKnowledgeBaseURL:(NSString*)knowledgeBaseURL andTicketURL:(NSString*)ticketURL;

/**
 *  The base URL of your knowledge base, to be used in constructing the search endpoint. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").
 */
@property(copy) NSString* knowledgeBaseURL;

/**
 *  Specifies the location of the ticket creation page. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com/anonymous_requests/new").
 *
 *  Setting to nil will disable creating tickets.
 */
@property(copy) NSString* ticketURL;

/**
 *  A boolean property that indicates whether to enable the app-wide gesture (two-finger swipe down) to present the SupportKit UI. Use option shift (⌥⇧) drag to perform the gesture on the simulator.
 *
 *  The default value is YES.
 */
@property BOOL enableAppWideGesture;

/**
 *  A boolean property that indicates whether to show a hint on how to perform the app-wide gesture when SupportKit is launched for the first time (without using the gesture).
 *
 *  The default value is YES.
 */
@property BOOL enableGestureHintOnFirstLaunch;

/**
 *  A Boolean property that indicates whether to show a local OS notification that brings your user into the ticket submission page once tapped.
 *  The local OS notification is only shown if a user searched for help and left the app within 20 seconds, but without reading any KB articles or attempting to create a support ticket.
 *
 *  The default value is YES.
 */
@property BOOL enableLocalNotification;

/**
 *  A boolean value specifying whether SupportKit should record touch events and include them with users' support requests.
 *
 *  The default value is YES.
 */
@property BOOL enableTouchEventRecording;

@end
