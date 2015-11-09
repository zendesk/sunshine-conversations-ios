//
//  SKTSettings.h
//  Smooch
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <UIKit/UIKit.h>

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
 *  @discussion The default value is nil.
 *
 *  This value may only be set once, and must be set at init time. To change at runtime, use Smooch.login instead.
 *
 *  @see Smooch
 */
@property(nonatomic, copy) NSString* userId;

/**
 *  @abstract Optional jwt used to prove the origin of the login request.
 *
 *  @discussion Used only if userId is not nil. The default value is nil. 
 *
 *  This value may only be set once, and must be set at init time. To change at runtime, use Smooch.login instead.
 *
 *  @see Smooch
 */
@property(nonatomic, copy) NSString* jwt;

/**
 *  @abstract Maximum number of seconds to display in-app notifications before dismissing.
 *
 *  @discussion Setting this value to 0 will cause notications to stay on-screen until the user acts on them.
 *
 *  The default value is 8.
 */
@property NSUInteger notificationDisplayTime;

@end
