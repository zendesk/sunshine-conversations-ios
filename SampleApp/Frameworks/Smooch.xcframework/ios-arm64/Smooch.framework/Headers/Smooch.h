//
//  Smooch.h
//  Smooch
//
//  version : 12.5.0

#import <Foundation/Foundation.h>
#import "SKTConversation.h"
#import "SKTSettings.h"
#import "SKTUser.h"
#import "SKTParticipant.h"
#import "SKTConversationListDelegate.h"

NS_ASSUME_NONNULL_BEGIN
@protocol UNUserNotificationCenterDelegate;

#define SMOOCH_VERSION @"12.5.0"
#define VENDOR_ID @"smooch"

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
 *  @abstract User info dictionary key for an SKTUser after a successful call to +login:jwt:completionHandler:
 *
 *  @see SKTUser
 *  @see SKTLoginDidCompleteNotification
 *  @see +login:jwt:completionHandler:
 */
extern NSString* const SKTUserIdentifier;

/**
 *  @abstract User info dictionary key for an SKTConversation after a successful call to +startConversationWithCompletionHandler:
 *
 *  @see SKTConversation
 *  @see +startConversationWithCompletionHandler:
 */
extern NSString* const SKTConversationIdentifier;

/**
 *  @abstract User info dictionary key to determine the error code of a failed operation. Possible operations that may include this value are +initWithSettings:completionHandler:, +login:jwt:completionHandler: and +logoutWithCompletionHandler:
 *
 *  @discussion Possible values include, but are not limited to, "unauthorized", "invalid_auth", "bad_request", "unhandled_error", "invalid_app" or an empty string for connectivity errors
 *
 *  @see SKTInitializationDidFailNotification
 *  @see SKTLoginDidFailNotification
 *  @see SKTLogoutDidFailNotification
 *  @see +initWithSettings:completionHandler:
 *  @see +login:jwt:completionHandler:
 *  @see +logoutWithCompletionHandler:
 */
extern NSString* const SKTErrorCodeIdentifier;

/**
 *  @abstract User info dictionary key to determine the error description of a failed operation. Possible operations that include this value are +initWithSettings:completionHandler:, +login:jwt:completionHandler: and +logoutWithCompletionHandler:
 *
 *  @see SKTInitializationDidFailNotification
 *  @see SKTLoginDidFailNotification
 *  @see SKTLogoutDidFailNotification
 *  @see +initWithSettings:completionHandler:
 *  @see +login:jwt:completionHandler:
 *  @see +logoutWithCompletionHandler:
 */
extern NSString* const SKTErrorDescriptionIdentifier;

/**
 *  @abstract Custom error domain identifier
 */
extern NSString* const SKTErrorDomainIdentifier;

/**
 *  @abstract User info dictionary key to determine the HTTP status code of a failed operation. Possible operations that include this value are +initWithSettings:completionHandler:, +login:jwt:completionHandler: and +logoutWithCompletionHandler:
 *
 *  @discussion User info dictionary key to determine the HTTP status code of a failed operation
 *
 *  @see SKTInitializationDidFailNotification
 *  @see SKTLoginDidFailNotification
 *  @see SKTLogoutDidFailNotification
 *  @see +initWithSettings:completionHandler:
 *  @see +login:jwt:completionHandler:
 *  @see +logoutWithCompletionHandler:
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
 *  @discussion This notification is fired each time a call to +initWithSettings:completionHandler: completes with a non-error status code.
 *
 *  @see +initWithSettings:completionHandler:
 */
extern NSString* const SKTInitializationDidCompleteNotification;

/**
 *  @abstract Notification that fires when initialization fails
 *
 *  @discussion This notification is fired each time a call to +initWithSettings:completionHandler: fails.
 *
 *  You may use this notification to know if initialization failed due to an invalid app ID, invalid JWT, or connectivity errors by inspecting the `userInfo` dictionary included with it.
 *
 *  @see SKTErrorCodeIdentifier
 *  @see SKTErrorDescriptionIdentifier
 *  @see SKTStatusCodeIdentifier
 */
extern NSString* const SKTInitializationDidFailNotification;

/**
 *  @abstract Notification that fires when +login:jwt:completionHandler: completes successfully
 *
 *  @discussion This notification is fired each time a call to +login:jwt:completionHandler: completes with a non-error status code.
 *
 *  @see +login:jwt:completionHandler:
 *  @see SKTUserIdentifier
 */
extern NSString* const SKTLoginDidCompleteNotification;

/**
 *  @abstract Notification that fires when +login:jwt:completionHandler: fails
 *
 *  @discussion This notification is fired each time a call to +login:jwt:completionHandler: fails.
 *
 *  You may use this notification to know if a call to +login:jwt:completionHandler: failed due to an invalid JWT, or connectivity errors by inspecting the `userInfo` dictionary included with it.
 *
 *  @see SKTErrorCodeIdentifier
 *  @see SKTErrorDescriptionIdentifier
 *  @see SKTStatusCodeIdentifier
 */
extern NSString* const SKTLoginDidFailNotification;

/**
 *  @abstract Notification that fires when +logoutWithCompletionHandler: completes successfully
 *
 *  @discussion This notification is fired each time a call to +logoutWithCompletionHandler: completes with a non-error status code.
 *
 *  @see +logoutWithCompletionHandler:
 */
extern NSString* const SKTLogoutDidCompleteNotification;

/**
 *  @abstract Notification that fires when a call to +logoutWithCompletionHandler: fails
 *
 *  @discussion This notification is fired when a call to +logoutWithCompletionHandler: fails
 *
 *  @see SKTErrorCodeIdentifier
 *  @see SKTErrorDescriptionIdentifier
 *  @see SKTStatusCodeIdentifier
 */
extern NSString* const SKTLogoutDidFailNotification;

/**
 * @abstract The core class used for interacting with Smooch. Provides methods to initialize, configure, and interact with the library.
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
 *  @param handler An optional block to evaluate the result of the operation
 */
+(void)initWithSettings:(SKTSettings*)settings completionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))handler;

/**
 *  @abstract Accessor method for the sdk settings.
 *
 *  @discussion Use this object to update settings at run time.
 *
 *  Note: Some settings may only be configured at init time. See the SKTSettings class reference for more information.
 *
 *  @see SKTSettings
 *
 *  @return Settings object passed in +initWithSettings:completionHandler:, or nil if +initWithSettings:completionHandler: hasn't been called yet.
 */
+(nullable SKTSettings*)settings;

/**
 *  @abstract Presents the Smooch conversation screen.
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)show;

/**
 *  @abstract Loads the conversation specified by the ID, and presents the Smooch conversation screen
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 *  @param conversationId The ID of the conversation to load
 */
+(void)showConversationWithId:(NSString *)conversationId;

/**
 *  @abstract Presents the Smooch conversation screen with prefilled text in the message input.
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller with prefilled text in the message input.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showWithStartingText:(nullable NSString *)startingText;

/**
 *  @abstract Loads the conversation specified by the ID, and presents the Smooch conversation screen with prefilled text in the message input.
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller with prefilled text in the message input.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 *  @param conversationId The ID of the conversation to load
 *
 *  @param startingText The text to prefill in the message input
 */
+(void)showConversationWithId:(NSString *)conversationId andStartingText:(nullable NSString *)startingText;

/**
 *  @abstract Dismisses the Smooch conversation, if shown.
 *
 *  @discussion Note: If a view controller was created and presented using `newConversationViewController`, calling this method will have no effect.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
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
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationFromViewController:(UIViewController*)viewController;

/**
 *  @abstract Loads the conversation specified by the ID, and presents the Smooch conversation screen, using the given view controller as presenting view controller.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 *  @param conversationId The ID of the conversation to load
 *
 *  @param viewController The view controller to use as the presenting view controller
 */
+(void)showConversationWithId:(NSString *)conversationId fromViewController:(UIViewController*)viewController;

/**
 *  @abstract Presents the Smooch conversation screen, using the given view controller as presenting view controller with prefilled text in the message input.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationFromViewController:(UIViewController*)viewController withStartingText:(nullable NSString *)startingText;

/**
 *  @abstract Loads the conversation specified by the ID, and presents the Smooch conversation screen, using the given view controller as presenting view controller with prefilled text in the message input.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 *  @param conversationId The ID of the conversation to load
 *
 *  @param viewController The view controller to use as the presenting view controller
 *
 *  @param startingText The text to prefill in the message input
 */
+(void)showConversationWithId:(NSString *)conversationId fromViewController:(UIViewController*)viewController andStartingText:(nullable NSString *)startingText;


/**
 *  @abstract Creates and returns a Smooch conversation view controller.
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose.
 *
 *  A view controller created in this way is tied to the current user's conversation at creation time. If the current user changes (i.e. by calling +login:jwt:completionHandler: or +logoutWithCompletionHandler:), the view controller is invalidated and must be recreated for the new user.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class. Returns nil if +initWithSettings:completionHandler: hasn't been called
 */
+(nullable UIViewController*)newConversationViewController;

/**
 *  @abstract Creates and returns a Smooch conversation view controller, loading the conversation specified by the ID
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @param conversationId The ID of the conversation to load
 *
 *  @param handler Completion handler which provides a UIViewController with the conversation loaded by the specified ID
 */
+(void)newConversationViewControllerWithId:(NSString *)conversationId completionHandler:(nullable void(^)(NSError * _Nullable error, UIViewController * _Nullable viewController))handler;


/**
 *  @abstract Creates and returns a Smooch conversation view controller with prefilled text in the message input.
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose. The message input will be prefilled with the given `startingText`
 *
 *  A view controller created in this way is tied to the current user's conversation at creation time. If the current user changes (i.e. by calling +login:jwt:completionHandler: or +logoutWithCompletionHandler:), the view controller is invalidated and must be recreated for the new user.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class. Returns nil if +initWithSettings:completionHandler: hasn't been called
 */
+(nullable UIViewController*)newConversationViewControllerWithStartingText:(nullable NSString *)startingText;

/**
 *  @abstract Creates and returns a Smooch conversation view controller with prefilled text in the message input, loading the conversation specified by the ID
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose. The message input will be prefilled with the given `startingText`
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @param conversationId The ID of the conversation to load
 *
 *  @param startingText The text to prefill in the message input
 *
 *  @param handler Completion handler which provides a UIViewController with the conversation loaded by the specified ID
 */
+(void)newConversationViewControllerWithId:(NSString *)conversationId startingText:(nullable NSString *)startingText completionHandler:(nullable void(^)(NSError * _Nullable error, UIViewController * _Nullable viewController))handler;

/**
 *  @abstract Presents the Smooch conversation list screen.
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationList;

/**
 *  @abstract Presents the Smooch conversation list screen without a create conversation button
 *
 *  @discussion Uses the top-most view controller of the `UIApplicationDelegate` as the presenting view controller.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationListWithoutCreateConversationButton;

/**
 *  @abstract Dismisses the Smooch conversation list, if shown.
 *
 *  @discussion Note: If a view controller was created and presented using `newConversationViewController`, calling this method will have no effect.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)closeConversationList;

/**
 *  @abstract Presents the Smooch conversation list screen, using the given view controller as presenting view controller.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationListFromViewController:(UIViewController*)viewController;

/**
 *  @abstract Presents the Smooch conversation list screen without a create conversation button, using the given view controller as presenting view controller.
 *
 *  @discussion In most cases, it is better to use +show. If you need more fine-grained control over which view controller is used as presenting view controller, use this method instead.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 */
+(void)showConversationListFromViewControllerWithoutCreateConversationButton:(UIViewController *)viewController;


/**
 *  @abstract Creates and returns a Smooch conversation list view controller.
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose.
 *
 *  A view controller created in this way is tied to the current user's conversation at creation time. If the current user changes (i.e. by calling +login:jwt:completionHandler: or +logoutWithCompletionHandler:), the view controller is invalidated and must be recreated for the new user.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class. Returns nil if +initWithSettings:completionHandler: hasn't been called
 */
+(nullable UIViewController *)newConversationListViewController;

/**
 *  @abstract Creates and returns a Smooch conversation list view controller without a create conversation button.
 *
 *  @discussion You may use this view controller to embed the conversation in a navigation controller, to change the modal presentation style, or display it in any way you choose.
 *
 *  A view controller created in this way is tied to the current user's conversation at creation time. If the current user changes (i.e. by calling +login:jwt:completionHandler: or +logoutWithCompletionHandler:), the view controller is invalidated and must be recreated for the new user.
 *
 *  Note: It is the responsibility of the caller to show, hide, and maintain a reference to this view controller. Calling `close` will not dismiss a view controller created in this way.
 *
 *  @return A new instance of the Smooch conversation view controller class. Returns nil if +initWithSettings:completionHandler: hasn't been called
 */
+(nullable UIViewController *)newConversationListViewControllerWithoutCreateConversationButton;

/**
 * @abstract Sets the conversation list delegate
 *
 *  @discussion The conversation list delegate is used to respond to events relating to the conversation list
 *
 *  @see SKTConversationListDelegate
 *
 *  @param delegate Can we an object conforming to SKTConversationListDelegate, or NULL, which would remove any existing delegate
 */
+(void)setConversationListDelegate:(nullable id<SKTConversationListDelegate>)delegate;

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
 *  @abstract Accessor method for the current conversation.
 *
 *  @see SKTConversation
 *
 *  @return Current conversation, or nil if +initWithSettings:completionHandler: hasn't been called yet.
 */
+ (nullable SKTConversation *)conversation;

/**
 * @abstract Get a conversationById. This is an asynchronous call and requires a callback to retrieve the result. The callback may be called more than once.
 *
 * +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 * @see SKTConversation
 * @param conversationId the conversationId
 */
+ (void)conversationById:(NSString *)conversationId completionHandler:(nullable void(^)(NSError * _Nullable error, SKTConversation * _Nullable conversation))handler;

/**
 *  @abstract Logs in a new Smooch user.
 *
 *  @discussion You can either use this method to transition from logged out state to logged in, or to switch the currently logged in user to a different one.
 *
 *  User login state is persisted across app launches. You must call +logoutWithCompletionHandler: to reset to anonymous mode.
 *
 *  +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 *  You may not call login while the conversation screen is shown. Doing so will result in a no-op.
 *
 *  @param externalId The distinct id of the user to login. Must not be nil.
 *  @param jwt jwt used to prove the origin of the login request. Must not be nil.
 */
+(void)login:(NSString*)externalId jwt:(NSString*)jwt completionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))handler;

/**
 *  @abstract Logs out the current user.
 *
 *  @discussion Calling this method while already in anonymous state has no effect.
 *
 *  You may not call logout while the conversation screen is shown. Doing so will result in a no-op.
 */
+(void)logoutWithCompletionHandler:(nullable void(^)( NSError * _Nullable error, NSDictionary * _Nullable userInfo))completionHandler;

/**
 *  @abstract Force-start a conversation for the current user
 *
 *  @discussion Creates a user and conversation on the server, allowing the business to reach out proactively to the user via the public API.
 *
 *  Creating a conversation via this method will count as a monthly active user (MAU) whether messages are exchanged or not, which may incur cost based on your plan. It is strongly recommended to only call this method in the case where a message is likely to be sent.
 *
 *  This method is called automatically when starting a conversation via the -sendMessage: or -sendImage:withProgress:completion: methods, or when a user sends a message via the conversation view controller.
 */
+(void)startConversationWithCompletionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))completionHandler __attribute__((deprecated("Use + createConversationWithName:description:iconUrl:metadata:completionHandler instead.")));

/**
 * @abstract Create a conversation for the current user, optionally sending a message of type text as part of the conversation creation
 *
 * @discussion Creates a user and conversation on the server, allowing the business to reach out proactively to the user via the public API.
 *
 * Creating a conversation via this method will count as an active user conversation (AUC) whether messages are exchanged or not, which may incur cost based on your plan. It is strongly recommended to only call this method in the case where a message is likely to be sent.
 *
 * This method is called automatically when starting a conversation via the -sendMessage: or -sendImage:withProgress:completion: methods, or when a user sends a message via the conversation view controller.
 *
 * Note: Only a single message of type text can be sent as part of conversation creation. Multiple messages, or other types (e.g files, attachments) will cause this method to return an error.
 *
 * @param displayName A user-friendly name to label the conversation in the list (max length 100 characters)
 * @param description A string describing the purpose of the conversation (max length 100 characters)
 * @param iconUrl An iconUrl to display in the conversation list
 * @param avatarUrl An avatarUrl that is associated with the current user
 * @param metadata A flat JSON Object that can only contain the following value types: string, number, boolean and null
 * @param message An array containing a single SKTMessage type, to be sent as part of conversation creation. Only a message of type text can be sent as part of conversation creation. Multiple messages, or other types (e.g files, attachments) will cause this method to return an error.
 * @param completionHandler An optional block to evaluate the result of the operation
 */

+(void)createConversationWithName:(nullable NSString *)displayName description:(nullable NSString *)description iconUrl:(nullable NSString *)iconUrl avatarUrl:(nullable NSString *)avatarUrl metadata:(nullable NSDictionary *)metadata message:(nullable NSArray<SKTMessage *> *)message completionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))completionHandler;

/**
 * @abstract Updates the specified conversation for the current user.
 *
 * +initWithSettings:completionHandler: must have been called prior to calling this method.
 *
 * If the displayName, description, iconUrl, and metadata parameters are all nil, this is a no-op.
 *
 * @see SKTConversation
 * @param conversationId the conversationId
 * @param displayName A user-friendly name to label the conversation (max length 100 characters)
 * @param description A string describing the purpose of the conversation (max length 100 characters)
 * @param iconUrl An iconUrl to display in the conversation list
 * @param metadata A flat JSON Object that can only contain the following value types: string, number, boolean and null
 * @param completionHandler An optional block to evaluate the result of the operation
 */
+(void)updateConversationById:(NSString *)conversationId withName:(nullable NSString *)displayName description:(nullable NSString *)description iconUrl:(nullable NSString *)iconUrl metadata:(nullable NSDictionary *)metadata completionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))completionHandler;

/**
 *  @abstract Toggles whether the input bar is displayed on the conversation view.
 *
 *  @discussion For some use cases, it can be useful to remove the ability for the user to craft their own messages. For example, if your conversation flow relies solely on postback buttons or quick replies, you may not want to allow the user to send anything other than the presented options.
 *
 *  Passing NO to this method will hide the input bar entirely, including the media button and the text area, thus preventing the user from sending messages themselves.
 *
 *  This method may be called at any time, even when the conversation view is currently displayed.
 *
 *  State is persisted across view controller launches.
 */
+(void)setConversationInputDisplayed:(BOOL)displayed;

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
 *  To disable automatic overriding, you must set SKTSettings.enableUserNotificationCenterDelegateOverride to NO before calling +initWithSettings:completionHandler:. If you choose to do so, you must manually forward any relevant calls from your own delegate object. To check the origin of a notification, see the documentation for SKTPushNotificationIdentifier. For example:
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
 *  @return An object conforming to UNUserNotificationCenterDelegate protocol, or nil if +initWithSettings:completionHandler: hasn't been called yet.
 */
+(nullable id<UNUserNotificationCenterDelegate>)userNotificationCenterDelegate;

/**
 *  @abstract Handle the user input from a reply type notification action.
 *
 *  @discussion Call this method in your -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler:, passing the action identifier, userInfo dictionary, responseInfo dictionary, and completionHandler callback.
 *
 *  This method will post a message on behalf of the user, with the contents of their inline reply. When the message upload completes (either in success or failure), the completion handler will be called.
 *
 *  If the action identifier does not match SKTUserNotificationReplyActionIdentifier, the completion handler will be called immediately and the notification will be ignored.
 *
 *  This method is called automatically if SKTSettings.enableAppDelegateSwizzling is set to YES.
 *
 *  @see SKTSettings
 */
+(void)handleUserNotificationActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void (^)(void))completionHandler;

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
+(void)handleUserNotificationActionWithIdentifier:(NSString *)identifier withResponseInfo:(NSDictionary *)responseInfo completionHandler:(void (^)(void))completionHandler __attribute__((deprecated("Use + handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler: instead.")));

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

/**
 *  @abstract Loads a conversation by its ID and sets it as the active conversation for the current session.
 *
 *  @discussion When called, subscribes the current device for push notifications on the passed conversationId, and sets the SDK to send and receive messages for that conversation going forward. Does not unsubscribe for notification on previously loaded conversations.
 *
 *  If the conversation is already set to the passed ID, this call is a no-op.
 */
+(void)loadConversation:(NSString*)conversationId completionHandler:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable userInfo))completionHandler;

/**
 *
 * @abstract Returns a list of conversations from storage.
 *
 * @discussion Returns a list of SKTConversation objects from storage.
 *
 */
+ (void)getConversations:(void (^)(NSError  *_Nullable, NSArray  *_Nullable))completionHandler;

/**
 *
 * @abstract Updating the conversation delegate
 *
 * @discussion when called, a new delegate is set
 */
+ (void)updateConversationDelegate:(id<SKTConversationDelegate>)delegate __deprecated_msg("Use `setConversationDelegate` instead.");


/**
 *
 * @abstract Set a conversation delegate may be used to receive callbacks when important changes happen in the conversation.
 *
 * @param delegate A conversation delegate conforming to `SKTConversationDelegate`.
 *
 * @discussion In a single conversation scenario, this delegate will be used for the single conversation. In a multi-conversation scenario, this delegate can be used to receive callbacks for changes in all conversations.
 */
+ (void)setConversationDelegate:(id<SKTConversationDelegate>)delegate NS_SWIFT_NAME(setConversationDelegate(delegate:));

/**
 *
 * @abstract Loads a list of conversations
 *
 * @discussion Retrives the next 10 conversations from the server, and stores them.
 *
 */
+ (void)getMoreConversations:(void (^)(NSError * _Nullable))completionHandler;

/**
 *
 * @abstract A boolean representing if the server has more conversations to load for the user, to support pagination.
 *
 * @discussion When called, returns a boolean indicating if the server has more conversations to load for the user.
 *
 */
+ (BOOL)hasMoreConversations;

/**
 *
 * @abstract Clears the last known user from both memory and persistence, for the provided app id.
 *
 * @discussion When called, the last known user info are reset back to nil and deleted from persistence, for the provided app id. This should be called before the initialization, it will have no effect otherwise.
 *
 */
+(void) forgetLastKnownUserForAppId:(NSString*)appId __attribute__((deprecated("This method is deprecated. Use resetLastKnownAuthenticatedUser instead.")));

/**
 *
 * @abstract Clears the last known authenticated user from both memory and persistence.
 *
 * @discussion When called, the last known user info are reset back to nil and deleted from persistence. This should be called before the initialization, it will have no effect otherwise.
 *
 */
+(void)resetLastKnownAuthenticatedUser;

@end
NS_ASSUME_NONNULL_END
