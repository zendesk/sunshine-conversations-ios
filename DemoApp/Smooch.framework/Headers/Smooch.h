//
//  Smooch.h
//  Smooch
//  version : 4.2.2
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SKTConversation.h"
#import "SKTSettings.h"
#import "SKTUser.h"

#define SMOOCH_VERSION @"4.2.2"

FOUNDATION_EXPORT double SmoochVersionNumber;
FOUNDATION_EXPORT const unsigned char SmoochVersionString[];

/**
 *  @abstract User info dictionary key to determine the origin of a push notification.
 *
 *  @discussion Push notifications that originate from Smooch will have a non-nil value for this key.
 *
 *  `BOOL isSmoochNotification = userInfo[SKTPushNotificationIdentifier] != nil`
 */
extern NSString* const SKTPushNotificationIdentifier;

/**
 *  @abstract Notification that fires when initialization completes successfully
 *
 *  @discussion This notification is fired each time a call to `POST /v1/init` completes with a non-error status code. Methods that will trigger this HTTP request include calls to +initWithSettings:, +login:jwt:, and +logout.
 *
 *  You may use this notification to know when initialization is complete, and the SKTUser object is correctly assigned it's `smoochId` property.
 *
 *  @see SKTUser
 */
extern NSString* const SKTInitializationDidCompleteNotification;

/**
 *  @abstract The core class used for interacting with Smooch. Provides methods to initialize, configure, and interact with the library.
 */
@interface Smooch : NSObject

/**
 *  @abstract Initialize the Smooch SDK with the provided settings. 
 *
 *  @discussion This may only be called once (preferably, in application:didFinishLaunchingWithOptions:).
 *
 *  Use +settings to retrieve and modify the given settings object.
 *
 *  @see SKTSettings
 *
 *  @param settings The settings to use.
 */
+(void)initWithSettings:(SKTSettings*)settings;

/**
 *  @abstract Accessor method for the sdk settings.
 *
 *  @discussion Use this object to update settings at run time.
 *
 *  Note: Some settings may only be configured at init time. See the SKTSettings class reference for more information.
 *
 *  @see SKTSettings
 *
 *  @return Settings object passed in +initWithSettings:, or nil if +initWithSettings: hasn't been called yet.
 */
+(SKTSettings*)settings;

/**
 *  @abstract Presents the Smooch conversation screen.
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller.
 *
 *  +initWithSettings: must have been called prior to calling this method.
 */
+(void)show;

/**
 *  @abstract Dismisses the Smooch conversation, if shown.
 *
 *  @discussion Note: If a view controller was created and presented using `newConversationViewController`, calling this method will have no effect.
 *
 *  +initWithSettings: must have been called prior to calling this method.
 */
+(void)close;

/**
 *  @abstract Presents the Smooch conversation screen, using the given view controller as presenting view controller.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings: must have been called prior to calling this method.
 */
+(void)showConversationFromViewController:(UIViewController*)viewController;

/**
 *  @abstract Creates and returns a Smooch conversation view controller.
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class.
 */
+(UIViewController*)newConversationViewController;

/**
 *  @abstract Sets the current user's first and last name to be used as a display name when sending messages.
 *
 *  @discussion This is a shortcut for -setFirstName and -setLastName on `[SKTUser currentUser]`
 *
 *  @see SKTUser
 *
 *  @param firstName The first name of the user
 *  @param lastName The last name of the user
 */
+(void)setUserFirstName:(NSString*)firstName lastName:(NSString*)lastName;

/**
 *  @abstract Tracks an app event, and processes any whispers associated with that event.
 *
 *  @discussion Whispers can be configured in the Smooch admin panel.
 *
 *  @param eventName The name of the event to track. This should match a whisper created on the admin panel for your app.
 */
+(void)track:(NSString*)eventName;

/**
 *  @abstract Accessor method for the current conversation.
 *
 *  @see SKTConversation
 *
 *  @return Current conversation, or nil if +initWithSettings: hasn't been called yet.
 */
+(SKTConversation*)conversation;

/**
 *  @abstract Logs in a new Smooch user.
 *
 *  @discussion You can either use this method to transition from logged out state to logged in, or to switch the currently logged in user to a different one.
 *
 *  User login state is persisted across app launches. You must call +logout to reset to anonymous mode.
 *
 *  +initWithSettings: must have been called prior to calling this method.
 *
 *  You may not call login while the conversation screen is shown. Doing so will result in a no-op.
 *
 *  @param userId The distinct id of the user to login. Must not be nil.
 *  @param jwt Optional jwt used to prove the origin of the login request. May be nil.
 */
+(void)login:(NSString*)userId jwt:(NSString*)jwt;

/**
 *  @abstract Logs out the current user.
 *
 *  @discussion This method will automatically login an anonymous user after logging out the current user.
 *
 *  Calling this method while already in anonymous state has no effect.
 *
 *  You may not call logout while the conversation screen is shown. Doing so will result in a no-op.
 */
+(void)logout;

/**
 *  @abstract Set the push notification token for this device.
 *
 *  @discussion This method is called automatically if SKTSettings.enableAppDelegateSwizzling is set to YES.
 *
 *  @see SKTSettings
 */
+(void)setPushToken:(NSData*)token;

/**
 *  @abstract Handle an incoming push notification.
 *
 *  @discussion Call this method in your -application:didReceiveRemoteNotification: or -application:didReceiveRemoteNotification:fetchCompletionHandler: callback, passing the userInfo dictionary.
 *
 *  If the push notification did not originate from Smooch, this is a no-op.
 *
 *  This method is called automatically if SKTSettings.enableAppDelegateSwizzling is set to YES.
 *
 *  @see SKTSettings
 */
+(void)handlePushNotification:(NSDictionary*)userInfo;

@end
