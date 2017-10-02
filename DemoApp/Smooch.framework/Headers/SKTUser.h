//
//  SKTUser.h
//  Smooch
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@interface SKTUser : NSObject

/**
 *  @abstract The object representing the current user.
 *
 *  @discussion Returns nil if +initWithSettings:completionHandler: has not been called yet.
 *
 *  @see Smooch
 */
+(nullable instancetype)currentUser;

/**
 *  @abstract Adds custom properties to the user. This info is used to provide more context around who a user is.
 *
 *  @discussion Keys must be of type NSString, and values must be of type NSString, NSNumber, or NSDate; any other type will be converted to NSString using the -description method.
 *
 *  Example:
 *
 *  `[user addProperties:@{ @"nickname" : @"Lil' Big Daddy Slim",  @"weight" : @650, @"premiumUser" : @YES }];`
 *
 *  Changes to user properties are uploaded in batches at regular intervals, when the app is sent to the background, or when a message is sent.
 *
 *  This API is additive, and subsequent calls will override values for the provided keys.
 *
 *  @param properties The properties to set for the current user.
 */
-(void)addProperties:(NSDictionary*)properties;

/**
 *  @abstract The assigned appUserId for this user.
 *
 *  @discussion Unlike `userId`, this property is set automatically by Smooch, and is not configurable. This is analogous to `appUser._id` in the REST API response. A user is assigned an `appUserId` once they start a conversation or when an existing user is logged in by calling +login:jwt:completionHandler:.
 *
 *  @see Smooch
 */
@property(readonly, nullable) NSString* appUserId;

/**
 *  @abstract The assigned userId for this user.
 *
 *  @discussion This property is set by calling +login:jwt:completionHandler:.
 *
 *  Unlike `appUserId`, this value is assigned and managed by the developer, and is used to identify a user across devices and app installations.
 *
 *  @see SKTSettings
 *  @see Smooch
 */
@property(readonly, nullable) NSString* userId;

/**
 *  @abstract The user's first name, to be used as part of the display name when sending messages.
 */
@property(copy, nullable) NSString* firstName;

/**
 *  @abstract The user's custom properties.
 */
@property(copy, readonly) NSDictionary *properties;

/**
 *  @abstract The user's last name, to be used as part of the display name when sending messages.
 */
@property(copy, nullable) NSString* lastName;

/**
 *  @abstract The user's email, to be used to display a gravatar.
 */
@property(copy, nullable) NSString* email;

/**
 *  @abstract The date the user started using your service.
 */
@property(copy, nullable) NSDate* signedUpAt;

@end
NS_ASSUME_NONNULL_END
