//
//  Smooch.h
//  Smooch
//  version : 5.8.2
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SKTConversation.h"
#import "SKTSettings.h"
#import "SKTUser.h"

NS_ASSUME_NONNULL_BEGIN
@protocol UNUserNotificationCenterDelegate;

#define SMOOCH_VERSION @"5.8.2"

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
 *  @abstract User info dictionary key to determine the error code of a failed initialization
 *
 *  @discussion Possible values include "unauthorized", "invalid_auth", "bad_request", "unhandled_error" or an empty string for connectivity errors
 *
 *  @see SKTInitializationDidFailNotification
 *
 */
extern NSString* const SKTErrorCodeIdentifier;

/**
 *  @abstract User info dictionary key to determine the HTTP status code of a failed initialization
 *
 *  @discussion User info dictionary key to determine the HTTP status code of a failed initialization
 *
 *  @see SKTInitializationDidFailNotification
 *
 */
extern NSString* const SKTStatusCodeIdentifier;

/**
 *  @abstract Identifier for a Smooch user notification reply action.
 *
 *  @discussion Used as the identifier for a UIUserNotificationAction on iOS 9, and a UNTextInputNotificationAction on iOS 10 and above.
 */
extern NSString* const SKTUserNotificationReplyActionIdentifier;

/**
 *  @abstract Identifier for a Smooch user notification category.
 *
 *  @discussion Used as the identifier for a UIUserNotificationCategory on iOS 9, and a UNNotificationCategory on iOS 10 and above.
 */
extern NSString* const SKTUserNotificationReplyCategoryIdentifier;

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
 *  @abstract Notification that fires when initialization fails
 *
 *  @discussion This notification is fired each time a call to `POST /v1/init` fails. Methods that will trigger this HTTP request include calls to +initWithSettings:, +login:jwt:, and +logout.
 *
 *  You may use this notification to know if initialization failed due to an invalid app token, invalid JWT, or connectivity errors by inspecting the `userInfo` dictionary included with it.
 *
 *  @see SKTErrorCodeIdentifier
 *  @see SKTStatusCodeIdentifier
 *
 */
extern NSString* const SKTInitializationDidFailNotification;

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
+(nullable SKTSettings*)settings;

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
 *  @abstract Destroys the Smooch SDK
 *
 *  @discussion Smooch is automatically terminated when the application exits. This method does not need to be called manually
 *
 */
+(void)destroy;

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
 *  A view controller created in this way is tied to the current user's conversation at creation time. If the current user changes (i.e. by calling +login:jwt: or +logout), the view controller is invalidated and must be recreated for the new user.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class. Returns nil if +initWithSettings: hasn't been called
 */
+(nullable UIViewController*)newConversationViewController;

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
+(void)setUserFirstName:(nullable NSString*)firstName lastName:(nullable NSString*)lastName;

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
+(nullable SKTConversation*)conversation;

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
+(void)login:(NSString*)userId jwt:(nullable NSString*)jwt;

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

/**
 *  @abstract An object conforming to UNUserNotificationCenterDelegate protocol, used to handle notifications on iOS 10 and above.
 *
 *  @discussion Implements both methods of UNUserNotificationCenterDelegate.
 *
 *  By default this object will automatically be set as the UNUserNotificationCenter delegate at init time. Smooch will maintain a reference to your app's existing delegate (if applicable), and automatically forward any calls for notifications that did not originate from Smooch.
 *
 *  To disable automatic overriding, you must set SKTSettings.enableUserNotificationCenterDelegateOverride to NO before calling +initWithSettings:. If you choose to do so, you must manually forward any relevant calls from your own delegate object. To check the origin of a notification, see the documentation for SKTPushNotificationIdentifier. For example:
 *
 *  -(void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler
 *  {
 *    if(notification.request.content.userInfo[SKTPushNotificationIdentifier] != nil){
 *      [[Smooch userNotificationCenterDelegate] userNotificationCenter:center willPresentNotification:notification withCompletionHandler:completionHandler];
 *      return;
 *    }
 *  }
 *
 *  -(void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)())completionHandler
 *  {
 *    if(response.notification.request.content.userInfo[SKTPushNotificationIdentifier] != nil){
 *      [[Smooch userNotificationCenterDelegate] userNotificationCenter:center didReceiveNotificationResponse:response withCompletionHandler:completionHandler];
 *      return;
 *    }
 *  }
 *
 *  @see SKTSettings
 *
 *  @return An object conforming to UNUserNotificationCenterDelegate protocol, or nil if +initWithSettings: hasn't been called yet.
 */
+(nullable id<UNUserNotificationCenterDelegate>)userNotificationCenterDelegate;

/**
 *  @abstract Handle the user input from a reply type notification action.
 *
 *  @discussion Call this method in your -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler:, passing the action identifier, responseInfo dictionary, and completionHandler callback.
 *
 *  This method will post a message on behalf of the user, with the contents of their inline reply. When the message upload completes (either in success or failure), the completion handler will be called.
 *
 *  If the action identifier does not match SKTUserNotificationReplyActionIdentifier, the completion handler will be called immediately and the notification will be ignored.
 *
 *  This method is called automatically if SKTSettings.enableAppDelegateSwizzling is set to YES.
 *
 *  @see SKTSettings
 */
+(void)handleUserNotificationActionWithIdentifier:(NSString *)identifier withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void (^)(void))completionHandler;

/**
 *  @abstract A set of categories used for handling and displaying Smooch user notification actions.
 *
 *  @discussion On iOS 8, returns an empty set.
 *  On iOS 9, returns a set of UIUserNotificationCategory objects, to be used with `UIUserNotificationSettings` +settingsForTypes:categories:
 *  On iOS 10, returns a set of UNNotificationCategory objects, to be used with `UNUserNotificationCenter` -setNotificationCategories:
 *
 *  Categories are registered automatically if SKTSettings.requestPushPermissionOnFirstMessage is set to YES. If automatic registration is disabled, you must make sure to include the Smooch categories in your calls to the above mentioned methods.
 *
 *  @see SKTSettings
 */
+(NSSet*)userNotificationCategories;

@end
NS_ASSUME_NONNULL_END
