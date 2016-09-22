//
//  SKTSettings.h
//  Smooch
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@interface SKTSettings : NSObject

/**
 *  @abstract Initializes a settings object with the given app token.
 *
 *  @param appToken A valid app token retrieved from the Smooch web portal.
 */
+(instancetype)settingsWithAppToken:(NSString*)appToken;

/**
 *  @abstract The app token corresponding to your application.
 *
 *  @discussion App tokens are issued on the Smooch web portal. 
 *
 *  This value may only be set once, and must be set at init time.
 */
@property(nonatomic, copy) NSString* appToken;

/**
 *  @abstract The accent color for the conversation screen.
 *
 *  @discussion Used as the color of user message bubbles, as well as the color of the send button and text input caret.
 *
 *  The default value is #00B0FF.
 */
@property(nonatomic, strong) UIColor* conversationAccentColor;

/**
 *  @abstract The status bar style to use on the conversation screen.
 *
 *  @discussion You should use this property if your app uses UIAppearance to style UINavigationBar, and your styling requires a specific status bar color.
 * 
 *  The default value is UIStatusBarStyleDefault.
 */
@property UIStatusBarStyle conversationStatusBarStyle;

/**
 *  @abstract The distinct id of the current user, if known.
 *
 *  @discussion Defaults to the last known user id for the given app token (user login state is persisted between app launches). Defaults to nil if the previous user was anonymous, or if there was no previous user.
 *
 *  This value may only be set once, and must be set at init time. To change at runtime, use Smooch.login instead.
 *
 *  @see Smooch
 */
@property(nonatomic, copy, nullable) NSString* userId;

/**
 *  @abstract Optional jwt used to prove the origin of the login request.
 *
 *  @discussion Used only if userId is not nil. Defaults to the last known jwt for the given app token.
 *
 *  This value may only be set once, and must be set at init time. To change at runtime, use Smooch.login instead.
 *
 *  @see Smooch
 */
@property(nonatomic, copy, nullable) NSString* jwt;

/**
 *  @abstract Maximum number of seconds to display in-app notifications before dismissing.
 *
 *  @discussion Setting this value to 0 will cause notications to stay on-screen until the user acts on them.
 *
 *  The default value is 8.
 */
@property NSUInteger notificationDisplayTime;

/**
 *  @abstract Whether or not to swizzle app delegate methods for handling push notifications.
 *
 *  @discussion When set to YES, Smooch will swizzle the following methods of your UIApplicationDelegate in order to automatically handle push notification receiving and registering, as well as user notification handling.
 *
 *  1. -application:didRegisterForRemoteNotificationsWithDeviceToken:
 *  2. -application:didFailToRegisterForRemoteNotificationsWithError:
 *  3. -application:didReceiveRemoteNotification:
 *  4. -application:didReceiveRemoteNotification:fetchCompletionHandler:
 *  5. -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler:
 *
 *  If set to NO, Smooch will not perform swizzling. It is up to the app to handle Smooch push notifications by doing the following:
 *
 *  1. When a new push token is received in -application:didRegisterForRemoteNotificationsWithDeviceToken:, you must call Smooch +setPushToken.
 *  2. In your -application:didReceiveRemoteNotification: or -application:didReceiveRemoteNotification:fetchCompletionHandler: callback, you must call Smooch +handlePushNotification: with the passed userInfo dictionary.
 *  3. In your -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler: callback, you must call Smooch +handleUserNotificationActionWithIdentifier:withResponseInfo:completionHandler: with the correct parameters.
 *
 *  The default value is YES.
 *
 *  @see Smooch
 */
@property BOOL enableAppDelegateSwizzling;

/**
 *  @abstract Whether or not to automatically replace the application's UNUserNotificationCenterDelegate at init time.
 *
 *  @discussion For more information, see the +userNotificationCenterDelegate method of the Smooch class.
 *
 *  If set to NO, the application must forward calls from its own UNUserNotificationCenterDelegate to Smooch to ensure proper handling of notifications on iOS 10.
 *
 *  The default value is YES.
 *
 *  @see Smooch
 */
@property BOOL enableUserNotificationCenterDelegateOverride;

/**
 *  @abstract Whether or not to request user notification privileges after the user sends their first message.
 *
 *  @discussion If your app has a preferred time to request user notification privileges, set this to NO.
 *
 *  If set to NO, the application must make sure to register the Smooch user notification category settings. For more information, see the +userNotificationCategories method of the Smooch class.
 *
 *  The default value is YES.
 *
 *  @see Smooch
 */
@property BOOL requestPushPermissionOnFirstMessage;

@end
NS_ASSUME_NONNULL_END
