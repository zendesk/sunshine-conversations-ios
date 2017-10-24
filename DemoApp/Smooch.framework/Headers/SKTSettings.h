//
//  SKTSettings.h
//  Smooch
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@interface SKTSettings : NSObject

/**
 *  @abstract Initializes a settings object with the given app id.
 *
 *  @param appId A valid app id retrieved from the Smooch web portal.
 */
+(instancetype)settingsWithAppId:(NSString*)appId;

/**
 *  @abstract Initializes a settings object with the given app id and auth code.
 *
 *  @param appId A valid app id retrieved from the Smooch web portal.
 *  @param authCode A valid auth code generated from the Smooch API.
 */
+(instancetype)settingsWithAppId:(NSString*)appId andAuthCode:(NSString*)authCode;

/**
 *  @abstract The app id corresponding to your application.
 *
 *  @discussion App id can be retrieved from the Smooch web portal
 *
 *  This value may only be set once, and must be set at init time.
 */
@property(nonatomic, copy) NSString* appId;

/**
 *  @abstract The auth code being used to authenticate as an existing user.
 *
 *  @discussion Auth code can be retrieved from the Smooch API
 *
 *  This value may only be set once, and must be set at init time.
 */
@property(nonatomic, copy) NSString* authCode;

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
