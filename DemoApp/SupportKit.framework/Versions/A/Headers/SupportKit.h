//
//  SupportKit
//  version : 1.5.3
//
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SKTSettings.h"

#define SUPPORTKIT_VERSION @"1.5.3"

/**
 *  Logs a message to be included with your users' support requests. This function calls through to NSLog (to avoid this, use SKTSilentLog instead).
 */
void SKTLog(NSString* format, ...);

/**
 *  Logs a message to be included with your users' support requests. This function does not call through to NSLog (to forward calls to NSLog, use SKTLog instead).
 */
void SKTSilentLog(NSString* format, ...);

@interface SupportKit : NSObject

/**
 *  Initialize the SupportKit SDK with the provided settings. This should be called only once (in your application:didFinishLaunchingWithOptions:).
 *
 *  The settings object is deep copied, and any modifications to it after this call will have no effect.
 *
 *  @param settings The settings to use.
 */
+(void)initWithSettings:(SKTSettings*)settings;

/**
 *  Presents the SupportKit view controller.
 *
 *  +initWithSettings: must have been called prior to calling show.
 */
+(void)show;

/**
 *  Presents the SupportKit view controller with gesture hint.
 *
 *  +initWithSettings: must have been called prior to calling showWithGestureHint.
 */
+(void)showWithGestureHint;

/**
 *  Notify SupportKit of a significant event in your application (to be included with your users' support requests).
 *
 *  @param event Name of the Event.
 *  @param properties Any properties related to the event.
 */
+(void)track:(NSString*)event properties:(NSDictionary*)properties;

/**
 *  Notify SupportKit of a significant event in your application (to be included with your users' support requests).
 *
 *  @param event Name of the Event.
 */
+(void)track:(NSString*)event;

/**
 *  Presents the SupportKit view controller.
 *
 *  SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https, depending which protocol your Zendesk instance uses (ex: "https://supportkit.zendesk.com"). An error is logged and displayed in the UI otherwise.
 *
 *  The default ticket creation page is constructed from the Zendesk URL as follows: "zendeskURL/anonymous_requests/new". To change this value, use +showInViewController:withZendeskURL:andTicketURL: instead.
 *
 *  Deprecated since v1.1, use +initWithSettings: and +show instead.
 *
 *  @param viewController The view controller that will present SupportKit.
 *  @param zendeskURL Fully qualified URL to your Zendesk instance.
 */
+(void)showInViewController:(UIViewController*)viewController withZendeskURL:(NSString*)zendeskURL __attribute((deprecated("use +initWithSettings: and +show instead")));

/**
 *  Same as +showInViewController:withZendeskURL:, but allows you to specify the URL for the ticket creation page.
 *
 *  SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https, depending which protocol your Zendesk instance uses (ex: "https://supportkit.zendesk.com").  An error is logged and displayed in the UI otherwise.
 *
 *  The ticket URL parameter specifies the location of the ticket creation page. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com/anonymous_requests/new").
 *
 *  Deprecated since v1.1, use +initWithSettings: and +show instead.
 *
 *  @param viewController The view controller that will present SupportKit.
 *  @param zendeskURL Fully qualified URL to your Zendesk instance.
 *  @param ticketURL Fully qualified URL, or nil to disable creating support tickets.
 */
+(void)showInViewController:(UIViewController *)viewController withZendeskURL:(NSString *)zendeskURL andTicketURL:(NSString *)ticketURL __attribute((deprecated("use +initWithSettings: and +show instead")));

/**
*  Set a list of recommendations that the user will see upon launching SupportKit.
*  The array should be a list of NSString's representing the URLs to the recommendations.
*
*  @param urlStrings The array of url strings.
*/
+(void)setDefaultRecommendations:(NSArray*)urlStrings;

/**
*  Sets the top recommendation that will appear at the beginning of the list of recommendations. 
*  This should be used when there is a one-to-one mapping between an event that occurred in the app, and a corresponding article describing that event.
*
*  Calling this method more than once will replace the previous top recommendation.
*  Passing nil will remove the current top recommendation.
*
*  @param urlString The url of the article to be displayed.
*/
+(void)setTopRecommendation:(NSString*)urlString;

/**
 *  Predefined fields that can be used with fillTicketWith:.
 */
extern NSString* const SKTPredefinedFieldEmail;
extern NSString* const SKTPredefinedFieldSubject;
extern NSString* const SKTPredefinedFieldDescription;
extern NSString* const SKTPredefinedFieldUsername;

/**
 *  Automatically fill Zendesk ticket fields.
 *
 *  Supported field types : text, checkbox and dropdown.
 *
 *  Values are passed in an NSDictionary where the keys must be the form field names found in the Zendesk ticket form HTML, and may include the predefined fields SKTPredefinedFieldEmail, SKTPredefinedFieldSubject, SKTPredefinedFieldDescription, and SKTPredefinedFieldUsername.
 *
 *  Example:
 *
 *      [SupportKit fillTicketWith:@{SKTPredefinedFieldSubject:@"Help me!", @"comment[value]":@"I need help with your app!", @"ticket[fields][23905543]":@"yes4"}];
 *
 *  Calling this method multiple times will overwrite existing key-value pairs and add new ones.
 *
 *  @param formData The dictionnary of form field names and their given values.
 */
+(void)fillTicketWith:(NSDictionary*)formData;

@end
