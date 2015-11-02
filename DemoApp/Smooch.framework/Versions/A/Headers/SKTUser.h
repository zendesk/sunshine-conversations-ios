//
//  SKTUser.h
//  Smooch
//
//  Copyright (c) 2015 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SKTUser : NSObject

/**
 *  @abstract The object representing the current user.
 *
 *  @discussion Returns nil if +initWithSettings: has not been called yet.
 *
 *  @see Smooch
 */
+(instancetype)currentUser;

/**
 *  @abstract Adds custom properties to the user. This info is used to provide more context around who a user is.
 *
 *  @discussion Keys must be of type NSString, and values must be of type NSString, NSNumber, or NSDate; any other type will be converted to NSString using the -description method.
 *  
 *  Example:
 *
 *  `[user addProperties:@{ @"nickname" : @"Lil' Big Daddy Slim",  @"weight" : @650, @"premiumUser" : @YES }];`
 *
 *  Changes to user properties are uploaded in batches every 60 seconds, or when the app is sent to the background.
 *
 *  This API is additive, and subsequent calls will override values for the provided keys.
 *
 *  @param properties The properties to set for the current user.
 */
-(void)addProperties:(NSDictionary*)properties;

/**
 *  @abstract The userId for this user
 *
 *  @discussion This property is set by either calling +initWithSettings: with a userId, or calling +login:jwt:.
 *
 *  @see SKTSettings
 *  @see Smooch
 */
@property(readonly) NSString* userId;

/**
 *  @abstract The user's first name, to be used as part of the display name when sending messages.
 */
@property(copy) NSString* firstName;

/**
 *  @abstract The user's last name, to be used as part of the display name when sending messages.
 */
@property(copy) NSString* lastName;

/**
 *  @abstract The user's email, to be used to display a gravatar.
 */
@property(copy) NSString* email;

/**
 *  @abstract The date the user started using your service. This can be used to create Whispers for user onboarding.
 */
@property(copy) NSDate* signedUpAt;

@end
