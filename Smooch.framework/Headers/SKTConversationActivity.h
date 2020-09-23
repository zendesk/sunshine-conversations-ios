//
//  SKTConversationActivity.h
//  Smooch
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract An activity type indicating that a participant of the converation started typing a response
 */
extern NSString *const SKTConversationActivityTypeTypingStart;

/**
 *  @abstract An activity type indicating that a participant of the converation stopped typing a response
 */
extern NSString *const SKTConversationActivityTypeTypingStop;

/**
 *  @abstract An activity type indicating that a participant of the converation recently read the user message
 *
 *  This event type is triggered for the current user when the conversation is read on a different device. 
 */
extern NSString *const SKTConversationActivityTypeConversationRead;

/**
 *  @abstract An activity type indicating that the current user was added to a conversation
 */
extern NSString *const SKTConversationActivityTypeConversationAdded;

/**
 *  @abstract An activity type indicating that the current user was removed from a conversation
 */
extern NSString *const SKTConversationActivityTypeConversationRemoved;

/**
 *  @abstract An activity type indicating that another user was added to a conversation that the current user is part of
 */
extern NSString *const SKTConversationActivityTypeParticipantAdded;

/**
 *  @abstract An activity type indicating that another user was removed from a conversation that the current user is part of
 */
extern NSString *const SKTConversationActivityTypeParticipantRemoved;

/**
 *  @abstract A key whose value is an NSString representing the business name.
 *
 *  @discussion This key is used in the SKTConversationActivity data object.
 */
extern NSString *const SKTConversationActivityDataNameKey;

/**
 *  @abstract A key whose value is an NSString representing the URL of the business avatar.
 *
 *  @discussion This key is used in the SKTConversationActivity data object.
 */
extern NSString *const SKTConversationActivityDataAvatarUrlKey;

@interface SKTConversationActivity : NSObject

/**
 *  @abstract the role of who is performing the typing activity
 */
@property(readonly, nullable) NSString *role;

/**
 *  @abstract the type of activity that is being triggered. Could be either
 *   - SKTConversationActivityTypeTypingStart
 *   - SKTConversationActivityTypeTypingStop
 *   - SKTConversationActivityTypeConversationRead
 *   - SKTConversationActivityTypeConversationAdded
 *   - SKTConversationActivityTypeConversationRemoved
 *   - SKTConversationActivityTypeParticipantAdded
 *   - SKTConversationActivityTypeParticipantRemoved
 */
@property(readonly) NSString *type;

/**
 *  @abstract additional data for this activity. Posible values are the business's 'name' and/or 'avatarUrl'
 */
@property(readonly, nullable) NSDictionary *data;

/**
 *  @abstract conversationId for activity. Can be nil
 */
@property(readonly, nullable) NSString *conversationId;

/**
 *  @abstract date when the business last read user messages for activities of type SKTConversationActivityTypeConversationRead
 */
@property(readonly, nullable) NSDate *businessLastRead;

/**
 * @abstract The userId if available, null otherwise
 *
 * available for SKTConversationActivityTypeParticipantAdded, SKTConversationActivityTypeParticipantRemoved
 */
@property(readonly, nullable) NSString *userId;

@end
NS_ASSUME_NONNULL_END
