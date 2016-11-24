//
//  SKTConversationActivity.h
//  Smooch
//
//  Copyright © 2016 Smooch Technologies. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract An activity type indicating that the appMaker started typing a response
 */
extern NSString const *SKTConversationActivityTypeTypingStart;

/**
 *  @abstract An activity type indicating that the appMaker stopped typing a response
 */
extern NSString const *SKTConversationActivityTypeTypingStop;

/**
 *  @abstract A key whose value is an NSString representing the appMaker name.
 *
 *  @discussion This key is used in the SKTConversationActivity data object.
 */
extern NSString const *SKTConversationActivityDataNameKey;

/**
 *  @abstract A key whose value is an NSString representing the URL of the appMaker avatar.
 *
 *  @discussion This key is used in the SKTConversationActivity data object.
 */
extern NSString const *SKTConversationActivityDataAvatarUrlKey;

@interface SKTConversationActivity : NSObject

/**
 *  @abstract the role of who is performing the typing activity
 */
@property(readonly) NSString *role;

/**
 *  @abstract the type of activity that is being triggered. Could be either SKTConversationActivityTypeTypingStart or SKTConversationActivityTypeTypingStop
 */
@property(readonly) NSString *type;

/**
 *  @abstract additional data for this activity. Posible values are the appMaker's 'name' and/or 'avatarUrl'
 */
@property(readonly, nullable) NSDictionary *data;

@end
NS_ASSUME_NONNULL_END
