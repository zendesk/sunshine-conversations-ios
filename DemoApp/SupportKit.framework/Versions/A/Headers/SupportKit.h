//
//  SupportKit
//  version : 1.2.0
//
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SKTSettings.h"

#define SUPPORTKIT_VERSION @"1.2.0"

@interface SupportKit : NSObject

/**
 Initialize the SupportKit SDK with the provided settings. This should be called only once (in your application:didFinishLaunchingWithOptions:).

 The settings object is deep copied, and any modifications to it after this call will have no effect.

 @param settings The settings to use.
 */

+(void)initWithSettings:(SKTSettings*)settings;

/**
 Presents the SupportKit view controller.

 +initWithSettings: must have been called prior to calling show.
*/
+(void)show;

/**
 Presents the SupportKit view controller with gesture hint.

 +initWithSettings: must have been called prior to calling showWithGestureHint.
 */
+(void)showWithGestureHint;

/**
 Presents the SupportKit view controller.

 SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https, depending which protocol your Zendesk instance uses (ex: "https://supportkit.zendesk.com"). An error is logged and displayed in the UI otherwise.

 The default ticket creation page is constructed from the Zendesk URL as follows: "zendeskURL/anonymous_requests/new". To change this value, use +showInViewController:withZendeskURL:andTicketURL: instead.

 Deprecated since v1.1, use +initWithSettings: and +show instead.

 @param viewController The view controller that will present SupportKit.
 @param zendeskURL Fully qualified URL to your Zendesk instance.
 */
+(void)showInViewController:(UIViewController*)viewController withZendeskURL:(NSString*)zendeskURL __attribute((deprecated("use +initWithSettings: and +show instead")));

/**
 
 Same as +showInViewController:withZendeskURL:, but allows you to specify the URL for the ticket creation page.

 SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https, depending which protocol your Zendesk instance uses (ex: "https://supportkit.zendesk.com").  An error is logged and displayed in the UI otherwise.

 The ticket URL parameter specifies the location of the ticket creation page. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com/anonymous_requests/new").

 Deprecated since v1.1, use +initWithSettings: and +show instead.

 @param viewController The view controller that will present SupportKit.
 @param zendeskURL Fully qualified URL to your Zendesk instance.
 @param ticketURL Fully qualified URL, or nil to disable creating support tickets.
 */
+(void)showInViewController:(UIViewController *)viewController withZendeskURL:(NSString *)zendeskURL andTicketURL:(NSString *)ticketURL __attribute((deprecated("use +initWithSettings: and +show instead")));

@end
