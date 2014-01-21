//
//  SupportKit
//  version : 1.0.1
//
//  Copyright (c) 2013 Radialpoint. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define SUPPORTKIT_VERSION @"1.0.1"

@interface SupportKit : NSObject

/**
 Presents the SupportKit view controller.

 SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com"). An error is logged and displayed in the UI otherwise.

 The default ticket creation page is constructed from the Zendesk URL as follows: "<zendeskURL>/anonymous_requests/new". To change this value, use +showInViewController:withZendeskURL:andTicketURL: instead.
 
 @param viewController The view controller that will present SupportKit.
 @param zendeskURL Fully qualified URL to your Zendesk instance.
 */
+(void)showInViewController:(UIViewController*)viewController withZendeskURL:(NSString*)zendeskURL;

/**
 Same as +showInViewController:withZendeskURL:, but allows you to specify the URL for the ticket creation page.
 
 SupportKit will use the given Zendesk URL to perform searches. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com").

 The ticket URL parameter specifies the location of the ticket creation page. The URL must be fully qualified, including http or https (ex: "https://supportkit.zendesk.com/anonymous_requests/new").

 @param viewController The view controller that will present SupportKit.
 @param zendeskURL Fully qualified URL to your Zendesk instance.
 @param ticketURL Fully qualified URL, or nil to disable creating support tickets.
 */
+(void)showInViewController:(UIViewController *)viewController withZendeskURL:(NSString *)zendeskURL andTicketURL:(NSString *)ticketURL;

@end
