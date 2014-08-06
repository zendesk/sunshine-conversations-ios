//
//  SKTSettings.h
//  SupportKit
//
//  Created by Michael Spensieri on 2/7/14.
//  Copyright (c) 2014 Radialpoint. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, SKTSearchResultsFilterMode) {
    SKTSearchResultIsIn,
    SKTSearchResultIsNotIn
};

@interface SKTSettings : NSObject

/**
 *  Initializes a settings object with the given app token.
 *
 *  @param appToken A valid app token retrieved from the SupportKit web portal.
 */
+(instancetype)settingsWithAppToken:(NSString*)appToken;

/**
 *  Sets the filtering policy applied to user search results based on the given filter mode.
 *
 *  SKTSearchResultIsIn : Filter out search results if they belong to any of the passed section ids.
 *  
 *  SKTSearchResultIsNotIn : Filter out search results if they do not belong to any of the passed section ids.
 *
 *  @param filterMode The filter mode to use.
 *  @param categories Array of category ids on which to filter search results. Can be objects of type NSString or NSNumber.
 *  @param sections Array of section ids on which to filter search results. Can be objects of type NSString or NSNumber.
 */
-(void)excludeSearchResultsIf:(SKTSearchResultsFilterMode)filterMode categories:(NSArray*)categories sections:(NSArray*)sections;

/**
 *  The app token corresponding to your application. App tokens are issued on the SupportKit web portal.
 */
@property(copy) NSString* appToken;

/**
 *  The base URL of your Zendesk knowledge base, to be used in constructing the search endpoint. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").
 *  
 *  If the knowledgeBaseURL is not specified, search is disabled.
 *  The default value is nil.
 */
@property(copy) NSString* knowledgeBaseURL;

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
 *  A Boolean property that indicates whether to show a local OS notification that brings your user into the conversation page once tapped.
 *  The local OS notification is only shown if a user searched for help and left the app within 20 seconds, but without reading any KB articles or attempting to start a conversation.
 *
 *  The default value is YES.
 */
@property BOOL enableLocalNotification;

@end
